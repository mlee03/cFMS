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
module cfms_mod

  use FMS, only : fms_init, fms_end, fms_mpp_domains_init
  use FMS, only : fms_string_utils_c2f_string, fms_string_utils_f2c_string
  use FMS, only : FmsMppDomain2D, FmsMppDomainsNestDomain_type
  use FMS, only : fms_mpp_domains_get_domain_name
  use FMS, only : fms_mpp_domains_define_domains, fms_mpp_domains_define_io_domain 
  use FMS, only : fms_mpp_domains_set_compute_domain, fms_mpp_domains_set_data_domain, fms_mpp_domains_set_global_domain
  use FMS, only : fms_mpp_domains_define_nest_domains

  use platform_mod, only : FMS_PATH_LEN
  
  use iso_c_binding

  implicit none
  private
  
  public :: cfms_init, cfms_end
  public :: cfms_set_current_domain, cfms_get_domain_name, cfms_set_npes
  public :: cfms_define_domains2D, cfms_define_io_domain2D
  public :: cfms_set_compute_domain2D, cfms_set_data_domain2D, cfms_set_global_domain2D
  public :: cfms_define_nest_domain
  
  integer, parameter :: NAME_LENGTH = 64 !< value taken from mpp_domains
  character(FMS_PATH_LEN), parameter :: input_nml_path="./input.nml"

  type(FmsMppDomain2D), allocatable, target,  public :: domain(:)
  type(FmsMppDomain2D), pointer :: current_domain
  
  type(FmsMppDomainsNestDomain_type), public :: nest_domain

  integer :: npes
  
