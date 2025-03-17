program main

  use c_fms_mod
  use c_fms_utils_mod, only : cFMS_pointer_to_array
  use iso_c_binding  
  implicit none


  call test_3d_cdouble()

contains
  subroutine test_3d_cdouble()

    implicit none
    real(c_double), target :: c_pointer(100)
    real(c_double), allocatable :: test_array(:,:,:)
    integer :: c_shape(3)

    integer :: i, j, k
    
    call test(c_shape, c_pointer)

    allocate(test_array(c_shape(1), c_shape(2), c_shape(3)))
    call cFMS_pointer_to_array(c_loc(c_pointer), c_shape, test_array)

    do k=1, c_shape(3)
       do j=1, c_shape(2)
          do i=1, c_shape(1)
             if(test_array(i,j,k).ne. real(i*100+j*10+k,c_double)) call cFMS_error(FATAL);
          end do
       end do
    end do
    
  end subroutine test_3d_cdouble
  
end program main
  
