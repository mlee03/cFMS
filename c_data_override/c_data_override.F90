module c_data_override_mod

  use FMS, only: FmsMppDomain2D, FATAL, fms_mpp_error
  use FMS, only: fms_data_override_init, fms_data_override
  use FMS, only: fms_string_utils_c2f_string, fms_string_utils_f2c_string
  use FMS, only: fms_time_manager_set_time, fms_time_manager_set_date, FmsTime_type
  
  use c_fms_mod, only : cFMS_get_domain_from_id, NAME_LENGTH, MESSAGE_LENGTH
  
  use iso_c_binding
  implicit none
  
  private
  public :: cFMS_data_override_0d_cfloat
  public :: cFMS_data_override_0d_cdouble  
  public :: cFMS_data_override_init
  public :: cFMS_data_override_set_time

  integer, public, bind(C, name="CFLOAT_MODE")  :: CFLOAT_MODE = c_float
  integer, public, bind(C, name="CDOUBLE_MODE") :: CDOUBLE_MODE = c_double

  type(FmsTime_type) :: data_override_time
  
contains

  subroutine cFMS_data_override_init(atm_domain_id, ocn_domain_id, ice_domain_id, land_domain_id, &
       land_domainUG_id, mode) bind(C, name="cFMS_data_override_init")

    implicit none
    integer, intent(in), optional :: atm_domain_id
    integer, intent(in), optional :: ocn_domain_id
    integer, intent(in), optional :: ice_domain_id
    integer, intent(in), optional :: land_domain_id
    integer, intent(in), optional :: land_domainUG_id
    integer, intent(in), optional :: mode

    type(FmsMppDomain2D), pointer :: atm_domain
    type(FmsMppDomain2D), pointer :: ocn_domain
    type(FmsMppDomain2D), pointer :: ice_domain
    type(FmsMppDomain2D), pointer :: land_domain
    type(FmsMppDomain2D), pointer :: land_domainUG
    
    if(present(atm_domain_id)) atm_domain => cFMS_get_domain_from_id(atm_domain_id)
    if(present(ocn_domain_id)) ocn_domain => cFMS_get_domain_from_id(ocn_domain_id)
    if(present(ice_domain_id)) ice_domain => cFMS_get_domain_from_id(ice_domain_id)
    if(present(land_domain_id)) land_domain => cFMS_get_domain_from_id(land_domain_id)
    if(present(land_domainUG_id)) landUG_domain => cFMS_get_domain_from_id(land_domainUG_id)

    call fms_data_override_init(atm_domain_in = atm_domain, mode = mode)    
    
  end subroutine cFMS_data_override_init


  subroutine cFMS_data_override_set_time(year, month, day, hour, minute, second, tick, err_msg)&
       bind(C, name="cFMS_data_override_set_time")

    implicit none
    integer, intent(in), optional :: year
    integer, intent(in), optional :: month
    integer, intent(in), optional :: day
    integer, intent(in), optional :: hour
    integer, intent(in), optional :: minute
    integer, intent(in), optional :: second
    integer, intent(in), optional :: tick
    character, intent(out), optional :: err_msg(MESSAGE_LENGTH)
    
    character(MESSAGE_LENGTH-1) :: err_msg_f = ""
    
    data_override_time = fms_time_manager_set_date(year = year,     &
                                                   month = month,   &
                                                   day = day,       &
                                                   hour = hour,     &
                                                   minute = minute, &
                                                   second = second, &
                                                   tick = tick,     &
                                                   err_msg = err_msg_f)

    if(present(err_msg) .and. err_msg_f /= '') call fms_string_utils_f2c_string(err_msg, err_msg_f)
    
  end subroutine cFMS_data_override_set_time

#include "c_data_override_0d.fh"
  
end module c_data_override_mod
