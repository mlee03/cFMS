!***********************************************************************
!*                   GNU Lesser General Public License
!*
!* This file is part of the GFDL Flexible Modeling System (FMS).
!*
!* FMS is free software: you can redistribute it and/or modify it under
!* the terms of the GNU Lesser General Public License as published by
!* the Free Software Foundation, either version 3 of the License, or (at
!* your option) any later version.
!*
!* FMS is distributed in the hope that it will be useful, but WITHOUT
!* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
!* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
!* for more details.
!*
!* You should have received a copy of the GNU Lesser General Public
!* License along with FMS.  If not, see <http://www.gnu.org/licenses/>.
!***********************************************************************

program test_data_override_ongrid

!> @brief This file was copied from test_fms/data_override and is used to generate test input files 
!! This file will eventually be replaced 
!! from FMS: "This programs tests data_override ability to override data for an
!! on grid case and when using bilinear interpolation"

use platform_mod,      only: r4_kind, r8_kind
use mpp_domains_mod,   only: mpp_define_domains, mpp_define_io_domain, mpp_get_data_domain, &
                             mpp_domains_set_stack_size, mpp_get_compute_domain, domain2d
use mpp_mod,           only: mpp_init, mpp_exit, mpp_pe, mpp_root_pe, mpp_error, FATAL, &
                             input_nml_file, mpp_sync, NOTE, mpp_npes, mpp_get_current_pelist, &
                             mpp_set_current_pelist
use data_override_mod, only: data_override_init, data_override
use fms2_io_mod
use time_manager_mod,  only: set_calendar_type, time_type, set_date, NOLEAP
use netcdf,            only: nf90_create, nf90_def_dim, nf90_def_var, nf90_enddef, nf90_put_var, &
                             nf90_close, nf90_put_att, nf90_clobber, nf90_64bit_offset, nf90_char, &
                             nf90_double, nf90_unlimited
use fms_mod, only: string, fms_init, fms_end

implicit none

integer, dimension(2)                      :: layout = (/2,3/) !< Domain layout
integer                                    :: nlon = 360       !< Number of points in x axis
integer                                    :: nlat = 180       !< Number of points in y axis
type(domain2d)                             :: Domain           !< Domain with mask table
integer                                    :: is               !< Starting x index
integer                                    :: ie               !< Ending x index
integer                                    :: js               !< Starting y index
integer                                    :: je               !< Ending y index
integer                                    :: nhalox=2, nhaloy=2
integer                                    :: io_status
integer, parameter                         :: array_3d = 1
integer, parameter                         :: array_2d = 2
integer, parameter                         :: scalar = 3
integer                                    :: test_case
logical                                    :: init_with_mode = .false.
integer                                    :: npes
integer, allocatable                       :: pelist(:)
logical                                    :: write_only=.false. !< True if creating the input files only

namelist /test_data_override_ongrid_nml/ test_case

call fms_init
call fms2_io_init

read (input_nml_file, test_data_override_ongrid_nml, iostat=io_status)
if (io_status > 0) call mpp_error(FATAL,'=>test_data_override_ongrid: Error reading input.nml')

!< Wait for the root PE to catch up
call mpp_sync

select case (test_case)
case (array_3d)
   call generate_array_3d_input_file ()
case (array_2d)
   call generate_array_2d_input_file ()
case (scalar)
   call generate_scalar_input_file ()
end select

call mpp_sync()
call mpp_error(NOTE, "Finished creating INPUT Files")  

call fms_end

contains

subroutine create_grid_spec_file
  type(FmsNetcdfFile_t) :: fileobj

  if (open_file(fileobj, 'INPUT/grid_spec.nc', 'overwrite')) then
    call register_axis(fileobj, 'str', 255)
    call register_field(fileobj, 'ocn_mosaic_file', 'char', (/'str'/))
    call write_data(fileobj, 'ocn_mosaic_file', "ocean_mosaic.nc")
    call close_file(fileobj)
  else
    call mpp_error(FATAL, "Error opening the file: 'INPUT/grid_spec.nc' to write")
  endif
end subroutine create_grid_spec_file

