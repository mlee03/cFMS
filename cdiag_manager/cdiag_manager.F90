module cdiag_manager_mod

  use FMS, only : fms_diag_init, fms_diag_register_diag_field, fms_diag_register_static_field, fms_diag_axis_init
  use FMS, only : DIAG_OTHER, DIAG_OCEAN, DIAG_ALL
  use FMS, only : fms_string_utils_c2f_string, fms_string_utils_f2c_string
  use FMS, only : THIRTY_DAY_MONTHS, GREGORIAN, JULIAN, NOLEAP
  use FMS, only : FmsTime_type, fms_time_manager_init, fms_time_manager_set_time, fms_time_manager_set_calendar_type

  use FMS, only : FmsMppDomain2D

  use cFMS_mod, only : cFMS_get_current_domain
  use cFMS_mod, only : CFMS_CFLOAT_TYPE, CFMS_CDOUBLE_TYPE, CFMS_CINT_TYPE, NAME_LENGTH, MESSAGE_LENGTH

  use iso_c_binding

  implicit none

  private

  public :: cFMS_diag_axis_init_cfloat
  public :: cFMS_diag_axis_init_cdouble  
  public :: cFMS_diag_init
  public :: cFMS_diag_set_field_init_time
  public :: cFMS_register_diag_field_scalar
  public :: cFMS_set_diag_axis_type
  public :: cFMS_set_diag_data_type
  
  type(FmsTime_type), save :: field_init_time

  integer, public, bind(C, name="DIAG_OTHER") :: DIAG_OTHER_C = DIAG_OTHER
  integer, public, bind(C, name="DIAG_OCEAN") :: DIAG_OCEAN_C = DIAG_OCEAN
  integer, public, bind(C, name="DIAG_ALL")   :: DIAG_ALL_C = DIAG_ALL

  integer, public, bind(C, name="THIRTY_DAY_MONTHS") :: THIRTY_DAY_MONTHS_C = THIRTY_DAY_MONTHS
  integer, public, bind(C, name="GREGORIAN")         :: GREGORIAN_C = GREGORIAN
  integer, public, bind(C, name="JULIAN")            :: JULIAN_C   = JULIAN
  integer, public, bind(C, name="NOLEAP")            :: NOLEAP_C    = NOLEAP

  integer, public :: CFMS_DIAG_AXIS_TYPE
  integer, public :: CFMS_DIAG_DATA_TYPE
  
contains

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

    call fms_diag_init(diag_model_subset=diag_model_subset, time_init=time_init, err_msg=err_msg_f)
    
    if(present(err_msg) .and. err_msg_f /= '' ) call fms_string_utils_f2c_string(err_msg, err_msg_f)
    
  end subroutine cFMS_diag_init

  
  subroutine cFMS_diag_set_field_init_time(seconds, days, ticks) bind(C, name="cFMS_diag_set_field_init_time")

    implicit none
    integer, intent(in), optional :: seconds
    integer, intent(in), optional :: days
    integer, intent(in), optional :: ticks

    field_init_time = fms_time_manager_set_time(seconds=seconds, days=days, ticks=ticks)
    
  end subroutine cFMS_diag_set_field_init_time
  
  function cFMS_register_diag_field_scalar(module_name, field_name, long_name, units, &
       missing_value_int, missing_value_cfloat, missing_value_cdouble, range_int, range_cfloat, range_cdouble, &
       standard_name, do_not_log, err_msg, area, volume, realm, multiple_send_data) &
       bind(C, name='cFMS_register_diag_field_scalar')
    
    implicit none
    character(c_char), intent(in) :: module_name(NAME_LENGTH)
    character(c_char), intent(in) :: field_name(NAME_LENGTH)
    character(c_char), intent(in), optional :: long_name(NAME_LENGTH)
    character(c_char), intent(in), optional :: units(NAME_LENGTH)
    character(c_char), intent(in),  optional :: standard_name(NAME_LENGTH)
    integer,        intent(in), optional :: missing_value_int
    real(c_float),  intent(in), optional :: missing_value_cfloat
    real(c_double), intent(in), optional :: missing_value_cdouble
    integer,        intent(in), optional :: range_int(2)
    real(c_float),  intent(in), optional :: range_cfloat(2)
    real(c_double), intent(in), optional :: range_cdouble(2)
    logical(c_bool),   intent(in),  optional :: do_not_log
    character(c_char), intent(out), optional :: err_msg(NAME_LENGTH)
    integer,   intent(in), optional :: area
    integer,   intent(in), optional :: volume
    character(c_char), intent(in), optional :: realm(NAME_LENGTH)
    logical(c_bool),   intent(in), optional :: multiple_send_data

    class(*), allocatable :: missing_value
    class(*), allocatable :: range(:)
    character(len=NAME_LENGTH-1) :: module_name_f = ''
    character(len=NAME_LENGTH-1) :: field_name_f  = ''
    character(len=NAME_LENGTH-1) :: long_name_f   = ''
    character(len=NAME_LENGTH-1) :: standard_name_f  = ''
    character(len=NAME_LENGTH-1) :: units_f   = ''
    character(len=NAME_LENGTH-1) :: err_msg_f = ''
    character(len=NAME_LENGTH-1) :: realm_f   = ''
    integer :: cFMS_register_diag_field_scalar

    if(present(range_int))     allocate(range, source=range_int)
    if(present(range_cfloat))  allocate(range, source=range_cfloat)
    if(present(range_cdouble)) allocate(range, source=range_cdouble)
    if(present(missing_value_int))     allocate(missing_value, source=missing_value_int)
    if(present(missing_value_cfloat))  allocate(missing_value, source=missing_value_cfloat)
    if(present(missing_value_cdouble)) allocate(missing_value, source=missing_value_cdouble)

    module_name_f = fms_string_utils_c2f_string(module_name)
    field_name_f  = fms_string_utils_c2f_string(field_name)
    if(present(units))     units_f = fms_string_utils_c2f_string(units)
    if(present(realm))     realm_f = fms_string_utils_c2f_string(realm)
    if(present(long_name)) long_name_f = fms_string_utils_c2f_string(long_name)
    if(present(standard_name)) standard_name_f = fms_string_utils_c2f_string(standard_name)
    
    cFMS_register_diag_field_scalar = fms_diag_register_diag_field(module_name_f, field_name_f,        &
         init_time=field_init_time, long_name=long_name_f, units=units_f, missing_value=missing_value, &
         range=range, standard_name=standard_name_f, do_not_log=logical(do_not_log), err_msg=err_msg_f,&
         area=area, volume=volume, realm=realm_f, multiple_send_data=logical(multiple_send_data))
       
    if(present(err_msg) .and. err_msg_f /= '') call fms_string_utils_f2c_string(err_msg, err_msg_f)
    
  end function cFMS_register_diag_field_scalar


  subroutine cFMS_set_diag_axis_type(axis_type) bind(C, name="cFMS_set_axis_type")
    implicit none
    integer, intent(in), value :: axis_type
    CFMS_DIAG_AXIS_TYPE = axis_type
  end subroutine cFMS_set_diag_axis_type

  
  subroutine cFMS_set_diag_data_type(data_type) bind(C, name="cFMS_set_data_type")
    implicit none
    integer, intent(in), value :: data_type
    CFMS_DIAG_DATA_TYPE = data_type
  end subroutine cFMS_set_diag_data_type
    
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
  
#include "cdiag_manager.fh"
  
end module cdiag_manager_mod
