module cdiag_manager_mod

  use FMS, only : fms_diag_manager_init, fms_diag_register_diag_field, fms_diag_register_static_field
  use FMS, only : DIAG_OTHER, DIAG_OCEAN, DIAG_ALL
  use FMS, only : FmsTime_type, fms_time_manager_init, fms_set_time
  use FMS, only : fms_string_utils_c2f_string, fms_string_utils_f2c_string
  use iso_c_binding

  private
  
  public :: cFMS_diag_manager_init
  public :: cFMS_diag_manager_set_field_init_time
  public :: cFMS_register_diag_field
  
  type(FmsTime_type), save :: field_init_time

  integer, parameter, bind(C, name="C_FLOAT") :: c_float_kind = 1
  integer, parameter, bind(C, name="C_DOUBLE") :: cdouble_kind = 2
  integer, parameter, bind(C, name="C_INT") :: c_int_kind = 3
  
contains

  subroutine cFMS_diag_manager_init(diag_model_subset, time_init, err_msg) bind(C, name='cFMS_diag_manager_init')

    implicit none
    integer, optional, intent(in) :: diag_model_subset
    integer, optional, intent(in) :: time_init(6)
    character, intent(out), optional :: err_msg(NAME_LENGTH)

    character :: err_msg_f(NAME_LENGTH)

    call diag_manager_init(diag_model_subset, time_init, err_msg_f)

    if(present(err_msg)) fms_string_utils_f2c_string(error_msg, err_msg_f)
    
  end subroutine cFMS_diag_manager_init


  subroutine cFMS_diag_manager_set_field_init_time(seconds, days, ticks)
    implicit none

    integer, intent(in), optional :: seconds
    integer, intent(in), optional :: days
    integer, intent(in), optional :: ticks

    field_init_time = fms_time_set_time(seconds=seconds, days=days, ticks=ticks)
    
  end subroutine cFMS_diag_manager_set_field_init_time
  
  function cFMS_register_diag_field_scalar(module_name, field_name, long_name, units, standard_name, naxis, axis, &
       missing_value_int, missing_value_cfloat, missing_value_cdouble, range_int, range_cfloat, range_cdouble, &
       do_not_log, err_msg, area, volume, realm, multiple_send_data) bind(C, name='cFMS_register_diag_field_scalar')
    
    implicit none
    character, intent(in) :: module_name(NAME_LENGTH)
    character, intent(in) :: field_name(NAME_LENGTH)
    character, intent(in), optional :: long_name(NAME_LENGTH)
    character, intent(in), optional :: units(NAME_LENGTH)
    integer,        intent(in), optional :: missing_value_int
    real(c_float),  intent(in), optional :: missing_value_cfloat
    real(c_double), intent(in), optional :: missing_value_cdouble
    integer,        intent(in), optional :: range_int(2)
    real(c_float),  intent(in), optional :: range_cfloat(2)
    real(c_double), intent(in), optional :: range_cdouble(2)
    character, intent(in),  optional :: standard_name(NAME_LENGTH)
    logical,   intent(in),  optional :: do_not_log
    character, intent(out), optional :: err_msg(NAME_LENGTH)
    integer,   intent(in), optional :: area
    integer,   intent(in), optional :: volume
    character, intent(in), optional :: realm
    logical,   intent(in), optional :: multiple_send_data

    class(*), allocatable :: missing_value
    class(*), allocatable :: range    
    character :: long_name_f(NAME_LENGTH) = ''
    character :: units_f(NAME_LENGTH) = ''
    character :: err_msg_f(NAME_LENGTH) = ''
    character :: interp_method_f(NAME_LENGTH) = ''
    integer :: cFMS_register_diag_field_scalar

    if(present(range_int))     allocate(range, source=range_int)
    if(present(range_cfloat))  allocate(range, source=range_cfloat)
    if(present(range_cdouble)) allocate(range, source=range_cdouble)
    if(present(missing_value_int))     allocate(missing_value, source=missing_value_int)
    if(present(missing_value_cfloat))  allocate(missing_value, source=missing_value_cfloat)
    if(present(missing_value_cdouble)) allocate(missing_value, source=missing_value_cdouble)
    
    if(present(units)) units_f = fms_string_utils_c2f_string(units)
    if(present(long_name)) long_name_f = fms_string_utils_c2f_string(long_name)
    
    cFMS_register_diag_field_scalar = fms_diag_register_diag_field_array(module_name, field_name, axes,     &
         field_init_time, long_name=long_name_f, units=units_f, missing_value=missing_value, range=range,   &
         standard_name=standard_name_f, verbose=verbose, do_not_log=do_not_log, err_msg=err_msg,            & 
         area=area, volume=volume, realm=realm, multiple_send_data=multiple_send_data)
       
    ! err_msg return
    
  end function cFMS_register_diag_field_scalar
  
  !subroutine register_diag_field
  !subroutine register_static_field
  
  
  !subroutine send_data
  !subroutine send_tile_averaged_data
  !subroutine diag_manager_end
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
