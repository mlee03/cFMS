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
submodule(c_fms_mod) c_mpp_smod

  implicit none
  
contains


  !> cFMS_declare_pelist
  module subroutine cFMS_declare_pelist(pelist, name, commID) bind(C, name="cFMS_declare_pelist")

    implicit none
    integer, intent(in) :: pelist(npes)
    character(c_char), intent(in), optional :: name(NAME_LENGTH)
    integer, intent(out), optional :: commID

    character(len=NAME_LENGTH) :: name_f=" " !mpp default

    if(present(name)) name_f = fms_string_utils_c2f_string(name)
    call fms_mpp_declare_pelist(pelist, name_f, commID)
    
  end subroutine cFMS_declare_pelist
  
  !> cFMS_error
  module subroutine cFMS_error(errortype, errormsg) bind(C, name="cFMS_error")
    
    implicit none
    integer, intent(in), value :: errortype
    character(c_char), intent(in), optional :: errormsg(MESSAGE_LENGTH)
    character(len=MESSAGE_LENGTH) :: errormsg_f=""

    if(present(errormsg)) errormsg_f = fms_string_utils_c2f_string(errormsg)
    call fms_mpp_error(errortype, trim(errormsg_f))
    
  end subroutine cFMS_error

  
  !> cFMS_get_current_pelist
  module subroutine cFMS_get_current_pelist(pelist, name, commID) bind(C, name="cFMS_get_current_pelist")

    implicit none
    integer, intent(out) :: pelist(npes)
    character(c_char), intent(out), optional :: name(NAME_LENGTH)
    integer, intent(out), optional :: commID

    character(len=NAME_LENGTH) :: name_f=" " !mpp default
    
    if(present(name)) name_f = fms_string_utils_c2f_string(name)
    call fms_mpp_get_current_pelist(pelist, name_f, commID)
    
  end subroutine cFMS_get_current_pelist

  !> cFMS_npes
  module function cFMS_npes() bind(C, name="cFMS_npes")
    implicit none
    integer :: cFMS_npes
    cFMS_npes = fms_mpp_npes()
  end function cFMS_npes  

  !> cFMS_pes
  module function cFMS_pe() bind(C, name="cFMS_pe")
    implicit none
    integer :: cFMS_pe
    cFMS_pe = fms_mpp_pe()
  end function cFMS_pe
  
  !> cFMS_set_current_pelist
  module subroutine cFMS_set_current_pelist(pelist, no_sync) bind(C, name="cFMS_set_current_pelist")

    implicit none
    integer, intent(in), optional :: pelist(npes)
    logical(c_bool), intent(in), optional :: no_sync

    if(present(no_sync)) then
       call fms_mpp_set_current_pelist(pelist, logical(no_sync))
    else
       call fms_mpp_set_current_pelist(pelist)
    end if
    
  end subroutine cFMS_set_current_pelist
  

end submodule c_mpp_smod
