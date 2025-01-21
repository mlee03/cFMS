function cFMS_REGISTER_DIAG_FIELD_SCALAR_(module_name, field_name, long_name, units, missing_value, range, &
     standard_name, do_not_log, err_msg, area, volume, realm, multiple_send_data) bind(C, name=CFMS_REGISTER_FIELD_SCALAR_C)

  implicit none
  character, intent(in) :: module_name(NAME_LENGTH)
  character, intent(in) :: field_name(NAME_LENGTH)
  character, intent(in) :: long_name(NAME_LENGTH)
  character, intent(in) :: units(NAME_LENGTH)
  character, intent(in) :: standard_name(NAME_LENGTH)
  CFMS_FIELD_TYPE_, intent(


function CFMS_REGISTER_FIELD_ARRAY_(module_name, field_name, long_name, units, standard_name, naxis, axis, missing_value, &
     range, do_not_log, err_msg, area, volume, realm, multiple_send_data) bind(C, name=CFMS_REGISTER_FIELD_ARRAY_C_)
  
  implicit none
  character, intent(in) :: module_name(NAME_LENGTH)
  character, intent(in) :: field_name(NAME_LENGTH)
  integer, intent(in), optional :: naxis
  integer, intent(in), optional :: axes(naxes)
  integer, intent(in), optional :: field_type
  character, intent(in), optional :: long_name(NAME_LENGTH)
  character, intent(in), optional :: units(NAME_LENGTH)
  CFMS_FIELD_TYPE_, intent(in), optional :: missing_value
  CFMS_FIELD_TYPE_, intent(in), optional :: range(2)
  logical, intent(in), optional :: mask_variant
  character, intent(in), optional :: standard_name(NAME_LENGTH)
  logical, intent(in), optional :: verbose    
  logical, intent(in), optional :: do_not_log
  character, intent(in), optional :: err_msg(NAME_LENGTH)
  character, intent(in), optional :: interp_method(NAME_LENGTH)
  integer, intent(in), optional :: tile_count    
  integer, intent(in), optional :: area
  integer, intent(in), optional :: volume
  character, intent(in), optional :: realm
  logical, intent(in), optional :: multiple_send_data
  
  integer :: cFMS_register_diag_field_scalar

  if(present(long_name)) long_name_f = fms_string_utils_c2f_string(long_name)
  if(present(units) units_f = fms_string_utils_c2f_string(units)
  if(present(standard_name) standard_name_f = fms_string_utils_c2f_string(standard_name)
  
  cFMS_register_diag_field_scalar = fms_diag_register_diag_field_array(module_name, field_name, axes, &
       field_init_time, long_name=long_name, units=units_f, missing_value=missing_value, range=range,   &
       mask_variant=mask_variant, standard_name=standard_name, verbose=verbose, do_not_log=do_not_log, &
       err_msg=err_msg, interp_method=interp_method, tile_count=tile_count, area=area, volume=volume, &
       realm=realm, multiple_send_data=multiple_send_data)
  
end function CFMS_REGISTER_FIELD_ARRAY_
  
