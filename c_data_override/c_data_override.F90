module c_data_override_mod

  use FMS, only: FmsMppDomain2D, FATAL, fms_mpp_error
  use FMS, only: fms_data_override_init

  use c_fms_mod, only : cFMS_get_domain_from_id
  
  use iso_c_binding
  implicit none
  
  private
  public :: cFMS_data_override_init

  integer, public,  bind(C, name="CFLOAT_MODE")  :: CFLOAT_MODE = c_float
  integer, public, bind(C, name="CDOUBLE_MODE") :: CDOUBLE_MODE = c_double
  
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

    if(present(ocn_domain_id))    call fms_mpp_error(FATAL, "ocn_domain will be implemented in the near future")
    if(present(ice_domain_id))    call fms_mpp_error(FATAL, "ice_domain will be implemented in the near future")
    if(present(land_domain_id))   call fms_mpp_error(FATAL, "land_domain will be implemented in the near future")
    if(present(land_domainUG_id)) call fms_mpp_error(FATAL, "land unstructured domain will be implemented in the near future")
    
    if(present(atm_domain_id)) atm_domain => cFMS_get_domain_from_id(atm_domain_id)

    call fms_data_override_init(atm_domain_in = atm_domain,&
                                mode = mode)    
    
  end subroutine cFMS_data_override_init
  
end module c_data_override_mod