subroutine create_ocean_mosaic_file
  type(FmsNetcdfFile_t) :: fileobj
  character(len=10) :: dimnames(2)

  dimnames(1) = 'str'
  dimnames(2) = 'ntiles'
  if (open_file(fileobj, 'INPUT/ocean_mosaic.nc', 'overwrite')) then
    call register_axis(fileobj, dimnames(1) , 255)
    call register_axis(fileobj, dimnames(2), 1)
    call register_field(fileobj, 'gridfiles', 'char', dimnames)
    call write_data(fileobj, 'gridfiles', (/"ocean_hgrid.nc"/))
    call close_file(fileobj)
  else
    call mpp_error(FATAL, "Error opening the file: 'INPUT/ocean_mosaic.nc' to write")
  endif
end subroutine create_ocean_mosaic_file

subroutine create_ocean_hgrid_file
  type(FmsNetcdfFile_t) :: fileobj
  real(r8_kind), allocatable, dimension(:,:) :: xdata, ydata
  integer :: nx, nxp, ny, nyp, i, j

  nx = nlon*2
  nxp = nx+1
  ny = nlat*2
  nyp = ny+1

  allocate(xdata(nxp, nyp))
  xdata(1,:) = 0_r8_kind
  do i = 2, nxp
    xdata(i,:) = xdata(i-1,:) + 0.5_r8_kind
  enddo

  allocate(ydata(nxp, nyp))
  ydata(:,1) = -90.0_r8_kind
  do i = 2, nyp
    ydata(:,i) = ydata(:, i-1) + 0.5_r8_kind
  enddo

  if (open_file(fileobj, 'INPUT/ocean_hgrid.nc', 'overwrite')) then
    call register_axis(fileobj, "nx", nx)
    call register_axis(fileobj, "ny", ny)
    call register_axis(fileobj, "nxp", nxp)
    call register_axis(fileobj, "nyp", nyp)
    call register_field(fileobj, 'x', 'float', (/'nxp', 'nyp'/))
    call register_field(fileobj, 'y', 'float', (/'nxp', 'nyp'/))
    call register_field(fileobj, 'area', 'float', (/'nx', 'ny'/))
    call write_data(fileobj, "x", xdata)
    call write_data(fileobj, "y", ydata)
    call close_file(fileobj)
  else
    call mpp_error(FATAL, "Error opening the file: 'INPUT/ocean_hgrid.nc' to write")
  endif
end subroutine create_ocean_hgrid_file


!> @brief Creates an input netcdf data file to use for the ongrid data_override test case
!! with either an increasing or decreasing lat, lon grid
subroutine create_array_2d_data_file()

  type(FmsNetcdfFile_t)         :: fileobj          !< Fms2_io fileobj
  character(len=10)             :: dimnames(3)      !< dimension names for the variable
  real(r8_kind), allocatable    :: runoff_in(:,:,:) !< Data to write
  real(r8_kind), allocatable    :: time_data(:)     !< Time dimension data
  real(r8_kind), allocatable    :: lat_data(:)      !< Lat dimension data
  real(r8_kind), allocatable    :: lon_data(:)      !< Lon dimension data
  character(len=:), allocatable :: filename         !< Name of the file
  integer                       :: factor           !< This is used when creating the grid data
                                                      !! -1 if the grid is decreasing
                                                      !! +1 if the grid is increasing
  integer                       :: i, j, k          !< For looping through variables
  integer                       :: nlon_data, nlat_data

  nlon_data = nlon + 1
  nlat_data = nlat - 1
  allocate(runoff_in(nlon_data, nlat_data, 10))
  allocate(time_data(10))
  allocate(lat_data(nlat_data))
  allocate(lon_data(nlon_data))

  filename = 'INPUT/array_2d.nc'
  lon_data(1) = 360.0_r8_kind
  lat_data(1) = 89.0_r8_kind
  factor = -1
  do i = 1, nlon_data
     do j = 1, nlat_data
        do k = 1, 10
           runoff_in(i, j, k) = 100._r8_kind + k*.01_r8_kind
        enddo
     enddo
  enddo

  do i = 2, nlon_data
    lon_data(i) = real(lon_data(i-1) + 1*factor, r8_kind)
  enddo

  do i = 2, nlat_data
    lat_data(i) =real(lat_data(i-1) + 1*factor, r8_kind)
  enddo

  time_data = (/1_r8_kind, 2_r8_kind, &
                3_r8_kind, 5_r8_kind, &
                6_r8_kind, 7_r8_kind, &
                8_r8_kind, 9_r8_kind, &
                10_r8_kind, 11_r8_kind/)

  dimnames(1) = 'i'
  dimnames(2) = 'j'
  dimnames(3) = 'time'

  if (open_file(fileobj, filename, 'overwrite')) then
    call register_axis(fileobj, "i", nlon_data)
    call register_axis(fileobj, "j", nlat_data)
    call register_axis(fileobj, "time", unlimited)

    call register_field(fileobj, "i", "float", (/"i"/))
    call register_variable_attribute(fileobj, "i", "cartesian_axis", "x", str_len=1)

    call register_field(fileobj, "j", "float", (/"j"/))
    call register_variable_attribute(fileobj, "j", "cartesian_axis", "y", str_len=1)

    call register_field(fileobj, "time", "float", (/"time"/))
    call register_variable_attribute(fileobj, "time", "cartesian_axis", "T", str_len=1)
    call register_variable_attribute(fileobj, "time", "calendar", "noleap", str_len=6)
    call register_variable_attribute(fileobj, "time", "units", "days since 0001-01-01 00:00:00", str_len=30)

    call register_field(fileobj, "runoff", "double", dimnames)

    call write_data(fileobj, "runoff", runoff_in)
    call write_data(fileobj, "i", lon_data)
    call write_data(fileobj, "j", lat_data)
    call write_data(fileobj, "time", time_data)
    call close_file(fileobj)
  endif
  deallocate(runoff_in)
