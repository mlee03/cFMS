  subroutine CFMS_DATA_OVERRIDE_0D_(gridname, fieldname_code, data_out, override, data_index) &
       bind(C, name=CFMS_DATA_OVERRIDE_0D_BINDC_)

    use FMS, only : fms_time_manager_get_date
    
    implicit none
    character(c_char), intent(in) :: gridname(NAME_LENGTH)
    character(c_char), intent(in) :: fieldname_code(NAME_LENGTH)
    CFMS_DATA_OVERRIDE_0D_TYPE_, intent(out) :: data_out
    logical(c_bool), intent(out), optional   :: override
    integer, intent(in),  optional :: data_index
    
    character(len=NAME_LENGTH-1) :: gridname_f
    character(len=NAME_LENGTH-1) :: fieldname_code_f

    CFMS_DATA_OVERRIDE_0D_TYPE_ :: data_out_f
    logical :: override_f

    gridname_f = fms_string_utils_c2f_string(gridname)
    fieldname_code_f = fms_string_utils_c2f_string(fieldname_code)

    call fms_data_override(gridname = gridname_f, &
                           fieldname_code = fieldname_code_f, &
                           data_out = data_out,       &
                           time = data_override_time, &
                           override = override_f,     &
                           data_index = data_index)

    if(present(override)) override = logical(override_f, c_bool)         
    
  end subroutine CFMS_DATA_OVERRIDE_0D_
  
