function CFMS_DIAG_SEND_DATA_(diag_field_id, field_shape, field, err_msg) bind(C, name=CFMS_DIAG_SEND_DATA_BINDC_)
  
  implicit none
  
  integer, intent(in) :: diag_field_id
  integer, intent(in) :: field_shape(CFMS_DIAG_SEND_DATA_FIELD_NDIM_)
  type(c_ptr), value, intent(in) :: field
  character(c_bool), intent(out), optional :: err_msg(MESSAGE_LENGTH)
  
  character(MESSAGE_LENGTH-1) :: err_msg_f
  logical(c_bool) :: CFMS_DIAG_SEND_DATA_  

  CFMS_DIAG_SEND_DATA_FIELD_TYPE_, pointer :: field_cf(:)
  CFMS_DIAG_SEND_DATA_FIELD_TYPE_, allocatable :: field_f321(CFMS_DIAG_SEND_DATA_FIELD_ASSUMED_SHAPE_)

  call c_f_pointer(field, field_cf, [product(field_shape)])
  field_f321 = reshape(field_cf,  [CFMS_DIAG_SEND_DATA_FIELD_REVERSED_SHAPE_])
  
  CFMS_DIAG_SEND_DATA_ = fms_diag_send_data(diag_field_id = diag_field_id, &
                                       field = field_f321,            &
                                       time = field_curr_time(diag_field_id), &
                                       err_msg = err_msg_f)

  CFMS_DIAG_SEND_DATA_ = logical(CFMS_DIAG_SEND_DATA_, kind=c_bool)

  deallocate(field_f321)
  
  if(present(err_msg) .and. err_msg_f /= '' ) call fms_string_utils_f2c_string(err_msg, err_msg_f)

end function CFMS_DIAG_SEND_DATA_
