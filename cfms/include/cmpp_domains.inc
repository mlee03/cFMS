module subroutine CFMS_UPDATE_DOMAINS_SUB_NAME_(field_shape, field, domain_id, flags, complete, position, &
     whalo, ehalo, shalo, nhalo, name_c, tile_count) bind(C, name=CFMS_UPDATE_DOMAINS_BINDC_)

  implicit none
  integer, intent(in) :: field_shape(CFMS_UPDATE_DOMAINS_FIELD_SHAPE_)
  CFMS_UPDATE_DOMAINS_FIELD_TYPE_, intent(inout) :: field(CFMS_UPDATE_DOMAINS_FIELD_)
  integer, intent(in), optional :: domain_id
  integer, intent(in), optional :: flags
  logical, intent(in), optional :: complete
  integer, intent(in), optional :: position
  integer,     intent(in), optional :: whalo, ehalo, shalo, nhalo
  type(c_ptr), intent(in), optional :: name_c
  integer,     intent(in), optional :: tile_count

  CFMS_UPDATE_DOMAINS_FIELD_TYPE_ :: field_f(CFMS_UPDATE_DOMAINS_RESHAPE_)
  character(len=NAME_LENGTH) :: name_f

  
  if(present(name_c)) name_f = fms_string_utils_c2f_string(name_c)

  if(CFMS_UPDATE_DOMAINS_FIELD_SHAPE_>1) &
       field_f = reshape(field, shape=CFMS_UPDATE_DOMAINS_RESHAPE_, order=CFMS_UPDATE_DOMAINS_RESHAPE_ORDER_)

  call cFMS_set_current_domain(domain_id)
  
  call fms_mpp_domains_update_domains(field, current_domain, flags, complete, position, &
                                      whalo, ehalo, shalo, nhalo, name_f, tile_count)

  if(CFMS_UPDATE_DOMAINS_FIELD_SHAPE_>1) &
       field = reshape(field_f, shape=CFMS_UPDATE_DOMAINS_RESHAPE_BACK_, order=CFMS_UPDATE_DOMAINS_RESHAPE_ORDER_)

end subroutine CFMS_UPDATE_DOMAINS_SUB_NAME_