end subroutine create_array_2d_data_file

!> @brief Creates an input netcdf data file to use for the ongrid data_override test case
!! with either an increasing or decreasing lat, lon grid
subroutine create_array_3d_data_file()

  type(FmsNetcdfFile_t)         :: fileobj          !< Fms2_io fileobj
  character(len=10)             :: dimnames(4)      !< dimension names for the variable
  real(r8_kind), allocatable    :: runoff_in(:,:,:,:) !< Data to write
  real(r8_kind), allocatable    :: time_data(:)     !< Time dimension data
  real(r8_kind), allocatable    :: lat_data(:)      !< Lat dimension data
  real(r8_kind), allocatable    :: lon_data(:)      !< Lon dimension data
  integer,       allocatable    :: z_data(:)
  character(len=:), allocatable :: filename         !< Name of the file
  integer                       :: factor           !< This is used when creating the grid data
                                                      !! -1 if the grid is decreasing
                                                      !! +1 if the grid is increasing
  integer                       :: i, j, k, z       !< For looping through variables
  integer                       :: nlon_data, nlat_data, nz_data

  nlon_data = nlon + 1
  nlat_data = nlat - 1
  nz_data = 5
  allocate(runoff_in(nlon_data, nlat_data, nz_data, 10))
  allocate(time_data(10))
  allocate(lat_data(nlat_data))
  allocate(lon_data(nlon_data))
  allocate(z_data(nz_data))

  filename = 'INPUT/array_3d.nc'
  lon_data(1) = 360.0_r8_kind
  lat_data(1) = 89.0_r8_kind
  factor = -1
  do i = 1, nlon_data
     do j = 1, nlat_data
        do z=1, nz_data
           do k = 1, 10
              runoff_in(i, j, z, k) = z*100._r8_kind + k*.01_r8_kind
              != real(-i, kind=r8_kind) * 100._r8_kind + &
              ! real(-j, kind=r8_kind) + real(-k, kind=r8_kind)/100._r8_kind
           end do
        enddo
     enddo
  enddo
  
  do i = 2, nlon_data
    lon_data(i) = real(lon_data(i-1) + 1*factor, r8_kind)
  enddo

  do i = 2, nlat_data
    lat_data(i) =real(lat_data(i-1) + 1*factor, r8_kind)
  enddo

  do i=1, nz_data
     z_data(i) = i
  end do

  time_data = (/1_r8_kind, 2_r8_kind, &
                3_r8_kind, 5_r8_kind, &
                6_r8_kind, 7_r8_kind, &
                8_r8_kind, 9_r8_kind, &
                10_r8_kind, 11_r8_kind/)

  dimnames(1) = 'i'
  dimnames(2) = 'j'
  dimnames(3) = 'z'
  dimnames(4) = 'time'

  if (open_file(fileobj, filename, 'overwrite')) then
    call register_axis(fileobj, "i", nlon_data)
    call register_axis(fileobj, "j", nlat_data)
    call register_axis(fileobj, "z", nz_data)
    call register_axis(fileobj, "time", unlimited)

    call register_field(fileobj, "i", "float", (/"i"/))
    call register_variable_attribute(fileobj, "i", "cartesian_axis", "x", str_len=1)

    call register_field(fileobj, "j", "float", (/"j"/))
    call register_variable_attribute(fileobj, "j", "cartesian_axis", "y", str_len=1)

    call register_field(fileobj, "z", "int", (/"z"/))
    call register_variable_attribute(fileobj, "z", "extra_axis", "z", str_len=1)
    
    call register_field(fileobj, "time", "float", (/"time"/))
    call register_variable_attribute(fileobj, "time", "cartesian_axis", "T", str_len=1)
    call register_variable_attribute(fileobj, "time", "calendar", "noleap", str_len=6)
    call register_variable_attribute(fileobj, "time", "units", "days since 0001-01-01 00:00:00", str_len=30)

    call register_field(fileobj, "runoff", "double", dimnames)

    call write_data(fileobj, "runoff", runoff_in)
    call write_data(fileobj, "i", lon_data)
    call write_data(fileobj, "j", lat_data)
    call write_data(fileobj, "z", z_data)
    call write_data(fileobj, "time", time_data)
    call close_file(fileobj)
  endif
  deallocate(runoff_in)
