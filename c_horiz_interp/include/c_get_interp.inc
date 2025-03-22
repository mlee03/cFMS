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

    if(c_associated(ilon_ptr)) then
        call cFMS_array_to_pointer(current_interp%ilon, ilon_shape, ilon_ptr)
    end if
    if(c_associated(j_lat_ptr)) then
        call cFMS_array_to_pointer(current_interp%jlat, jlat_shape, jlat_ptr)
    end if
    if(c_associated(i_lon_ptr)) then
        call cFMS_array_to_pointer(current_interp%i_lon, i_lon_shape, i_lon_ptr)
    end if
    if(c_associated(j_lat_ptr)) then
        call cFMS_array_to_pointer(current_interp%j_lat, j_lat_shape, j_lat_ptr)
    end if
    if(c_associated(found_neighbors_ptr)) then
        call cFMS_array_to_pointer(current_interp%found_neighbors, found_neighbors_shape, found_neighbors_ptr)
    end if
    if(c_associated(num_found_ptr)) then
        call cFMS_array_to_pointer(current_interp%num_found, num_found_shape, num_found_ptr)
    end if
    if(present(nlon_src)) then
        nlon_src = current_interp%nlon_src
    end if
    if(present(nlat_src)) then
        nlat_src = current_interp%nlat_src
    end if
    if(present(nlon_dst)) then
        nlon_dst = current_interp%nlon_dst
    end if
    if(present(nlat_dst)) then
        nlat_dst = current_interp%nlat_dst
    end if
    if(present(interp_method)) then
        interp_method = current_interp%interp_method
    end if
    if(present(I_am_initialized)) then
        I_am_initialized = current_interp%I_am_initialized
    end if
    if(present(version)) then
        version = current_interp%version
    end if
    if(present(nxgrid)) then
        nxgrid = current_interp%nxgrid
    end if
    if(present(i_src)) then
        i_src = current_interp%i_src
    end if
    if(present(j_src)) then
        j_src = current_interp%j_src
    end if
    if(present(i_dst)) then
        i_dst = current_interp%i_dst
    end if
    if(present(j_dst)) then
        j_dst = current_interp%j_dst
    end if
    if(c_associated(faci_ptr)) then
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%faci, faci_shape, faci_ptr)
    end if
    if(c_associated(facj_ptr)) then
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%facj, facj_shape, facj_ptr)
    end if
    if(c_associated(area_src_ptr)) then
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%area_src, area_src_shape, area_src_ptr)
    end if
    if(c_associated(area_dst_ptr)) then
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%area_dst, area_dst_shape, area_dst_ptr)
    end if
    if(c_associated(wti_ptr)) then
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%wti, wti_shape, wti_ptr)
    end if
    if(c_associated(wtj_ptr)) then
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%wtj, wtj_shape, wtj_ptr)
    end if
    if(c_associated(src_dist_ptr)) then
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%src_dist, src_dist_shape, src_dist_ptr)
    end if
    if(c_associated(rat_x_ptr)) then
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%rat_x, rat_x_shape, rat_x_ptr)
    end if
    if(c_associated(rat_y_ptr)) then
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%rat_y, rat_y_shape, rat_y_ptr)
    end if
    if(present(lon_in)) then
        lon_in = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%lon_in
    end if
    if(present(lat_in)) then
        lat_in = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%lat_in
    end if
    if(present(area_frac_dst)) then
        area_frac_dst = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%area_frac_dst
    end if
    if(c_associated(mask_in_ptr)) then
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%mask_in, mask_in_shape, mask_in_ptr)
    end if
    if(present(max_src_dist)) then
        max_src_dist = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%max_src_dist
    end if
    if(present(is_allocated)) then
        is_allocated = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%is_allocated
    end if

end subroutine CFMS_GET_INTERP_SUB_NAME_


