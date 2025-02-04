function CFMS_REGISTER_DIAG_FIELD_SCALAR_(module_name, field_name, long_name, units,                    &
     missing_value, range, standard_name, do_not_log, err_msg, area, volume, realm, multiple_send_data) &
     bind(C, name=CFMS_REGISTER_DIAG_FIELD_SCALAR_BINDC_)
  
  implicit none
  character(c_char), intent(in) :: module_name(NAME_LENGTH)
  character(c_char), intent(in) :: field_name(NAME_LENGTH)
  character(c_char), intent(in),  optional :: long_name(NAME_LENGTH)
  character(c_char), intent(in),  optional :: units(NAME_LENGTH)
  character(c_char), intent(in),  optional :: standard_name(NAME_LENGTH)
  CFMS_REGISTER_DIAG_FIELD_SCALAR_TYPE_, intent(in), optional :: missing_value
  CFMS_REGISTER_DIAG_FIELD_SCALAR_TYPE_, intent(in), optional :: range(2)
  logical(c_bool),   intent(in),  optional :: do_not_log
  character(c_char), intent(out), optional :: err_msg(NAME_LENGTH)
  integer,           intent(in),  optional :: area
  integer,           intent(in),  optional :: volume
  character(c_char), intent(in),  optional :: realm(NAME_LENGTH)
  logical(c_bool),   intent(in),  optional :: multiple_send_data
  
  character(len=NAME_LENGTH-1) :: module_name_f    = ''
  character(len=NAME_LENGTH-1) :: field_name_f     = ''
  character(len=NAME_LENGTH-1) :: long_name_f      = ''
  character(len=NAME_LENGTH-1) :: standard_name_f  = ''
  character(len=NAME_LENGTH-1) :: units_f   = ''
  character(len=NAME_LENGTH-1) :: err_msg_f = ''
  character(len=NAME_LENGTH-1) :: realm_f   = ''
  integer :: CFMS_REGISTER_DIAG_FIELD_SCALAR_
  
  module_name_f = fms_string_utils_c2f_string(module_name)
  field_name_f  = fms_string_utils_c2f_string(field_name)  
  if(present(units))     units_f = fms_string_utils_c2f_string(units)
  if(present(realm))     realm_f = fms_string_utils_c2f_string(realm)
  if(present(long_name)) long_name_f = fms_string_utils_c2f_string(long_name)
  if(present(standard_name)) standard_name_f = fms_string_utils_c2f_string(standard_name)
  
  CFMS_REGISTER_DIAG_FIELD_SCALAR_ = fms_diag_register_diag_field(module_name_f,                   &
                                                                  field_name_f,                    &
                                                                  init_time = field_init_time,     &
                                                                  long_name = long_name_f,         &
                                                                  units = units_f,                 &
                                                                  missing_value = missing_value,   &
                                                                  range = range,                   &
                                                                  standard_name = standard_name_f, &
                                                                  do_not_log = logical(do_not_log),&
                                                                  err_msg = err_msg_f,             &
                                                                  area = area,                     &
                                                                  volume = volume,                 &
                                                                  realm = realm_f,                 &
                                                                  multiple_send_data = logical(multiple_send_data))
  
  if(present(err_msg) .and. err_msg_f /= '') call fms_string_utils_f2c_string(err_msg, err_msg_f)
    
end function CFMS_REGISTER_DIAG_FIELD_SCALAR_



