module cdiag_manager_mod

  use FMS, only : fms_diag_init, fms_diag_end
  use FMS, only : fms_diag_register_diag_field, fms_diag_register_static_field, fms_diag_axis_init
  use FMS, only : DIAG_OTHER, DIAG_OCEAN, DIAG_ALL
  use FMS, only : fms_string_utils_c2f_string, fms_string_utils_f2c_string
  use FMS, only : THIRTY_DAY_MONTHS, GREGORIAN, JULIAN, NOLEAP
  use FMS, only : FmsTime_type, fms_time_manager_init, fms_time_manager_set_date, fms_time_manager_set_calendar_type

  use FMS, only : FmsMppDomain2D

  use cFMS_mod, only : cFMS_get_current_domain
  use cFMS_mod, only : CFMS_CFLOAT_TYPE, CFMS_CDOUBLE_TYPE, CFMS_CINT_TYPE, NAME_LENGTH, MESSAGE_LENGTH

  use iso_c_binding

  implicit none

  private
  
  public :: cFMS_diag_axis_init_cfloat
  public :: cFMS_diag_axis_init_cdouble  
  public :: cFMS_diag_end
  public :: cFMS_diag_init
  public :: cFMS_diag_set_field_init_time
  public :: cFMS_diag_set_field_curr_time
  public :: cFMS_register_diag_field_scalar_int
  public :: cFMS_register_diag_field_scalar_cfloat
  public :: cFMS_register_diag_field_scalar_cdouble
  public :: cFMS_register_diag_field_array_int
  public :: cFMS_register_diag_field_array_cfloat
  public :: cFMS_register_diag_field_array_cdouble
  
  type(FmsTime_type), save :: field_init_time
  type(FmsTime_type), save :: field_curr_time

  integer, public, bind(C, name="DIAG_OTHER") :: DIAG_OTHER_C = DIAG_OTHER
  integer, public, bind(C, name="DIAG_OCEAN") :: DIAG_OCEAN_C = DIAG_OCEAN
  integer, public, bind(C, name="DIAG_ALL")   :: DIAG_ALL_C   = DIAG_ALL

  integer, public, bind(C, name="THIRTY_DAY_MONTHS") :: THIRTY_DAY_MONTHS_C = THIRTY_DAY_MONTHS
  integer, public, bind(C, name="GREGORIAN")         :: GREGORIAN_C = GREGORIAN
  integer, public, bind(C, name="JULIAN")            :: JULIAN_C    = JULIAN
  integer, public, bind(C, name="NOLEAP")            :: NOLEAP_C    = NOLEAP

contains


  subroutine cFMS_diag_end() bind(C, name="cFMS_diag_end")
    implicit none

    call fms_diag_end(field_curr_time)
    
  end subroutine cFMS_diag_end
  
  subroutine cFMS_diag_init(diag_model_subset, time_init, err_msg, calendar_type) bind(C, name='cFMS_diag_init')

    implicit none
    integer, optional, intent(in) :: diag_model_subset
    integer, optional, intent(in) :: time_init(6)
    integer, optional, intent(in) :: calendar_type
    character(c_char), intent(out), optional :: err_msg(MESSAGE_LENGTH)

    character(len=MESSAGE_LENGTH-1) :: err_msg_f="None"
    integer :: calendar_type_f = NOLEAP

    if(present(calendar_type)) calendar_type_f = NOLEAP

    call fms_time_manager_init()
    call fms_time_manager_set_calendar_type(calendar_type_f)

    call fms_diag_init(diag_model_subset = diag_model_subset, &
                       time_init = time_init, &
                       err_msg = err_msg_f)
    
    if(present(err_msg) .and. err_msg_f /= '' ) call fms_string_utils_f2c_string(err_msg, err_msg_f)
    
  end subroutine cFMS_diag_init

  
  subroutine cFMS_diag_set_field_init_time(year, month, day, hour, minute, second, tick, err_msg) &
       bind(C, name="cFMS_diag_set_field_init_time")

    implicit none
    integer, intent(in) :: year
    integer, intent(in) :: month
    integer, intent(in) :: day
    integer, intent(in) :: hour
    integer, intent(in) :: minute
    integer, intent(in), optional :: second
    integer, intent(in), optional :: tick
    character, intent(out), optional :: err_msg(MESSAGE_LENGTH)

    character(MESSAGE_LENGTH-1) :: err_msg_f = ""
    
    field_init_time = fms_time_manager_set_date(year = year,     &
                                                month = month,   &
                                                day = day,       &
                                                hour = hour,     &
                                                minute = minute, &
                                                second = second, &
                                                tick = tick,     &
                                                err_msg = err_msg_f)

    
    if(present(err_msg) .and. err_msg_f /= '') call fms_string_utils_f2c_string(err_msg, err_msg_f)
    
  end subroutine cFMS_diag_set_field_init_time

  
  subroutine cFMS_diag_set_field_curr_time(year, month, day, hour, minute, second, tick, err_msg) &
       bind(C, name="cFMS_diag_set_field_curr_time")

    implicit none
    integer, intent(in), optional :: year
    integer, intent(in), optional :: month
    integer, intent(in), optional :: day
    integer, intent(in), optional :: hour
    integer, intent(in), optional :: minute
    integer, intent(in), optional :: second
    integer, intent(in), optional :: tick
    character(c_char), intent(out), optional :: err_msg(MESSAGE_LENGTH)

    character(MESSAGE_LENGTH-1) :: err_msg_f

    field_curr_time = fms_time_manager_set_date(year = year,   &
                                                month = month, &
                                                day = day,     &
                                                hour = hour,   &
                                                minute = minute, &
                                                second = second, &
                                                tick = tick,     &
                                                err_msg = err_msg_f)

    if(present(err_msg) .and. err_msg_f /= '') call fms_string_utils_f2c_string(err_msg, err_msg_f)    

  end subroutine cFMS_diag_set_field_curr_time
  
#include "cdiag_axis_init.fh"
#include "cregister_diag_field.fh"

  
  
  !subroutine register_diag_field
  !subroutine register_static_field
  
  
  !subroutine send_data
  !subroutine send_tile_averaged_data
  !subroutine diag_end
  !subroutine get_base_time
  !subroutine get_base_date
  !subroutine get_diag_global_att
  !subroutine set_diag_global_att
  !subroutine diag_field_add_attribute
  !subroutine get_diag_field_id
  !subroutine diag_axis_add_attribute
  !subroutine diag_send_complete
  !subroutine diag_send_complete_instant
  
  
end module cdiag_manager_mod
