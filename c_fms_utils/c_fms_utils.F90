module c_fms_utils_mod

  use iso_c_binding
  implicit none

  private
  public :: cFMS_pointer_to_array
  
  interface cFMS_pointer_to_array
     module procedure cFMS_pointer_to_array_2d_int
     module procedure cFMS_pointer_to_array_3d_int
     module procedure cFMS_pointer_to_array_4d_int
     module procedure cFMS_pointer_to_array_5d_int
     module procedure cFMS_pointer_to_array_2d_cfloat
     module procedure cFMS_pointer_to_array_3d_cfloat
     module procedure cFMS_pointer_to_array_4d_cfloat
     module procedure cFMS_pointer_to_array_5d_cfloat
     module procedure cFMS_pointer_to_array_2d_cdouble
     module procedure cFMS_pointer_to_array_3d_cdouble
     module procedure cFMS_pointer_to_array_4d_cdouble
     module procedure cFMS_pointer_to_array_5d_cdouble
  end interface cFMS_pointer_to_array
  
contains

#include "pointer_to_array.fh"
  
end module c_fms_utils_mod
