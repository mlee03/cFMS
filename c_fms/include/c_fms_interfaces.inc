module subroutine CFMS_UPDATE_DOMAINS_SUB_NAME_(field_shape, field, domain_id, flags, complete, position, &
     whalo, ehalo, shalo, nhalo, name_c, tile_count) bind(C, name=CFMS_UPDATE_DOMAINS_BINDC_)
  implicit none
  integer, intent(in) :: field_shape(CFMS_UPDATE_DOMAINS_FIELD_NDIM_)
  type(c_ptr), intent(inout) :: field
  integer, intent(in), optional :: domain_id
  integer, intent(in), optional :: flags
  logical, intent(in), optional :: complete
  integer, intent(in), optional :: position
  integer,     intent(in), optional :: whalo, ehalo, shalo, nhalo
  character(c_char), intent(in), optional :: name_c(NAME_LENGTH)
  integer,     intent(inout), optional :: tile_count
end subroutine
