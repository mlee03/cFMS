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

  use FMS, only : FATAL, NOTE, WARNING
  use FMS, only : FmsMppDomain2D, FmsMppDomainsNestDomain_type
  use FMS, only : fms_init, fms_end, fms_mpp_domains_init
  use FMS, only : fms_string_utils_c2f_string, fms_string_utils_f2c_string, fms_string_utils_cstring2cpointer
  use platform_mod, only : FMS_PATH_LEN
  
  use FMS, only : fms_mpp_declare_pelist, fms_mpp_error, fms_mpp_get_current_pelist
  use FMS, only : fms_mpp_npes, fms_mpp_pe, fms_mpp_set_current_pelist

  use FMS, only : fms_mpp_domains_define_domains, fms_mpp_domains_define_io_domain, fms_mpp_domains_define_layout
  use FMS, only : fms_mpp_domains_define_nest_domains, fms_mpp_domains_domain_is_initialized
  use FMS, only : fms_mpp_domains_get_compute_domain, fms_mpp_domains_get_data_domain, fms_mpp_domains_get_domain_name
  use FMS, only : fms_mpp_domains_get_layout, fms_mpp_domains_get_pelist
  use FMS, only : fms_mpp_domains_set_compute_domain, fms_mpp_domains_set_data_domain, fms_mpp_domains_set_global_domain
  
  use iso_c_binding

  implicit none
  private

  integer, parameter :: NAME_LENGTH = 64 !< value taken from mpp_domains
  integer, parameter :: MESSAGE_LENGTH=128
  character(FMS_PATH_LEN), parameter :: input_nml_path="./input.nml"

  integer, public, bind(c, name="cFMS_pelist_npes") :: npes
  integer, public, bind(c, name="NOTE")      :: NOTE_C    = NOTE
  integer, public, bind(c, name="WARNING")   :: WARNING_C = WARNING
  integer, public, bind(c, name="FATAL")     :: FATAL_C    = FATAL
  
  type(FmsMppDomain2D), allocatable, target,  public :: domain(:)
  type(FmsMppDomain2D), pointer  :: current_domain  
  type(FmsMppDomainsNestDomain_type), public :: nest_domain
  
  interface

     module subroutine cFMS_declare_pelist(pelist, name_c, commID)
       implicit none
       integer, intent(in) :: pelist(npes)
       type(c_ptr), intent(in), optional :: name_c
       integer, intent(out), optional :: commID
     end subroutine

     !> cFMS_error
     module subroutine cFMS_error(errortype, errormsg_c) bind(C, name="cFMS_error")
       
       implicit none
       integer, intent(in), value :: errortype
       character(c_char), intent(in), optional :: errormsg_c(MESSAGE_LENGTH)
       character(len=MESSAGE_LENGTH) :: errormsg_f
     end subroutine
     
     module subroutine cFMS_get_current_pelist(pelist, name_c, commID)
       implicit none
       integer, intent(out) :: pelist(npes)
       type(c_ptr), intent(out), optional :: name_c
       integer, intent(out), optional :: commID
     end subroutine

     module function cFMS_npes()
       integer :: cFMS_npes
     end function

     module function cFMS_pe()
       integer :: cFMS_pe
     end function

     module subroutine cFMS_set_current_pelist(pelist, no_sync)
       implicit none
       integer, intent(in), optional :: pelist(npes)
       logical, intent(in), optional :: no_sync
     end subroutine

     module subroutine cFMS_define_domains(global_indices, layout, domain_id, pelist,     &
          xflags, yflags, xhalo, yhalo, xextent, yextent, maskmap, name_c,                &
          symmetry, memory_size, whalo, ehalo, shalo, nhalo, is_mosaic, tile_count,       &
          tile_id, complete, x_cyclic_offset, y_cyclic_offset)
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
     end subroutine

     module subroutine cFMS_define_io_domain(io_layout, domain_id)
       implicit none
       integer, intent(in) :: io_layout(2)
       integer, intent(in),  optional :: domain_id
     end subroutine

     module subroutine cFMS_define_layout(global_indices, ndivs, layout)
       implicit none
       integer, intent(in) :: global_indices(4)
       integer, intent(in) :: ndivs
       integer, intent(out) :: layout(2)
     end subroutine
     
     module subroutine cFMS_define_nest_domain(num_nest, nest_level, tile_fine, tile_coarse,&
          istart_coarse, icount_coarse, jstart_coarse, jcount_coarse, npes_nest_tile,       &
          x_refine, y_refine, domain_id, extra_halo, name_ptr)          
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
     end subroutine
     
     module function cFMS_domain_is_initialized(domain_id)
       implicit none
       integer, intent(in), optional :: domain_id
       logical :: cFMS_domain_is_initialized
     end function

     module subroutine cFMS_get_compute_domain(domain_id, xbegin, xend, ybegin, yend, xsize, xmax_size, &
          ysize, ymax_size, x_is_global, y_is_global, tile_count, position)
       implicit none
       integer, intent(in), optional :: domain_id
       integer, intent(out), optional :: xbegin, xend, ybegin, yend
       integer, intent(out), optional :: xsize, xmax_size, ysize, ymax_size
       logical, intent(out), optional :: x_is_global, y_is_global
       integer, intent(in), optional :: tile_count, position
     end subroutine

     module subroutine cFMS_get_data_domain(domain_id, xbegin, xend, ybegin, yend, xsize, xmax_size, ysize, ymax_size, &
          x_is_global, y_is_global, tile_count, position)
       implicit none
       integer, intent(in), optional :: domain_id
       integer, intent(out), optional :: xbegin, xend, ybegin, yend
       integer, intent(out), optional :: xsize, xmax_size, ysize, ymax_size
       logical, intent(out), optional :: x_is_global, y_is_global
       integer, intent(in), optional :: tile_count, position
     end subroutine

     module subroutine cFMS_get_domain_name(domain_name_c, domain_id)
       implicit none
       type(c_ptr) , intent(out) :: domain_name_c
       integer, intent(in),  optional :: domain_id
     end subroutine

     module subroutine cFMS_get_domain_layout(layout, domain_id)
       implicit none
       integer, intent(out) :: layout(2)
       integer, intent(in),  optional :: domain_id
     end subroutine

     module subroutine cFMS_get_domain_pelist(pelist, domain_id, pos)
       implicit none
       integer, intent(out) :: pelist(npes)
       integer, intent(in),  optional :: domain_id
       integer, intent(out), optional :: pos
     end subroutine

     module subroutine cFMS_set_compute_domain(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, &
          x_is_global, y_is_global, tile_count)
       implicit none
       integer, intent(in),  optional :: domain_id
       integer, intent(in),  optional :: xbegin, xend, ybegin, yend, xsize, ysize
       logical, intent(in),  optional :: x_is_global, y_is_global
       integer, intent(in),  optional :: tile_count
     end subroutine

     module subroutine cFMS_set_current_domain(domain_id) 
       implicit none
       integer, intent(in), optional :: domain_id
     end subroutine

     module subroutine cFMS_set_data_domain(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, &
          x_is_global, y_is_global, tile_count) 
       implicit none
       integer, intent(in),  optional :: domain_id
       integer, intent(in),  optional :: xbegin, xend, ybegin, yend, xsize, ysize
       logical, intent(in),  optional :: x_is_global, y_is_global
       integer, intent(in),  optional :: tile_count
     end subroutine

     module subroutine cFMS_set_global_domain(domain_id, xbegin, xend, ybegin, yend, xsize, ysize, tile_count)          
       implicit none
       integer, intent(in),  optional :: domain_id
       integer, intent(in),  optional :: xbegin, xend, ybegin, yend, xsize, ysize
       integer, intent(in),  optional :: tile_count
     end subroutine 

  end interface
  
  public :: cFMS_end, cFMS_error, cFMS_init
  public :: cFMS_declare_pelist, cFMS_get_current_pelist, cFMS_npes, cFMS_pe, cFMS_set_current_pelist
  public :: cFMS_define_domains
  public :: cFMS_define_io_domain
  public :: cFMS_define_layout
  public :: cFMS_define_nest_domain
  public :: cFMS_domain_is_initialized  
  public :: cFMS_set_compute_domain
  public :: cFMS_set_data_domain
  public :: cFMS_set_global_domain
  public :: cFMS_get_compute_domain
  public :: cFMS_get_data_domain
  public :: cFMS_get_domain_layout
  public :: cFMS_get_domain_name
  public :: cFMS_get_domain_pelist

contains

  !> cFMS_end
  module subroutine cFMS_end() bind(C, name="cFMS_end")
    implicit none
    call fms_end()
  end subroutine cFMS_end

  !> cFMS_init
  module subroutine cFMS_init(localcomm, alt_input_nml_path_ptr, ndomain) bind(C, name="cFMS_init")
    
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
       allocate(domain(0:ndomain-1))
    else
       allocate(domain(0:0))
    end if
    
  end subroutine cFMS_init

  !> cFMS_set_npes
  module subroutine cFMS_set_npes(npes_in) bind(C, name="cFMS_set_npes")
    implicit none
    integer, intent(in) :: npes_in
    npes = npes_in
  end subroutine cFMS_set_npes  
     
end module cFMS_mod