contains

  subroutine cfms_set_current_domain(domain_id)

    implicit none
    integer, intent(in), optional :: domain_id
    
    if(present(domain_id)) then
       current_domain => domain(domain_id)
    else
       current_domain => domain(1)
    end if
    
  end subroutine cfms_set_current_domain
  

  subroutine cfms_get_domain_name(domain_id, domain_name_c) bind(C)

    implicit none

    integer, intent(in), optional :: domain_id
    character(kind=c_char), intent(out) :: domain_name_c(NAME_LENGTH)
    character(len=NAME_LENGTH) :: domain_name_f
    
    call cfms_set_current_domain(domain_id)
    domain_name_f = fms_mpp_domains_get_domain_name(current_domain)
    call fms_string_utils_f2c_string(domain_name_c, domain_name_f)
    
  end subroutine cfms_get_domain_name

  subroutine cfms_set_npes(npes_in) bind(C)
    implicit none
    integer, intent(in) :: npes_in
    npes = npes_in
  end subroutine cfms_set_npes
  
  subroutine cfms_init(localcomm, alt_input_nml_path_ptr, ndomain) bind(C)

    implicit none
    integer, intent(in), optional     :: localcomm
    integer, intent(in), optional     :: ndomain
    type(c_ptr), intent(in), optional :: alt_input_nml_path_ptr
    
    character(100) :: alt_input_nml_path = input_nml_path

    if(present(alt_input_nml_path_ptr)) &
         alt_input_nml_path = fms_string_utils_c2f_string(alt_input_nml_path_ptr)
    
    call fms_init(localcomm=localcomm, alt_input_nml_path=alt_input_nml_path)
    call fms_mpp_domains_init()
    
    if(present(ndomain)) then
       allocate(domain(ndomain))
    else
       allocate(domain(1))
    end if

  end subroutine cfms_init

  
  subroutine cfms_end() bind(C)
    implicit none
    call fms_end()
  end subroutine cfms_end

  !subroutine cfms_define_mosaic(global_indices, layout, num_tile, num_contact, tile1, tile2,              &
  !                              istart1, iend1, jstart1, jend1, istart2, iend2, jstart2, jend2, pe_start, &
  !                              pe_end, pelist, whalo, ehalo, shalo, nhalo, xextent, yextent,             &
  !                              maskmap, name, memory_size, symmetry, xflags, yflags, tile_id ) bind(C)
  !
  !  implicit none
  !
  !  integer, intent(in) :: global_indices(4)
  !  integer, intent(in) :: layout(2)
  !  integer, intent(in) :: num_tile
  !  integer, intent(in) :: num_contact
  !  integer, intent(in) :: tile1, tile2
  !  integer, intent(in), dimension(num_tile) :: istart1, iend1, jstart1, jend1
  !  integer, intent(in), dimension(num_tile) :: istart2, iend2, jstart2, jend2
  !  integer, intent(in) :: pe_start(num_tile)
  !  integer, intent(in) :: pe_end(num_tile)
  !  integer, intent(in) :: whalo, ehalo, shalo, nhalo
  !  integer, intent(in) :: xextent(:,:)
  !  
  !
  !end subroutine cfms_define_mosaic
  
  !> call mpp_define_domain
  subroutine cfms_define_domains2D(global_indices, layout, domain_id, pelist,   &
       xflags, yflags, xhalo, yhalo, xextent, yextent, maskmap, name_c,         &
       symmetry, memory_size, whalo, ehalo, shalo, nhalo, is_mosaic, tile_count,&
       tile_id, complete, x_cyclic_offset, y_cyclic_offset) bind(C, name="cfms_define_domains2D")

    implicit none
    
    integer, intent(in) :: global_indices(4) 
    integer, intent(in) :: layout(2)
    integer, intent(in), optional :: domain_id
    integer, intent(in), optional :: pelist(npes) 
    integer, intent(in), optional :: xflags, yflags
    integer, intent(in), optional :: xhalo, yhalo
    integer, intent(in), optional :: xextent(layout(1)), yextent(layout(2))
    logical, intent(in), optional :: maskmap(layout(1),layout(2))
    character(c_char), intent(in), optional :: name_c(NAME_LENGTH)
    logical, intent(in), optional :: symmetry
    integer, intent(in), optional :: memory_size(2)
    integer, intent(in), optional :: whalo, ehalo, shalo, nhalo
    logical, intent(in), optional :: is_mosaic
    integer, intent(in), optional :: tile_count
    integer, intent(in), optional :: tile_id
    logical, intent(in), optional :: complete
    integer, intent(in), optional :: x_cyclic_offset
    integer, intent(in), optional :: y_cyclic_offset

    character(len=20) :: name_f = input_nml_path

    if(present(name_c)) name_f = fms_string_utils_c2f_string(name_c)

    call cfms_set_current_domain(domain_id)    
    call fms_mpp_domains_define_domains(global_indices, layout, current_domain,                           &
         pelist, xflags, yflags, xhalo, yhalo, xextent, yextent, maskmap, name_f, symmetry,  memory_size, &
         whalo, ehalo, shalo, nhalo, is_mosaic, tile_count, tile_id, complete, x_cyclic_offset, y_cyclic_offset)

  end subroutine cfms_define_domains2D


  subroutine cfms_define_io_domain2D(io_layout, domain_id) bind(C)

    implicit none
    integer, intent(in) :: io_layout(2)
    integer, intent(in), optional :: domain_id

    call cfms_set_current_domain(domain_id)
    call fms_mpp_domains_define_io_domain(current_domain, io_layout)

  end subroutine cfms_define_io_domain2D


  subroutine cfms_set_compute_domain2D(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, &
                                       x_is_global, y_is_global, tile_count) bind(C)
    
    implicit none

    integer, intent(in), optional :: domain_id
    integer, intent(in), optional :: xbegin, xend, ybegin, yend, xsize, ysize
    logical, intent(in), optional :: x_is_global, y_is_global
    integer, intent(in), optional :: tile_count

    call cfms_set_current_domain(domain_id)
    call fms_mpp_domains_set_compute_domain(current_domain, xbegin, xend, ybegin, yend, xsize, ysize, &
                                            x_is_global, y_is_global, tile_count)

  end subroutine cfms_set_compute_domain2D


  subroutine cfms_set_data_domain2D(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, &
                                    x_is_global, y_is_global, tile_count) bind(C)
 
    implicit none

    integer, intent(in), optional :: domain_id
    integer, intent(in), optional :: xbegin, xend, ybegin, yend, xsize, ysize
    logical, intent(in), optional :: x_is_global, y_is_global
    integer, intent(in), optional :: tile_count
    
    call cfms_set_current_domain(domain_id)
    call fms_mpp_domains_set_data_domain(current_domain, xbegin, xend, ybegin, yend, xsize, ysize, &
                                         x_is_global, y_is_global, tile_count)

  end subroutine cfms_set_data_domain2D


  subroutine cfms_set_global_domain2D(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, tile_count) bind(C)

    implicit none

    integer, intent(in), optional :: domain_id
    integer, intent(in), optional :: xbegin, xend, ybegin, yend, xsize, ysize
    integer, intent(in), optional :: tile_count

    call cfms_set_current_domain(domain_id)
    call fms_mpp_domains_set_global_domain(current_domain, xbegin, xend, ybegin, yend, &
                                           xsize, ysize, tile_count)

  end subroutine cfms_set_global_domain2D
  

  subroutine cfms_define_nest_domain(num_nest, nest_level, tile_fine, tile_coarse,                               &
                                     istart_coarse, icount_coarse, jstart_coarse, jcount_coarse, npes_nest_tile, &
                                     x_refine, y_refine, domain_id, extra_halo, name_ptr) bind(C)

    implicit none

    integer, intent(in) :: num_nest
    integer, intent(in) :: nest_level(num_nest)
    integer, intent(in) :: tile_fine(num_nest)
    integer, intent(in) :: tile_coarse(num_nest)
    integer, intent(in) :: istart_coarse(num_nest)
    integer, intent(in) :: icount_coarse(num_nest)
    integer, intent(in) :: jstart_coarse(num_nest)
    integer, intent(in) :: jcount_coarse(num_nest)
    integer, intent(in) :: npes_nest_tile(num_nest) !fix this
    integer, intent(in) :: x_refine(num_nest)
    integer, intent(in) :: y_refine(num_nest)
    integer, intent(in), optional :: domain_id
    integer, intent(in), optional :: extra_halo
    type(c_ptr), intent(in), optional :: name_ptr

    character(100) :: name = "nest"    
    
    if(present(name_ptr)) name = fms_string_utils_c2f_string(name_ptr)

    call cfms_set_current_domain(domain_id)
    call fms_mpp_domains_define_nest_domains(nest_domain, current_domain, num_nest, nest_level, &
         tile_fine, tile_coarse, istart_coarse, icount_coarse, jstart_coarse, jcount_coarse, npes_nest_tile,&
         x_refine, y_refine, extra_halo, name)
    
  end subroutine cfms_define_nest_domain
  
end module cfms_mod
