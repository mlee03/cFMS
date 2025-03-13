module c_horiz_interp_mod

  use FMS, only : fms_horiz_interp_init
  use iso_c_binding
  implicit none

  private

  public :: cFMS_create_xgrid_2dx2d_order1
  public :: cFMS_get_maxxgrid
  public :: cFMS_horiz_interp_init
  
contains

  !cFMS_create_xgrid_2dx2d_order1
  function cFMS_create_xgrid_2dx2d_order1(nlon_in, nlat_in, nlon_out, nlat_out, lon_in, lat_in, lon_out, &
       lat_out, mask_in, maxxgrid, i_in, j_in, i_out, j_out, xgrid_area) bind(C, name="cFMS_create_xgrid_2dx2d_order1")

    integer, intent(in) :: nlon_in
    integer, intent(in) :: nlat_in
    integer, intent(in) :: nlon_out
    integer, intent(in) :: nlat_out
    real(c_double), intent(in) :: lon_in((nlon_in+1)*(nlat_in+1))
    real(c_double), intent(in) :: lat_in((nlon_in+1)*(nlat_in+1))
    real(c_double), intent(in) :: lon_out((nlon_out+1)*(nlat_out+1))
    real(c_double), intent(in) :: lat_out((nlon_out+1)*(nlat_out+1))
    real(c_double), intent(in) :: mask_in(nlon_in*nlat_in)
    integer, intent(in) :: maxxgrid
    real(c_double), intent(out) :: i_in(maxxgrid)
    real(c_double), intent(out) :: j_in(maxxgrid)
    real(c_double), intent(out) :: i_out(maxxgrid)
    real(c_double), intent(out) :: j_out(maxxgrid)
    real(c_double), intent(out) :: xgrid_area(maxxgrid)

    integer create_xgrid_2dx2d_order1
    integer cFMS_create_xgrid_2dx2d_order1
    
    cFMS_create_xgrid_2dx2d_order1 = create_xgrid_2dx2d_order1(nlon_in, nlat_in, nlon_out, nlat_out, lon_in, lat_in, &
         lon_out, lat_out, mask_in, i_in, j_in, i_out, j_out, xgrid_area)
    
  end function cFMS_create_xgrid_2dx2d_order1

  !cFMS_get_maxxgrid
  function cFMS_get_maxxgrid() bind(C, name="cFMS_get_maxxgrid")

    implicit none
    integer :: get_maxxgrid
    integer :: cFMS_get_maxxgrid

    cFMS_get_maxxgrid = get_maxxgrid()

  end function cFMS_get_maxxgrid

  !cFMS_horiz_interp_init
  subroutine cFMS_horiz_interp_init() bind(C, name="cFMS_horiz_interp_init")

    implicit none
    call fms_horiz_interp_init

  end subroutine cFMS_horiz_interp_init



  
end module c_horiz_interp_mod
