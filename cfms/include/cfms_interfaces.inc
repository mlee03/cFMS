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

end subroutine
