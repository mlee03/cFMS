module c_data_override_mod

  use FMS, only: FmsMppDomain2D, FmsMppDomainUG, FATAL, fms_mpp_error
  use FMS, only: fms_data_override_init

  use c_fms_mod, only : cFMS_get_domain_from_id
  
  use iso_c_binding
  implicit none
  
  private
  public :: cFMS_data_override_init

  integer, public, bind(C, name="CFLOAT_MODE")  :: CFLOAT_MODE = c_float
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
    type(FmsMppDomain2D), pointer :: ocn_domain
    type(FmsMppDomain2D), pointer :: ice_domain
    type(FmsMppDomain2D), pointer :: land_domain
    type(FmsMppDomainUG), pointer :: land_domainUG

    atm_domain => NULL()
    ocn_domain => NULL()
    ice_domain => NULL()
    land_domain => NULL()
    land_domainUG => NULL()

    !NULL pointers are interpreted as not present optional arguments 
    !https://fortran-lang.discourse.group/t/an-unallocated-variable-passed-as-an-argument-is-not-present/1724/3
    if(present(atm_domain_id)) atm_domain => cFMS_get_domain_from_id(atm_domain_id)
    if(present(ocn_domain_id)) ocn_domain => cFMS_get_domain_from_id(ocn_domain_id)
    if(present(ice_domain_id)) ice_domain => cFMS_get_domain_from_id(ice_domain_id)
    if(present(land_domain_id)) land_domain => cFMS_get_domain_from_id(land_domain_id)
    if(present(land_domainUG_id)) call fms_mpp_error(FATAL, "unstructured domain is currently not implemented")
    
    call fms_data_override_init(atm_domain_in = atm_domain,   &
                                ocean_domain_in = ocn_domain, &
                                ice_domain_in = ice_domain,   &
                                land_domain_in = land_domain,  &
                                land_domainUG_in = land_domainUG, &
                                mode = mode)
    
  end subroutine cFMS_data_override_init
  
end module c_data_override_mod
