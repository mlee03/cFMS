subroutine CFMS_GET_INTERP_SUB_NAME_(ilon_ptr, ilon_shape, jlat_ptr, jlat_shape, i_lon_ptr, &
                            i_lon_shape, j_lat_ptr, j_lat_shape, found_neighbors_ptr, &
                            found_neighbors_shape, num_found_ptr, num_found_shape, &
                            nlon_src, nlat_src, nlon_dst, nlat_dst, interp_method, & 
                            I_am_initialized, version, nxgrid, i_src, j_src, i_dst, &
                            j_dst, faci_ptr, faci_shape, area_src_ptr, area_src_shape, &
                            area_dst_ptr, area_dst_shape, wti_ptr, wti_shape, wtj_ptr, &
                            wtj_shape, src_dist_ptr, src_dist_shape, rat_x_ptr, rat_x_shape, &
                            rat_y_ptr, rat_y_shape, lon_in, lat_in, area_frac_dst, mask_in, &
                            max_src_dist, is_allocated, interp_id) bind(C, CFMS_GET_INTERP_BINDC_)

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
    integer, intent(out), optional :: nlon_src                  
    integer, intent(out), optional :: nlat_src                  
    integer, intent(out), optional :: nlon_dst                  
    integer, intent(out), optional :: nlat_dst
    integer, intent(out), optional :: interp_method
    logical, intent(out), optional :: I_am_initialized
    integer, intent(out), optional :: version           
    integer, intent(inout), optional :: nxgrid                  
    integer, intent(out), optional :: i_src(nxgrid)            
    integer, intent(out), optional :: j_src(nxgrid)             
    integer, intent(out), optional :: i_dst(nxgrid)             
    integer, intent(out), optional :: j_dst(nxgrid)
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
    CFMS_GET_INTERP_DATA_TYPE_, intent(out), optional :: lon_in(nxgrid)
    CFMS_GET_INTERP_DATA_TYPE_, intent(out), optional :: lat_in(nxgrid)       
    CFMS_GET_INTERP_DATA_TYPE_, intent(out), optional :: area_frac_dst(nxgrid)
    type(c_ptr), intent(in), value :: mask_in_ptr
    integer, intent(in) :: mask_in_shape
    CFMS_GET_INTERP_DATA_TYPE_, intent(out) :: max_src_dist
    logical(c_bool), intent(out) :: is_allocated
    integer, intent(in), optional :: interp_id

    call cFMS_set_current_interp(interp_id)

    call cFMS_array_to_pointer(current_interp%ilon, ilon_shape, ilon_ptr)
    call cFMS_array_to_pointer(current_interp%jlat, jlat_shape, jlat_ptr)
    call cFMS_array_to_pointer(current_interp%i_lon, i_lon_shape, i_lon_ptr)
    call cFMS_array_to_pointer(current_interp%j_lat, j_lat_shape, j_lat_ptr)
    call cFMS_array_to_pointer(current_interp%found_neighbors, found_neighbors_shape, found_neighbors_ptr)
    call cFMS_array_to_pointer(current_interp%num_found, num_found_shape, num_found_ptr)
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
    call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%faci, faci_shape, faci_ptr)
    call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%facj, facj_shape, facj_ptr)
    call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%area_src, area_src_shape, area_src_ptr)
    call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%area_dst, area_dst_shape, area_dst_ptr)
    call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%wti, wti_shape, wti_ptr)
    call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%wtj, wtj_shape, wtj_ptr)
    call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%src_dist, src_dist_shape, src_dist_ptr)
    call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%rat_x, rat_x_shape, rat_x_ptr)
    call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%rat_y, rat_y_shape, rat_y_ptr)
    lon_in = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%lon_in
    lat_in = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%lat_in
    area_frac_dst = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%area_frac_dst
    call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%mask_in, mask_in_shape, mask_in_ptr)
    max_src_dist = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%max_src_dist
    is_allocated = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%is_allocated

end subroutine CFMS_GET_INTERP_SUB_NAME_


