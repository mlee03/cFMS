subroutine test_3d_cdouble(array_shape, c_pointer) bind(C, name="test_3d_cdouble")
  
  use c_fms_mod, only: cFMS_error, FATAL
  use c_fms_utils_mod, only : cFMS_pointer_to_array, cFMS_array_to_pointer
  use iso_c_binding  
  
  implicit none
  integer, intent(in) :: array_shape(3)
  type(c_ptr), value, intent(in) :: c_pointer
  
  integer :: i, j, k
  real(c_double), allocatable :: f_array(:,:,:)
  real(c_double), allocatable :: answers(:,:,:)
  
  allocate(answers(array_shape(1),array_shape(2),array_shape(3)))
  do k=1, array_shape(3)
     do j=1, array_shape(2)
        do i=1, array_shape(1)
           answers(i,j,k) = (i-1)*100+(j-1)*10+(k-1)
        end do
     end do
  end do
  
  allocate(f_array(array_shape(1),array_shape(2),array_shape(3)))
  call cFMS_pointer_to_array(c_pointer, array_shape, f_array)
  
  if(any(answers.ne.f_array)) then
     write(*,*) "ERROR converting pointer to array"
     call cFMS_error(FATAL)
  end if

  f_array = - f_array
 
  call cFMS_array_to_pointer(f_array, array_shape, c_pointer)

  deallocate(f_array)
  deallocate(answers)
  
end subroutine test_3d_cdouble
  
