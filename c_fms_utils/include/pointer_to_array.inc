subroutine CFMS_POINTER_TO_ARRAY_(c_pointer, c_shape, f_array)
  
  implicit none
  type(c_ptr), intent(in), value :: c_pointer
  integer, intent(in) :: c_shape(:)
  CFMS_POINTER_TO_ARRAY_TYPE_, intent(out) :: f_array(CFMS_POINTER_TO_ARRAY_ASSUMED_SHAPE_)

  CFMS_POINTER_TO_ARRAY_TYPE_, pointer :: f_pointer(CFMS_POINTER_TO_ARRAY_ASSUMED_SHAPE_)
  
  call c_f_pointer(c_pointer, f_pointer, CFMS_POINTER_TO_ARRAY_REVERSED_SHAPE_)
  f_array = reshape(f_pointer, shape=CFMS_POINTER_TO_ARRAY_SHAPE_, order=CFMS_POINTER_TO_ARRAY_ROW_MAJOR_)

  nullify(f_pointer)

end subroutine CFMS_POINTER_TO_ARRAY_
