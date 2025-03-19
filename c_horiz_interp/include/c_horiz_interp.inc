subroutine CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_SUB_NAME_(lon_in_ptr, lon_in_shape, lat_in_ptr, lat_in_shape, &
                                                          lon_out_ptr, lon_out_shape, lat_out_ptr, lat_out_shape, &
                                                          mask_in_ptr, mask_in_shape, mask_out_ptr, mask_out_shape, &
                                                          ilon_ptr, ilon_shape, jlat_ptr, jlat_shape, i_lon_ptr, &
                                                          i_lon_shape, j_lat_ptr, j_lat_shape, found_neighbors_ptr, &
                                                          found_neighbors_shape, num_found_ptr, num_found_shape, &
                                                          nlon_src, nlat_src, nlon_dst, nlat_dst, interp_method, & 
                                                          I_am_initialized, version, nxgrid, i_src, j_src, i_dst, &
                                                          j_dst, faci_ptr, faci_shape, area_src_ptr, area_src_shape, &
                                                          area_dst_ptr, area_dst_shape, wti_ptr, wti_shape, wtj_ptr, &
                                                          wtj_shape, src_dist_ptr, src_dist_shape, rat_x_ptr, rat_x_shape, &
                                                          rat_y_ptr, rat_y_shape, area_frac_dst, verbose, interp_id)
  implicit none
  type(c_ptr), intent(in), value :: lon_in_ptr
  integer, intent(in) :: lon_in_shape(2)
  type(c_ptr), intent(in), value :: lat_in_ptr
  integer, intent(in) :: lat_in_shape(2)
  type(c_ptr), intent(in), value :: lon_out_ptr
  integer, intent(in) :: lon_out_shape(2)
  type(c_ptr), intent(in), value :: lat_out_ptr
  integer, intent(in) :: lat_out_shape(2)
  type(c_ptr), intent(in), value :: mask_in_ptr
  integer, intent(in) :: mask_in_shape(2)
  type(c_ptr), intent(in), value :: mask_out_ptr
  integer, intent(in) :: mask_out_shape(2)

  !> part of HorizInterp obj
  type(c_ptr), intent(in), value :: ilon_ptr
  integer, intent(in) :: ilon_shape(2)  
  type(c_ptr), intent(in), value :: jlat_ptr
  integer, intent(in) :: jlat_shape(2)
  type(c_ptr), intent(in), value :: i_lon_ptr
  integer, intent(in) :: i_lon_shape(3)
  type(c_ptr), intent(in), value  :: j_lat_ptr
  integer, intent(in) :: j_lat_shape(3)
  type(c_ptr), intent(in), value :: found_neighbors_ptr
  integer, intent(in) :: found_neighbors_shape(2)
  type(c_ptr), intent(in), value :: num_found_ptr
  integer, intent(in) :: num_found_shape(2)         
  integer, intent(out) :: nlon_src                  
  integer, intent(out) :: nlat_src                  
  integer, intent(out) :: nlon_dst                  
  integer, intent(out) :: nlat_dst
  integer, intent(inout) :: interp_method
  logical, intent(inout) :: I_am_initialized
  integer, intent(inout) :: version           
  integer, intent(inout) :: nxgrid                  
  integer, intent(out) :: i_src(nxgrid)            
  integer, intent(out) :: j_src(nxgrid)             
  integer, intent(out) :: i_dst(nxgrid)             
  integer, intent(out) :: j_dst(nxgrid)
  type(c_ptr), intent(in), value :: faci_ptr
  integer, intent(in) :: faci_shape(2)
  type(c_ptr), intent(in), value :: facj_ptr
  integer, intent(in) :: facj_shape(2)
  type(c_ptr), intent(in), value :: area_src_ptr
  integer, intent(in) :: area_src_shape(2)
  type(c_ptr), intent(in), value :: area_dst_ptr
  integer, intent(in) :: area_dst_shape(2)
  type(c_ptr), intent(in), value :: wti_ptr
  integer, intent(in) :: wti_shape(3)
  type(c_ptr), intent(in), value :: wtj_ptr
  integer, intent(in) :: wtj_shape(3)
  type(c_ptr), intent(in), value :: src_dist_ptr
  integer, intent(in) :: src_dist_shape(3)
  type(c_ptr), intent(in), value :: rat_x_ptr
  integer, intent(in) :: rat_x_shape(2)
  type(c_ptr), intent(in), value :: rat_y_ptr
  integer, intent(in) :: rat_y_shape(2)       
  CFMS_HORIZ_INTERP_OBJ_DATA_TYPE, intent(out) :: area_frac_dst(nxgrid)     
  integer, intent(in), optional :: verbose
  integer, intent(in), optional :: interp_id

  call cFMS_set_current_interp(interp_id)

  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: lon_in_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LON_IN_SHAPE_F_)
  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: lat_in_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LAT_IN_SHAPE_F_)
  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: lon_out_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LON_OUT_SHAPE_F_)
  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: lat_out_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_LAT_OUT_SHAPE_F_)
  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: mask_in_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_MASK_IN_SHAPE_F_)
  CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_DATA_TYPE_ :: mask_out_f(CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_MASK_OUT_SHAPE_F_)
  integer :: ilon_f(ilon_shape(1), ilon_shape(2))
  integer :: jlat_f(j_lat_shape(1), j_lat_shape(2))
  integer :: i_lon_f(i_lon_shape(1), i_lon_shape(2), i_lon_shape(3))
  integer :: j_lat_f(j_lat_shape(1), j_lat_shape(2), j_lat_shape(3))
  integer :: found_neighbors_f(found_neighbors_shape(1), found_neighbors_shape(2))
  integer :: num_found_f(num_found_shape(1), num_found_shape(2))
  CFMS_HORIZ_INTERP_OBJ_DATA_TYPE :: faci_f(faci_shape(1), faci_shape(2))
  CFMS_HORIZ_INTERP_OBJ_DATA_TYPE :: facj_f(facj_shape(1), facj_shape(2))
  CFMS_HORIZ_INTERP_OBJ_DATA_TYPE :: area_src_f(area_src_shape(1), area_src_shape(2))
  CFMS_HORIZ_INTERP_OBJ_DATA_TYPE :: area_dst_f(area_dst_shape(1), area_dst_shape(2))
  CFMS_HORIZ_INTERP_OBJ_DATA_TYPE :: wti_f(wti_shape(1), wti_shape(2), wti_shape(3))
  CFMS_HORIZ_INTERP_OBJ_DATA_TYPE :: wtj_f(wtj_shape(1), wtj_shape(2), wtj_shape(3))
  CFMS_HORIZ_INTERP_OBJ_DATA_TYPE :: src_dist_f(src_dist_shape(1), src_dist_shape(2), src_dist_shape(3))
  CFMS_HORIZ_INTERP_OBJ_DATA_TYPE :: rat_x_f(rat_x_shape(1), rat_x_shape(2))
  CFMS_HORIZ_INTERP_OBJ_DATA_TYPE :: rat_y_f(rat_y_shape(1), rat_y_shape(2))

  call cFMS_pointer_to_array(lon_in_ptr, lon_in_shape, lon_in_f)
  call cFMS_pointer_to_array(lat_in_ptr, lat_in_shape, lat_in_f)
  call cFMS_pointer_to_array(lon_out_ptr, lon_out_shape, lon_out_f)
  call cFMS_pointer_to_array(lat_out_ptr, lat_out_shape, lat_out_f)
  call cFMS_pointer_to_array(mask_in_ptr, mask_in_shape, mask_in_f)
  call cFMS_pointer_to_array(mask_out_ptr, mask_out_shape, mask_out_f)
  call cFMS_pointer_to_array(ilon_ptr, ilon_shape, ilon_f)
  call cFMS_pointer_to_array(jlat_ptr, jlat_shape, jlat_f)
  call cFMS_pointer_to_array(i_lon_ptr, i_lon_shape, i_lon_f)
  call cFMS_pointer_to_array(j_lat_ptr, j_lat_shape, j_lat_f)
  call cFMS_pointer_to_array(found_neighbors_ptr, found_neighbors_shape, found_neighbors_f)
  call cFMS_pointer_to_array(num_found_ptr, num_found_shape, num_found_f)
  call cFMS_pointer_to_array(faci_ptr, faci_shape, faci_f)
  call cFMS_pointer_to_array(facj_ptr, facj_shape, facj_f)
  call cFMS_pointer_to_array(area_src_ptr, area_src_shape, area_src_f)
  call cFMS_pointer_to_array(area_dst_ptr, area_dst_shape, area_dst_f)
  call cFMS_pointer_to_array(wti_ptr, wti_shape, wti_f)
  call cFMS_pointer_to_array(wtj_ptr, wtj_shape, wtj_f)
  call cFMS_pointer_to_array(src_dist_ptr, src_dist_shape, src_dist_f)
  call cFMS_pointer_to_array(rat_x_ptr, rat_x_shape, rat_x_f)
  call cFMS_pointer_to_array(rat_y_ptr, rat_y_shape, rat_y_f)

  call horiz_interp_conserve_new(Interp=current_interp, lon_in=lon_in_f, lat_in=lat_in_f, lon_out=lon_out_f, lat_out=lat_out_f, &
                                 mask_in=mask_in_f, mask_out=mask_out_f, verbose=verbose)

  
  !> Need to test functionality of this method of accessing
  ilon_f = current_interp%ilon
  jlat_f = current_interp%jlat
  i_lon_f = current_interp%i_lon
  j_lat_f = current_interp%j_lat
  found_neighbors_f = current_interp%found_neighbors
  num_found_f = current_interp%num_found
  nlon_src = current_interp%nlon_src
  nlat_src = current_interp%nlat_src
  nlon_dst = current_interp%nlon_dst
  nlat_dst = current_interp%nlat_dst
  interp_method = current_interp%interp_method
  I_am_initialized = current_interp%I_am_initialized
  version = current_interp%version
  nxgrid = current_interp%nxgrid
  i_src = current_interp%i_src
  j_src = current_interp%j_src
  i_dst = current_interp%i_dst
  j_dst = current_interp%j_dst
  faci_f = current_interp%faci
  facj_f = current_interp%facj
  area_src_f = current_interp%area_src
  area_dst_f = current_interp%area_dst
  wti_f = current_interp%wti_f
  wtj_f = current_interp%wtj_f
  src_dist_f = current_interp%src_dist
  rat_x_f = current_interp%rat_x
  rat_y_f = current_interp%rat_y
  if(allocated(current_interp%horizInterpReals4_type%area_frac_dst)) then
      area_frac_dst = current_interp%horizInterpReals4_type%area_frac_dst
  end if
  if(allocated(current_interp%horizInterpReals8_type%area_frac_dst)) then
      area_frac_dst = current_interp%horizInterpReals8_type%area_frac_dst
  end if

end subroutine CFMS_HORIZ_INTERP_CONSERVE_NEW_2DX2D_SUB_NAME_
  







