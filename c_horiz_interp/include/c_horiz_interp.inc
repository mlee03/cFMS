subroutine CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_SUB_NAME_(lon_in, lon_in_shape, lat_in, lat_in_shape, &
                                                          lon_out, lon_out_shape, lat_out, lat_out_shape, &
                                                          nlon_src, nlat_src, nlon_dst, nlat_dst, nxgrid, &
                                                          i_src, j_src, i_dst, j_dst, area_frac_dst, &
                                                          mask_in, mask_in_shape, mask_out, mask_out_shape, verbose)
  implicit none
  type(c_ptr), intent(in) :: lon_in
  integer, intent(in) :: lon_in_shape(2)
  type(c_ptr), intent(in) :: lat_in
  integer, intent(in) :: lat_in_shape(2)
  type(c_ptr), intent(in) :: lon_out
  integer, intent(in) :: lon_out_shape(2)
  type(c_ptr), intent(in) :: lat_out
  integer, intent(in) :: lat_out_shape(2)
  integer, intent(out) :: nlon_src                  !> part of HorizInterp obj
  integer, intent(out) :: nlat_src                  !> part of HorizInterp obj
  integer, intent(out) :: nlon_dst                  !> part of HorizInterp obj
  integer, intent(out) :: nlat_dst                  !> part of HorizInterp obj
  integer, intent(inout) :: nxgrid                  !> part of HorizInterp obj
  integer, intent(out) :: i_src(nxgrid)             !> part of HorizInterp obj
  integer, intent(out) :: j_src(nxgrid)             !> part of HorizInterp obj
  integer, intent(out) :: i_dst(nxgrid)             !> part of HorizInterp obj
  integer, intent(out) :: j_dst(nxgrid)             !> part of HorizInterp obj
  integer, intent(out) :: area_frac_dst(nxgrid)     !> part of HorizInterp obj
  type(c_ptr), intent(in), optional :: mask_in
  integer, intent(in), optional :: mask_in_shape(2)
  type(c_ptr), intent(inout), optional :: mask_out
  integer, intent(in), optional :: mask_out_shape(2)
  integer, intent(in), optional :: verbose

  type(FmsHorizInterp_type) :: interp


  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_, pointer :: lon_in_cf(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_POINTER_)
  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: lon_in_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LON_IN_SHAPE_F_)

  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_, pointer :: lat_in_cf(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_POINTER_)
  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: lat_in_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LAT_IN_SHAPE_F_)

  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_, pointer :: lon_out_cf(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_POINTER_)
  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: lon_out_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LON_OUT_SHAPE_F_)

  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_, pointer :: lat_out_cf(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_POINTER_)
  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: lat_out_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LAT_OUT_SHAPE_F_)

  if(present(mask_in)) then
      CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_, pointer :: mask_in_cf(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_POINTER_)
      CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: mask_in_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_MASK_IN_SHAPE_F_)
  end if

  if(present(mask_out)) then
      CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_, pointer :: mask_out_cf(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_POINTER_)
      CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: mask_out_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_MASK_OUT_SHAPE_F_)
  end if

  call c_f_pointer(lon_in, lon_in_cf, (/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LON_IN_SHAPE_CF_/))
  lon_in_f = reshape(lon_in_cf, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LON_IN_SHAPE_F_/), &
                                       order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)

  call c_f_pointer(lat_in, lat_in_cf, (/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LAT_IN_SHAPE_CF_/))
  lat_in_f = reshape(lat_in_cf, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LAT_IN_SHAPE_F_/), &
                                       order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)

  call c_f_pointer(lon_out, lon_out_cf, (/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LON_OUT_SHAPE_CF_/))
  lon_out_f = reshape(lon_out_cf, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LON_OUT_SHAPE_F_/), &
                                         order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)

  call c_f_pointer(lat_out, lat_out_cf, (/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LAT_OUT_SHAPE_CF_/))
  lat_out_f = reshape(lat_out_cf, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LAT_OUT_SHAPE_F_/), &
                                        order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)

  if(present(mask_in)) then
      call c_f_pointer(mask_in, mask_in_cf, (/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_MASK_IN_SHAPE_CF_/))
      mask_in_f = reshape(mask_in_cf, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_MASK_IN_SHAPE_F_/), &
                                             order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)
  end if

  if(present(mask_out)) then
      call c_f_pointer(mask_out, mask_out_cf, (/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_MASK_OUT_SHAPE_CF_/))
      mask_out_f = reshape(mask_out_cf, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_MASK_OUT_SHAPE_F_/), &
                                               order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)
  end if

  call horiz_interp_conserve_new(Interp=interp, lon_in=lon_in_f, lat_in=lat_in_f, lon_out=lon_out_f, lat_out=lat_out_f, &
                                 mask_in=mask_in_f, mask_out=mask_out_f, verbose=verbose)

  nlon_src = interp%nlon_src
  nlat_src = interp%nlat_src
  nlon_dst = interp%nlon_dst
  nlat_dst = interp%nlat_dst
  nxgrid = interp%nxgrid
  i_src = interp%i_src
  j_src = interp%j_src
  i_dst = interp%i_dst
  j_dst = interp%j_dst
  area_frac_dst = interp%CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_%area_frac_dst !> Need to look at this

  lon_in_cf = reshape(lon_in_f, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LON_IN_SHAPE_CF_/), &
                                       order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)

  lat_in_cf = reshape(lat_in_f, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LAT_IN_SHAPE_CF_/), &
                                       order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)

  lon_out_cf = reshape(lon_out_f, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LON_OUT_SHAPE_CF_/), &
                                         order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)

  lat_out_cf = reshape(lat_out_f, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LAT_OUT_SHAPE_CF_/), &
                                        order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)

  if(present(mask_in)) then
    mask_in_cf = reshape(mask_in_f, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_MASK_IN_SHAPE_CF_/), &
                                             order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)
  end if

  if(present(mask_out)) then
    mask_out_cf = reshape(mask_out_f, shape=(/CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_MASK_OUT_SHAPE_CF_/), &
                                               order=CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_RESHAPE_ORDER_)
  end if

end subroutine CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_SUB_NAME_
  







