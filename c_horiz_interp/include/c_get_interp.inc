subroutine CFMS_GET_INTERP_(ilon_ptr, ilon_shape, jlat_ptr, jlat_shape, i_lon_ptr, &
                            i_lon_shape, j_lat_ptr, j_lat_shape, found_neighbors_ptr, &
                            found_neighbors_shape, num_found_ptr, num_found_shape, &
                            nlon_src, nlat_src, nlon_dst, nlat_dst, interp_method, & 
                            I_am_initialized, version, nxgrid, i_src, j_src, i_dst, &
                            j_dst, faci_ptr, faci_shape, area_src_ptr, area_src_shape, &
                            area_dst_ptr, area_dst_shape, wti_ptr, wti_shape, wtj_ptr, &
                            wtj_shape, src_dist_ptr, src_dist_shape, rat_x_ptr, rat_x_shape, &
                            rat_y_ptr, rat_y_shape, area_frac_dst, verbose, interp_id) bind(C, CFMS_GET_INTERP_BINDC_)

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