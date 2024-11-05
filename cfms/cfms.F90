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
module cFMS_mod

  use FMS, only : fms_init, fms_end, fms_mpp_domains_init
  use FMS, only : fms_string_utils_c2f_string, fms_string_utils_f2c_string

  use FMS, only : fms_mpp_error, NOTE, WARNING, FATAL

  use FMS, only : FmsMppDomain2D, FmsMppDomainsNestDomain_type
  use FMS, only : fms_mpp_domains_get_domain_name, fms_mpp_domains_get_pelist, fms_mpp_domains_get_layout
  use FMS, only : fms_mpp_domains_domain_is_initialized
  use FMS, only : fms_mpp_domains_define_domains, fms_mpp_domains_define_io_domain 
  use FMS, only : fms_mpp_domains_set_compute_domain, fms_mpp_domains_set_data_domain, fms_mpp_domains_set_global_domain
  use FMS, only : fms_mpp_domains_define_nest_domains

  use platform_mod, only : FMS_PATH_LEN
  
  use iso_c_binding

  implicit none
  private
  
  public :: cFMS_init, cFMS_end, cFMS_error, cFMS_set_npes
  public :: cFMS_define_domains, cFMS_define_io_domain
  public :: cFMS_set_compute_domain, cFMS_set_data_domain, cFMS_set_global_domain
  public :: cFMS_define_nest_domain
  public :: cFMS_get_domain_name, cFMS_get_domain_pelist, cFMS_get_domain_layout
  public :: cFMS_domain_is_initialized

  public :: cFMS_set_current_domain
  
  integer, parameter :: NAME_LENGTH = 64 !< value taken from mpp_domains
  integer, parameter :: MESSAGE_LENGTH=128
  character(FMS_PATH_LEN), parameter :: input_nml_path="./input.nml"

  integer, public, bind(c, name="NOTE")    :: NOTE_C = NOTE
  integer, public, bind(c, name="WARNING") :: WARNING_C = WARNING
  integer, public, bind(c, name="FATAL")   :: FATAL_C = FATAL
  
  type(FmsMppDomain2D), allocatable, target,  public :: domain(:)
  type(FmsMppDomain2D), pointer :: current_domain
  
  type(FmsMppDomainsNestDomain_type), public :: nest_domain

  integer :: npes
  
