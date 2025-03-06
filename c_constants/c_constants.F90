module c_constants_mod

  use constants_mod, only: PI_8
  use constants_mod, only: RADIUS
  use iso_c_binding

  implicit none

  real(c_double), public, bind(C, name="PI")     :: PI_C = PI_8
  real(c_double), public, bind(C, name="RADIUS") :: RADIUS_C = RADIUS  

end module c_constants_mod
