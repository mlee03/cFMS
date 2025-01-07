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
  
  !> cFMS_calls mpp_define_domains2D to define the domain with id=domain_id.  Domain_id must be
  !! an integer.  This wrapper assumes C indexing convention where array indexing starts from 0
  module subroutine cFMS_define_domains(global_indices, layout, domain_id, pelist, &
       xflags, yflags, xhalo, yhalo, xextent, yextent, maskmap, name,              &
       symmetry, memory_size, whalo, ehalo, shalo, nhalo, is_mosaic, tile_count,   &
       tile_id, complete, x_cyclic_offset, y_cyclic_offset) bind(C, name="cFMS_define_domains")

    implicit none   
    integer, intent(inout) :: global_indices(4) 
    integer, intent(in) :: layout(2)
    integer, intent(in), optional :: domain_id
    integer, intent(in), optional :: pelist(npes) 
    integer, intent(in), optional :: xflags, yflags
    integer, intent(in), optional :: xhalo, yhalo
    integer, intent(in), optional :: xextent(layout(1)), yextent(layout(2))
    type(c_ptr), intent(in), optional :: maskmap
    character(c_char), intent(in), optional :: name(NAME_LENGTH)
    logical(c_bool), intent(in), optional :: symmetry
    integer, intent(in), optional :: memory_size(2)
    integer, intent(in), optional :: whalo, ehalo, shalo, nhalo
    logical(c_bool), intent(in), optional :: is_mosaic
    integer, intent(inout), optional :: tile_count
    integer, intent(inout), optional :: tile_id
    logical(c_bool), intent(in), optional :: complete
    integer, intent(in), optional :: x_cyclic_offset
    integer, intent(in), optional :: y_cyclic_offset
    
    character(len=NAME_LENGTH) :: name_f = "cdomain"
    integer :: global_indices_f(4)
    logical(c_bool), pointer :: maskmap_f(:,:) => NULL()
    logical :: symmetry_f  = .False.
    logical :: is_mosaic_f = .False.
    logical :: complete_f  = .True.
    logical :: dealloc_maskmap = .False.
    
    global_indices_f = global_indices + 1

    if(present(tile_id))    tile_id = tile_id + 1;
    if(present(tile_count)) tile_count = tile_count + 1;
    if(present(name))       name_f = fms_string_utils_c2f_string(name)
    if(present(symmetry))   symmetry_f = logical(symmetry)
    if(present(is_mosaic))  is_mosaic_f = logical(is_mosaic)
    if(present(complete))   complete_f = logical(complete)

    nullify(maskmap_f)
    if(present(maskmap)) then
       call c_f_pointer(maskmap, maskmap_f, (/layout(2), layout(1)/))
       maskmap_f = reshape(maskmap_f, shape=(/layout(1), layout(2)/))
    else
       allocate(maskmap_f(layout(1), layout(2)))
       maskmap_f = .True.
       dealloc_maskmap = .True.
    end if

    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_define_domains(global_indices_f, layout, current_domain, pelist=pelist,  &
         xflags=xflags, yflags=yflags, xhalo=xhalo, yhalo=yhalo, xextent=xextent, yextent=yextent,&
         maskmap=logical(maskmap_f), name=name_f, symmetry=symmetry_f, memory_size=memory_size,            &
         whalo=whalo, ehalo=ehalo, shalo=shalo, nhalo=nhalo, is_mosaic=is_mosaic_f, tile_count=tile_count, &
         tile_id=tile_id, complete=complete_f, x_cyclic_offset=x_cyclic_offset, y_cyclic_offset=y_cyclic_offset)

    if(present(tile_id))    tile_id = tile_id - 1;
    if(present(tile_count)) tile_count = tile_count - 1;

    if(dealloc_maskmap) deallocate(maskmap_f)
    nullify(maskmap_f)
    
  end subroutine cFMS_define_domains


  !> cFMS_define_io_domain
  module subroutine cFMS_define_io_domain(io_layout, domain_id) bind(C, name="cFMS_define_io_domain")
    
    implicit none
    integer, intent(in) :: io_layout(2)
    integer, intent(in), optional :: domain_id
    
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
  

  !> cFMS_define_nest_domain calls mpp_define_nest_domains to define the nest domain with id=nest_domain_id.
  !! Nest_domain_id must be an integer.  This wrapper assumes C indexing convention where array indexing starts from 0  
  module subroutine cFMS_define_nest_domains(num_nest, ntiles, nest_level, tile_fine, tile_coarse,               &
                                     istart_coarse, icount_coarse, jstart_coarse, jcount_coarse, npes_nest_tile, &
                                     x_refine, y_refine, nest_domain_id, domain_id, extra_halo, name)            &
                                                                            bind(C, name="cFMS_define_nest_domains")

    implicit none
    integer, intent(in) :: num_nest
    integer, intent(in) :: ntiles
    integer, intent(in) :: nest_level(num_nest)
    integer, intent(in) :: tile_fine(num_nest)
    integer, intent(in) :: tile_coarse(num_nest)
    integer, intent(in) :: istart_coarse(num_nest)
    integer, intent(in) :: icount_coarse(num_nest)
    integer, intent(in) :: jstart_coarse(num_nest)
    integer, intent(in) :: jcount_coarse(num_nest)
    integer, intent(in) :: npes_nest_tile(ntiles)
    integer, intent(in) :: x_refine(num_nest)
    integer, intent(in) :: y_refine(num_nest)
    integer, intent(in),  optional :: nest_domain_id, domain_id
    integer, intent(in),  optional :: extra_halo
    character(c_char), intent(in), optional :: name(NAME_LENGTH)

    integer :: istart_coarse_f(num_nest), jstart_coarse_f(num_nest)
    integer :: tile_fine_f(num_nest), tile_coarse_f(num_nest)
    character(100) :: name_f = "cnest_domain"    

    istart_coarse_f = istart_coarse + 1
    jstart_coarse_f = jstart_coarse + 1
    tile_fine_f     = tile_fine + 1
    tile_coarse_f   = tile_coarse + 1
    if(present(name)) name_f = fms_string_utils_c2f_string(name)
    
    call cFMS_set_current_nest_domain(nest_domain_id)
    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_define_nest_domains(current_nest_domain, current_domain, num_nest, nest_level,             &
         tile_fine_f, tile_coarse_f, istart_coarse_f, icount_coarse, jstart_coarse_f, jcount_coarse, npes_nest_tile,&
         x_refine, y_refine, extra_halo=extra_halo, name=name_f)
    
  end subroutine cFMS_define_nest_domains


  function cFMS_domain_is_initialized(domain_id) bind(C, name="cFMS_domain_is_initialized")

    implicit none
    integer, intent(in), optional :: domain_id
    logical(c_bool) :: cFMS_domain_is_initialized

    call cFMS_set_current_domain(domain_id)
    cFMS_domain_is_initialized = logical(fms_mpp_domains_domain_is_initialized(current_domain), kind=c_bool)

  end function cFMS_domain_is_initialized


  !> cFMS_get_compute_domain
  module subroutine cFMS_get_compute_domain(domain_id, xbegin, xend, ybegin, yend, xsize, xmax_size, ysize, ymax_size, &
       x_is_global, y_is_global, tile_count, position, whalo, shalo) bind(C, name="cFMS_get_compute_domain")
    
    implicit none
    integer, intent(in),  optional :: domain_id
    integer, intent(out), optional :: xbegin, xend, ybegin, yend
    integer, intent(out), optional :: xsize, xmax_size, ysize, ymax_size
    logical(c_bool), intent(out), optional :: x_is_global, y_is_global
    integer, intent(inout), optional :: tile_count
    integer, intent(in),  optional :: position
    integer, intent(in),  optional :: whalo, shalo

    integer :: xshift = 0, yshift = 0
    logical :: x_is_global_f, y_is_global_f
    
    if(present(tile_count)) tile_count = tile_count + 1
    if(present(whalo)) xshift = whalo 
    if(present(shalo)) yshift = shalo 
    
    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_get_compute_domain(current_domain, xbegin=xbegin, xend=xend, ybegin=ybegin, yend=yend, &
                                            xsize=xsize, xmax_size=xmax_size, ysize=ysize, ymax_size=ymax_size, &
                                            x_is_global=x_is_global_f, y_is_global=y_is_global_f, &
                                            tile_count=tile_count, position=position)

    if(present(xbegin)) xbegin = xbegin + xshift - 1
    if(present(xend))   xend   = xend   + xshift - 1 
    if(present(ybegin)) ybegin = ybegin + yshift - 1 
    if(present(yend))   yend   = yend   + yshift - 1    
    if(present(tile_count)) tile_count = tile_count - 1
    if(present(x_is_global)) x_is_global = logical(x_is_global_f, kind=c_bool)
    if(present(y_is_global)) y_is_global = logical(y_is_global_f, kind=c_bool)
    
  end subroutine cFMS_get_compute_domain


  !> cFMS_get_data_domain
  module subroutine cFMS_get_data_domain(domain_id, xbegin, xend, ybegin, yend, xsize, xmax_size, ysize, ymax_size, &
       x_is_global, y_is_global, tile_count, position, whalo, shalo) bind(C, name="cFMS_get_data_domain")
    
    implicit none
    integer, intent(in),  optional :: domain_id
    integer, intent(out), optional :: xbegin, xend, ybegin, yend
    integer, intent(out), optional :: xsize, xmax_size, ysize, ymax_size
    logical(c_bool), intent(out), optional :: x_is_global, y_is_global
    integer, intent(inout), optional :: tile_count
    integer, intent(in), optional  :: position
    integer, intent(in), optional  :: whalo, shalo

    integer :: xshift = 0, yshift = 0
    logical :: x_is_global_f, y_is_global_f
    
    if(present(tile_count)) tile_count = tile_count + 1
    if(present(whalo)) xshift = whalo
    if(present(shalo)) yshift = shalo    
    
    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_get_data_domain(current_domain, xbegin=xbegin, xend=xend, ybegin=ybegin, yend=yend, &
         xsize=xsize, xmax_size=xmax_size, ysize=ysize, ymax_size=ymax_size, x_is_global=x_is_global_f,      &
         y_is_global=y_is_global_f, tile_count=tile_count, position=position)
        
    if(present(xbegin)) xbegin = xbegin + xshift - 1 
    if(present(xend))   xend   = xend   + xshift - 1    
    if(present(ybegin)) ybegin = ybegin + yshift - 1 
    if(present(yend))   yend   = yend   + yshift - 1 
    if(present(tile_count)) tile_count = tile_count - 1
    if(present(x_is_global)) x_is_global = logical(x_is_global,kind=4)
    if(present(y_is_global)) y_is_global = logical(y_is_global,kind=4)
    
  end subroutine cFMS_get_data_domain


  !> cFMS_get_domain_name
  module subroutine cFMS_get_domain_name(domain_name_c, domain_id) bind(C, name="cFMS_get_domain_name")
    
    implicit none
    character(c_char), intent(out) :: domain_name_c(NAME_LENGTH)
    integer, intent(in),  optional :: domain_id
    character(len=NAME_LENGTH) :: domain_name_f
    
    call cFMS_set_current_domain(domain_id)
    domain_name_f = fms_mpp_domains_get_domain_name(current_domain)

    call fms_string_utils_f2c_string(domain_name_c, domain_name_f)
    
  end subroutine cFMS_get_domain_name


  module subroutine cFMS_get_layout(layout, domain_id) bind(C, name="cFMS_get_layout")
    
    implicit none
    integer, intent(out) :: layout(2)
    integer, intent(in),  optional :: domain_id

    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_get_layout(current_domain, layout)

  end subroutine cFMS_get_layout


  !> cFMS_get_pelist
  module subroutine cFMS_get_domain_pelist(pelist, domain_id) bind(C, name="cFMS_get_domain_pelist")
    
    implicit none
    integer, intent(out) :: pelist(npes)
    integer, intent(in),  optional :: domain_id
    
    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_get_pelist(current_domain, pelist)
    
  end subroutine cFMS_get_domain_pelist

    
  !>cFMS_set_compute_domain
  module subroutine cFMS_set_compute_domain(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, &
       x_is_global, y_is_global, tile_count, whalo, shalo) bind(C, name="cFMS_set_compute_domain")
    
    implicit none
    integer, intent(in),    optional :: domain_id
    integer, intent(inout), optional :: xbegin, xend, ybegin, yend, xsize, ysize
    logical(c_bool), intent(inout), optional :: x_is_global, y_is_global
    integer, intent(inout), optional :: tile_count
    integer, intent(in),    optional :: whalo, shalo

    integer :: xshift = 0, yshift = 0
    
    if(present(whalo)) xshift = whalo
    if(present(shalo)) yshift = shalo
    
    if(present(xbegin)) xbegin = xbegin - xshift + 1
    if(present(xend))   xend   = xend   - xshift + 1
    if(present(ybegin)) ybegin = ybegin - yshift + 1
    if(present(yend))   yend   = yend   - yshift + 1    
    if(present(tile_count)) tile_count = tile_count + 1

    call cFMS_set_current_domain(domain_id)

    if(present(x_is_global)) then
       if(present(y_is_global)) then
          call fms_mpp_domains_set_compute_domain(domain=current_domain, xbegin=xbegin, xend=xend,&
               tile_count=tile_count, ybegin=ybegin, yend=yend, xsize=xsize, ysize=ysize,         &
               x_is_global=logical(x_is_global), y_is_global=logical(y_is_global))
       else
          call fms_mpp_domains_set_compute_domain(domain=current_domain, xbegin=xbegin, xend=xend,&
               tile_count=tile_count, ybegin=ybegin, yend=yend, xsize=xsize, ysize=ysize,         &
               x_is_global=logical(x_is_global))
       end if
    else if(present(y_is_global)) then
       call fms_mpp_domains_set_compute_domain(domain=current_domain, xbegin=xbegin, xend=xend,&
            tile_count=tile_count, ybegin=ybegin, yend=yend, xsize=xsize, ysize=ysize,         &
            y_is_global=logical(y_is_global))
    else
       call fms_mpp_domains_set_compute_domain(domain=current_domain, xbegin=xbegin, xend=xend,&
            tile_count=tile_count, ybegin=ybegin, yend=yend, xsize=xsize, ysize=ysize)
    end if

    if(present(xbegin)) xbegin = xbegin + xshift - 1
    if(present(xend))   xend   = xend   + xshift - 1
    if(present(ybegin)) ybegin = ybegin + yshift - 1
    if(present(yend))   yend   = yend   + yshift - 1
    if(present(tile_count)) tile_count = tile_count - 1


  end subroutine cFMS_set_compute_domain
 
  
  !> cFMS_set_current_domain sets the domain to the current_domain where the
  !! current_domain has id=domain_id
  module subroutine cFMS_set_current_domain(domain_id)

    implicit none
    integer, intent(in), optional :: domain_id
    
    if(present(domain_id)) then
       current_domain => domain(domain_id)
    else
       current_domain => domain(0)
    end if
    
  end subroutine cFMS_set_current_domain


  !> cFMS_set_current_nest_domain sets the nest_domain to the current_nest_domain
  !! where the current_nest_domain has id=nest_domain_id  
  module subroutine cFMS_set_current_nest_domain(nest_domain_id)

    implicit none
    integer, intent(in), optional :: nest_domain_id
    
    if(present(nest_domain_id)) then
       current_nest_domain => nest_domain(nest_domain_id)
    else
       current_nest_domain => nest_domain(0)
    end if
    
  end subroutine cFMS_set_current_nest_domain


  !> cFMS_set_data_domain
  module subroutine cFMS_set_data_domain(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, &
       x_is_global, y_is_global, tile_count, whalo, shalo) bind(C, name="cFMS_set_data_domain")
    
    implicit none
    integer, intent(in),    optional :: domain_id
    integer, intent(inout), optional :: xbegin, xend, ybegin, yend, xsize, ysize
    logical(c_bool), intent(in),    optional :: x_is_global, y_is_global
    integer, intent(inout), optional :: tile_count
    integer, intent(in),    optional :: whalo, shalo
   
    integer :: yshift = 0, xshift = 0
    
    if(present(whalo)) xshift = whalo
    if(present(shalo)) yshift = shalo

    if(present(xbegin)) xbegin = xbegin - xshift + 1
    if(present(xend))   xend   = xend   - xshift + 1
    if(present(ybegin)) ybegin = ybegin - yshift + 1
    if(present(yend))   yend   = yend   - yshift + 1
    if(present(tile_count)) tile_count = tile_count + 1

    !simply way to avoid converting logicals from c_bool to kind=4.  The program will always send in
    ! x_is_global and y_is_global
    call cFMS_set_current_domain(domain_id)

    if(present(x_is_global)) then
       if(present(y_is_global)) then
          call fms_mpp_domains_set_data_domain(current_domain, xbegin=xbegin, xend=xend, ybegin=ybegin, yend=yend, &
               xsize=xsize, ysize=ysize, x_is_global=logical(x_is_global), y_is_global=logical(y_is_global),       &
               tile_count=tile_count)
       else
          call fms_mpp_domains_set_data_domain(current_domain, xbegin=xbegin, xend=xend, ybegin=ybegin, yend=yend, &
               xsize=xsize, ysize=ysize, x_is_global=logical(x_is_global), tile_count=tile_count)
       end if
    else if(present(y_is_global)) then
       call fms_mpp_domains_set_data_domain(current_domain, xbegin=xbegin, xend=xend, ybegin=ybegin, yend=yend, &
            xsize=xsize, ysize=ysize, y_is_global=logical(y_is_global), tile_count=tile_count)
    else
       call fms_mpp_domains_set_data_domain(current_domain, xbegin=xbegin, xend=xend, ybegin=ybegin, yend=yend, &
            xsize=xsize, ysize=ysize, tile_count=tile_count)
    end if

    if(present(xbegin)) xbegin = xbegin + xshift - 1
    if(present(xend))   xend   = xend   + xshift - 1
    if(present(ybegin)) ybegin = ybegin + yshift - 1
    if(present(yend))   yend   = yend   + yshift - 1
    if(present(tile_count)) tile_count = tile_count - 1
    
  end subroutine cFMS_set_data_domain


  !> cFMS_set_global_domain
  module subroutine cFMS_set_global_domain(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, tile_count, &
                                           whalo, shalo) bind(C, name="cFMS_set_global_domain")
    implicit none
    integer, intent(in),    optional :: domain_id
    integer, intent(inout), optional :: xbegin, xend, ybegin, yend, xsize, ysize
    integer, intent(inout), optional :: tile_count
    integer, intent(in),    optional :: whalo, shalo
    
    integer :: xshift = 0, yshift = 0

    if(present(whalo)) xshift = whalo
    if(present(shalo)) yshift = shalo

    if(present(xbegin)) xbegin = xbegin - xshift + 1
    if(present(xend))   xend   = xend   - xshift + 1    
    if(present(ybegin)) ybegin = ybegin - yshift + 1
    if(present(yend))   yend   = yend   - yshift + 1
    if(present(tile_count)) tile_count = tile_count + 1
    
    call cFMS_set_current_domain(domain_id)
    call fms_mpp_domains_set_global_domain(current_domain, xbegin=xbegin, xend=xend, ybegin=ybegin, yend=yend, &
                                           xsize=xsize, ysize=ysize, tile_count=tile_count)

    if(present(xbegin)) xbegin = xbegin + xshift - 1
    if(present(xend))   xend   = xend   + xshift - 1    
    if(present(ybegin)) ybegin = ybegin + yshift - 1
    if(present(yend))   yend   = yend   + yshift - 1
    if(present(tile_count)) tile_count = tile_count - 1
   
  end subroutine cFMS_set_global_domain
  
  !> cFMS_update_domains
#include "cmpp_domains.fh"
  
end submodule cmpp_domains_smod