contains

  !> cFMS_set_current_domain
  subroutine cFMS_set_current_domain(domain_id)

    implicit none
    integer, intent(in), optional :: domain_id
    
    if(present(domain_id)) then
       current_domain => domain(domain_id)
    else
       current_domain => domain(1)
    end if
    
  end subroutine cFMS_set_current_domain
  
  !> cFMS_set_npes
  subroutine cFMS_set_npes(npes_in) bind(C, name="cFMS_set_npes")
    implicit none
    integer, intent(in) :: npes_in
    npes = npes_in
  end subroutine cFMS_set_npes


  !> cFMS_init
  subroutine cFMS_init(localcomm, alt_input_nml_path_ptr, ndomain) bind(C, name="cFMS_init")

    implicit none
    integer, intent(in), optional :: localcomm
    integer, intent(in), optional :: ndomain
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

  end subroutine cFMS_init


  !> cFMS_end
  subroutine cFMS_end() bind(C, name="cFMS_end")
    implicit none
    call fms_end()
  end subroutine cFMS_end
  

  !> cFMS_error
  subroutine cFMS_error(errortype, errormsg_c) bind(C, name="cFMS_error")
    
    implicit none
    integer, intent(in), value :: errortype
    character(c_char), intent(in), optional :: errormsg_c(MESSAGE_LENGTH)
    character(len=MESSAGE_LENGTH) :: errormsg_f

    if(present(errormsg_c)) errormsg_f = fms_string_utils_c2f_string(errormsg_c)
    call fms_mpp_error(errortype, trim(errormsg_f))
    
  end subroutine cFMS_error
  
  
  !> call mpp_define_domain
  subroutine cFMS_define_domains(global_indices, layout, domain_id, pelist,   &
       xflags, yflags, xhalo, yhalo, xextent, yextent, maskmap, name_c,         &
       symmetry, memory_size, whalo, ehalo, shalo, nhalo, is_mosaic, tile_count,&
       tile_id, complete, x_cyclic_offset, y_cyclic_offset) bind(C, name="cFMS_define_domains")

    implicit none   
    integer, intent(in) :: global_indices(4) 
    integer, intent(in) :: layout(2)
    integer, intent(in),  optional :: domain_id
    integer, intent(in), optional :: pelist(npes) 
    integer, intent(in),  optional :: xflags, yflags
    integer, intent(in),  optional :: xhalo, yhalo
    integer, intent(in), optional :: xextent(layout(1)), yextent(layout(2))
    logical, intent(in), optional :: maskmap(layout(1),layout(2))
    character(c_char), intent(in), optional :: name_c(NAME_LENGTH)
    logical, intent(in),  optional :: symmetry
    integer, intent(in), optional :: memory_size(2)
    integer, intent(in),  optional :: whalo, ehalo, shalo, nhalo
    logical, intent(in),  optional :: is_mosaic
    integer, intent(in),  optional :: tile_count
    integer, intent(in),  optional :: tile_id
    logical, intent(in),  optional :: complete
    integer, intent(in),  optional :: x_cyclic_offset
    integer, intent(in),  optional :: y_cyclic_offset

    character(len=NAME_LENGTH) :: name_f = "domain"

    if(present(name_c)) name_f = fms_string_utils_c2f_string(name_c)

    call cFMS_set_current_domain(domain_id)    
    call fms_mpp_domains_define_domains(global_indices, layout, current_domain,                           &
         pelist, xflags, yflags, xhalo, yhalo, xextent, yextent, maskmap, name_f, symmetry,  memory_size, &
         whalo, ehalo, shalo, nhalo, is_mosaic, tile_count, tile_id, complete, x_cyclic_offset, y_cyclic_offset)

  end subroutine cFMS_define_domains


  !> cFMS_define_io_domain
  subroutine cFMS_define_io_domain(io_layout, domain_id) bind(C, name="cFMS_define_io_domain")

    implicit none
    integer, intent(in) :: io_layout(2)
    integer, intent(in),  optional :: domain_id

    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_define_io_domain(current_domain, io_layout)

  end subroutine cFMS_define_io_domain


  !>cFMS_set_compute_domain
  subroutine cFMS_set_compute_domain(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, &
                                     x_is_global, y_is_global, tile_count) bind(C, name="cFMS_set_compute_domain")
    
    implicit none
    integer, intent(in),  optional :: domain_id
    integer, intent(in),  optional :: xbegin, xend, ybegin, yend, xsize, ysize
    logical, intent(in),  optional :: x_is_global, y_is_global
    integer, intent(in),  optional :: tile_count

    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_set_compute_domain(current_domain, xbegin, xend, ybegin, yend, xsize, ysize, &
                                            x_is_global, y_is_global, tile_count)

  end subroutine cFMS_set_compute_domain


  !> cFMS_set_data_domain
  subroutine cFMS_set_data_domain(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, &
                                  x_is_global, y_is_global, tile_count) bind(C, name="cFMS_set_data_domain")
 
    implicit none
    integer, intent(in),  optional :: domain_id
    integer, intent(in),  optional :: xbegin, xend, ybegin, yend, xsize, ysize
    logical, intent(in),  optional :: x_is_global, y_is_global
    integer, intent(in),  optional :: tile_count
    
    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_set_data_domain(current_domain, xbegin, xend, ybegin, yend, xsize, ysize, &
                                         x_is_global, y_is_global, tile_count)

  end subroutine cFMS_set_data_domain


  !> cFMS_set_global_domain
  subroutine cFMS_set_global_domain(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, tile_count) &
                                                              bind(C, name="cFMS_set_global_domain")
    implicit none
    integer, intent(in),  optional :: domain_id
    integer, intent(in),  optional :: xbegin, xend, ybegin, yend, xsize, ysize
    integer, intent(in),  optional :: tile_count

    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_set_global_domain(current_domain, xbegin, xend, ybegin, yend, &
                                           xsize, ysize, tile_count)

  end subroutine cFMS_set_global_domain
  

  !> cFMS_define_nest_domain
  subroutine cFMS_define_nest_domain(num_nest, nest_level, tile_fine, tile_coarse,                               &
                                     istart_coarse, icount_coarse, jstart_coarse, jcount_coarse, npes_nest_tile, &
                                     x_refine, y_refine, domain_id, extra_halo, name_ptr)                        &
                                                                            bind(C, name="cFMS_define_nest_domain")

    implicit none
    integer, intent(in), value :: num_nest
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
    integer, intent(in),  optional :: domain_id
    integer, intent(in),  optional :: extra_halo
    type(c_ptr), intent(in), optional :: name_ptr

    character(100) :: name = "nest"    
    
    if(present(name_ptr)) name = fms_string_utils_c2f_string(name_ptr)

    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_define_nest_domains(nest_domain, current_domain, num_nest, nest_level, &
         tile_fine, tile_coarse, istart_coarse, icount_coarse, jstart_coarse, jcount_coarse, npes_nest_tile,&
         x_refine, y_refine, extra_halo, name)
    
  end subroutine cFMS_define_nest_domain

  !> cFMS_get_domain_name
  subroutine cFMS_get_domain_name(domain_name_c, domain_id) bind(C, name="cFMS_get_domain_name")

    implicit none
    character(kind=c_char), intent(out) :: domain_name_c(NAME_LENGTH)
    integer, intent(in),  optional :: domain_id
    character(len=NAME_LENGTH) :: domain_name_f
    
    call cFMS_set_current_domain(domain_id)
    domain_name_f = fms_mpp_domains_get_domain_name(current_domain)
    call fms_string_utils_f2c_string(domain_name_c, domain_name_f)
    
  end subroutine cFMS_get_domain_name

  !> cFMS_get_pelist
  subroutine cFMS_get_domain_pelist(pelist, domain_id, pos) bind(C, name="cFMS_get_domain_pelist")

    implicit none
    integer, intent(out) :: pelist(npes)
    integer, intent(in),  optional :: domain_id
    integer, intent(out), optional :: pos

    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_get_pelist(current_domain, pelist, pos)

  end subroutine cFMS_get_domain_pelist


  subroutine cFMS_get_domain_layout(layout, domain_id) bind(C, name="cFMS_get_domain_layout")

    implicit none
    integer, intent(out) :: layout(2)
    integer, intent(in),  optional :: domain_id

    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_get_layout(current_domain, layout)

  end subroutine cFMS_get_domain_layout


  function cFMS_domain_is_initialized(domain_id) bind(C, name="cFMS_domain_is_initialized")

    implicit none
    integer, intent(in), optional :: domain_id
    logical :: cFMS_domain_is_initialized

    call cFMS_set_current_domain(domain_id)
    cFMS_domain_is_initialized = fms_mpp_domains_domain_is_initialized(current_domain)

  end function cFMS_domain_is_initialized
  
  
end module cFMS_mod
