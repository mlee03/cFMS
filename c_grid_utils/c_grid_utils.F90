module c_grid_utils_mod

  use iso_c_binding
  implicit none

  private

  public :: cFMS_get_grid_area

contains

  subroutine cFMS_get_grid_area(nlon, nlat, lon, lat, area) bind(C, name="cFMS_get_grid_area")
    
    implicit none
    integer, intent(in) :: nlon
    integer, intent(in) :: nlat
    real(c_double), intent(in)  :: lon((nlon+1)*(nlat+1))
    real(c_double), intent(in)  :: lat((nlon+1)*(nlat+1))
    real(c_double), intent(out) :: area(nlon*nlat)

    call get_grid_area(nlon, nlat, lon, lat, area)

  end subroutine cFMS_get_grid_area

end module c_grid_utils_mod