end subroutine create_array_3d_data_file

!> @brief Generates the input for the bilinear data_override test_case
subroutine generate_array_2d_input_file
  if (mpp_pe() .eq. mpp_root_pe()) then
    call create_grid_spec_file ()
    call create_ocean_mosaic_file()
    call create_ocean_hgrid_file()
    call create_array_2d_data_file()
  endif
  call mpp_sync()
end subroutine generate_array_2d_input_file

!> @brief Generates the input for the bilinear data_override test_case
subroutine generate_array_3d_input_file
  if (mpp_pe() .eq. mpp_root_pe()) then
    call create_grid_spec_file ()
    call create_ocean_mosaic_file()
    call create_ocean_hgrid_file()
    call create_array_3d_data_file()
  endif
  call mpp_sync()
end subroutine generate_array_3d_input_file


!> @brief Generates the input for the bilinear data_override test_case
subroutine generate_scalar_input_file
  if (mpp_pe() .eq. mpp_root_pe()) then
    call create_grid_spec_file ()
    call create_ocean_mosaic_file()
    call create_ocean_hgrid_file()
    call create_scalar_data_file()
  endif
  call mpp_sync()
end subroutine generate_scalar_input_file

subroutine create_scalar_data_file
  type(FmsNetcdfFile_t) :: fileobj
  character(len=10) :: dimnames(1)
  real(r8_kind), allocatable, dimension(:)     :: co2_in
  real(r8_kind), allocatable, dimension(:)     :: time_data
  integer :: i

  allocate(co2_in(10))
  allocate(time_data(10))

  do i = 1, 10
    co2_in(i) = real(i, r8_kind)
  enddo

  time_data = (/1_r8_kind, 2_r8_kind, &
                3_r8_kind, 5_r8_kind, &
                6_r8_kind, 7_r8_kind, &
                8_r8_kind, 9_r8_kind, &
                10_r8_kind, 11_r8_kind/)

  dimnames(1) = 'time'

  if (open_file(fileobj, 'INPUT/scalar.nc', 'overwrite')) then
    call register_axis(fileobj, "time", unlimited)
    call register_field(fileobj, "time", "float", (/"time"/))
    call register_variable_attribute(fileobj, "time", "cartesian_axis", "T", str_len=1)
    call register_variable_attribute(fileobj, "time", "calendar", "noleap", str_len=6)
    call register_variable_attribute(fileobj, "time", "units", "days since 0001-01-01 00:00:00", str_len=30)

    call register_field(fileobj, "co2", "float", dimnames)
    call write_data(fileobj, "co2", co2_in)
    call write_data(fileobj, "time", time_data)
    call close_file(fileobj)
  else
    call mpp_error(FATAL, "Error opening the file: 'INPUT/scalar.nc' to write")
  endif
  deallocate(co2_in)
end subroutine create_scalar_data_file

end program test_data_override_ongrid
