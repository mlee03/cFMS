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
submodule(cfms_mod) cmpp_domains_smod
  
  implicit none

contains
  
  !> call mpp_define_domain
  module subroutine cFMS_define_domains(global_indices, layout, domain_id, pelist,     &
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
  module subroutine cFMS_define_io_domain(io_layout, domain_id) bind(C, name="cFMS_define_io_domain")
    
    implicit none
    integer, intent(in) :: io_layout(2)
    integer, intent(in),  optional :: domain_id
    
    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_define_io_domain(current_domain, io_layout)
    
  end subroutine cFMS_define_io_domain

  !> cFMS_define_layout
  module subroutine cFMS_define_layout(global_indices, ndivs, layout) bind(C, name="cFMS_define_layout")
    
    implicit none
    integer, intent(in) :: global_indices(4)
    integer, intent(in) :: ndivs
    integer, intent(out) :: layout(2)

    call fms_mpp_domains_define_layout(global_indices, ndivs, layout)
    
  end subroutine cFMS_define_layout
  

  !> cFMS_define_nest_domain
  module subroutine cFMS_define_nest_domain(num_nest, nest_level, tile_fine, tile_coarse,                               &
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


  function cFMS_domain_is_initialized(domain_id) bind(C, name="cFMS_domain_is_initialized")

    implicit none
    integer, intent(in), optional :: domain_id
    logical :: cFMS_domain_is_initialized

    call cFMS_set_current_domain(domain_id)
    cFMS_domain_is_initialized = fms_mpp_domains_domain_is_initialized(current_domain)

  end function cFMS_domain_is_initialized


  !> cFMS_get_domain_name
  module subroutine cFMS_get_domain_name(domain_name_c, domain_id) bind(C, name="cFMS_get_domain_name")
    
    implicit none
    type(c_ptr) , intent(out) :: domain_name_c
    integer, intent(in),  optional :: domain_id
    character(len=NAME_LENGTH) :: domain_name_f
    character(kind=c_char), allocatable, target :: domain_name_cstring(:)

    character(kind=c_char), target :: tmp
    
    call cFMS_set_current_domain(domain_id)
    domain_name_f = fms_mpp_domains_get_domain_name(current_domain)

    allocate(domain_name_cstring(len(trim(domain_name_f))+1))    
    call fms_string_utils_f2c_string(domain_name_cstring, trim(domain_name_f))
    domain_name_c = fms_string_utils_cstring2cpointer(domain_name_cstring)
    
  end subroutine cFMS_get_domain_name


  module subroutine cFMS_get_layout(layout, domain_id) bind(C, name="cFMS_get_layout")

    implicit none
    integer, intent(out) :: layout(2)
    integer, intent(in),  optional :: domain_id

    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_get_layout(current_domain, layout)

  end subroutine cFMS_get_layout

  
  !> cFMS_get_pelist
  module subroutine cFMS_get_domain_pelist(pelist, domain_id, pos) bind(C, name="cFMS_get_domain_pelist")

    implicit none
    integer, intent(out) :: pelist(npes)
    integer, intent(in),  optional :: domain_id
    integer, intent(out), optional :: pos

    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_get_pelist(current_domain, pelist, pos)

  end subroutine cFMS_get_domain_pelist


  !> cFMS_set_current_domain
  module subroutine cFMS_set_current_domain(domain_id)

    implicit none
    integer, intent(in), optional :: domain_id
    
    if(present(domain_id)) then
       current_domain => domain(domain_id)
    else
       current_domain => domain(0)
    end if
    
  end subroutine cFMS_set_current_domain
  

end submodule cmpp_domains_smod
