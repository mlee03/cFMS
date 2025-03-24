subroutine CFMS_ARRAY_TO_POINTER_(f_array, c_shape, c_pointer)

  implicit none
  integer, intent(in) :: c_shape(:)
  CFMS_ARRAY_TO_POINTER_TYPE_, intent(in) :: f_array(CFMS_ARRAY_TO_POINTER_ASSUMED_SHAPE_)
  type(c_ptr), value, intent(in) :: c_pointer

  CFMS_ARRAY_TO_POINTER_TYPE_, pointer :: cf_pointer(CFMS_ARRAY_TO_POINTER_ASSUMED_SHAPE_)
  CFMS_ARRAY_TO_POINTER_TYPE_, allocatable :: tmp_array(CFMS_ARRAY_TO_POINTER_ASSUMED_SHAPE_)
  
  allocate(tmp_array(CFMS_ARRAY_TO_POINTER_REVERSED_SHAPE_))
  tmp_array = reshape(f_array, [CFMS_ARRAY_TO_POINTER_REVERSED_SHAPE_], order=[CFMS_ARRAY_TO_POINTER_COLUMN_MAJOR_])

  call c_f_pointer(c_pointer, cf_pointer, [CFMS_ARRAY_TO_POINTER_REVERSED_SHAPE_])
  cf_pointer = tmp_array
  
  deallocate(tmp_array)
  nullify(cf_pointer)
  
end subroutine CFMS_ARRAY_TO_POINTER_
