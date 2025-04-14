subroutine CFMS_GET_INTERP_NAME_(interp_id, nxgrid, ilon_ptr, ilon_shape, jlat_ptr, jlat_shape, &
    i_lon_ptr, i_lon_shape, j_lat_ptr, j_lat_shape, found_neighbors_ptr, found_neighbors_shape, &
    num_found_ptr, num_found_shape, nlon_src, nlat_src, nlon_dst, nlat_dst, interp_method, &
    I_am_initialized, version, i_src_ptr, i_src_shape, j_src_ptr, j_src_shape, i_dst_ptr, i_dst_shape, &
    j_dst_ptr, j_dst_shape, faci_ptr, faci_shape, facj_ptr, facj_shape, area_src_ptr, area_src_shape, &
    area_dst_ptr, area_dst_shape, wti_ptr, wti_shape, wtj_ptr, wtj_shape, src_dist_ptr, src_dist_shape, &
    rat_x_ptr, rat_x_shape, rat_y_ptr, rat_y_shape, lon_in_ptr, lon_in_shape, lat_in_ptr, lat_in_shape, &
    area_frac_dst_ptr, area_frac_dst_shape, mask_in_ptr, mask_in_shape, max_src_dist, is_allocated) &
    bind(C, name=CFMS_GET_INTERP_BINDC_)

    integer, intent(in), optional :: interp_id
    integer, intent(out), optional :: nxgrid
    type(c_ptr), intent(in), value :: ilon_ptr
    integer, intent(in), optional :: ilon_shape(2)  
    type(c_ptr), intent(in), value :: jlat_ptr
    integer, intent(in), optional :: jlat_shape(2)
    type(c_ptr), intent(in), value :: i_lon_ptr
    integer, intent(in), optional :: i_lon_shape(3)
    type(c_ptr), intent(in), value  :: j_lat_ptr
    integer, intent(in), optional :: j_lat_shape(3)
    type(c_ptr), intent(in), value :: found_neighbors_ptr
    integer, intent(in), optional :: found_neighbors_shape(2)
    type(c_ptr), intent(in), value :: num_found_ptr
    integer, intent(in), optional :: num_found_shape(2)         
    integer, intent(out), optional :: nlon_src                  
    integer, intent(out), optional :: nlat_src                  
    integer, intent(out), optional :: nlon_dst                  
    integer, intent(out), optional :: nlat_dst
    integer, intent(out), optional :: interp_method
    logical, intent(out), optional :: I_am_initialized
    integer, intent(out), optional :: version                  
    type(c_ptr), intent(in), value :: i_src_ptr
    integer, intent(in), optional :: i_src_shape            
    type(c_ptr), intent(in), value :: j_src_ptr
    integer, intent(in), optional :: j_src_shape            
    type(c_ptr), intent(in), value :: i_dst_ptr
    integer, intent(in), optional :: i_dst_shape             
    type(c_ptr), intent(in), value :: j_dst_ptr
    integer, intent(in), optional :: j_dst_shape
    type(c_ptr), intent(in), value :: faci_ptr
    integer, intent(in), optional :: faci_shape(2)
    type(c_ptr), intent(in), value :: facj_ptr
    integer, intent(in), optional :: facj_shape(2)
    type(c_ptr), intent(in), value :: area_src_ptr
    integer, intent(in), optional :: area_src_shape(2)
    type(c_ptr), intent(in), value :: area_dst_ptr
    integer, intent(in), optional :: area_dst_shape(2)
    type(c_ptr), intent(in), value :: wti_ptr
    integer, intent(in), optional :: wti_shape(3)
    type(c_ptr), intent(in), value :: wtj_ptr
    integer, intent(in), optional :: wtj_shape(3)
    type(c_ptr), intent(in), value :: src_dist_ptr
    integer, intent(in), optional :: src_dist_shape(3)
    type(c_ptr), intent(in), value :: rat_x_ptr
    integer, intent(in), optional :: rat_x_shape(2)
    type(c_ptr), intent(in), value :: rat_y_ptr
    integer, intent(in), optional :: rat_y_shape(2)
    type(c_ptr), intent(in), value :: lon_in_ptr
    integer, intent(in), optional :: lon_in_shape
    type(c_ptr), intent(in), value :: lat_in_ptr
    integer, intent(in), optional :: lat_in_shape       
    type(c_ptr), intent(in), value :: area_frac_dst_ptr
    integer, intent(in), optional :: area_frac_dst_shape
    type(c_ptr), intent(in), value :: mask_in_ptr
    integer, intent(in), optional :: mask_in_shape(2)
    CFMS_GET_INTERP_DATA_TYPE_, intent(out), optional :: max_src_dist
    logical(c_bool), intent(out), optional :: is_allocated

    integer, pointer :: i_src_cf(:)
    integer, pointer :: j_src_cf(:)
    integer, pointer :: i_dst_cf(:)
    integer, pointer :: j_dst_cf(:)
    CFMS_GET_INTERP_DATA_TYPE_, pointer :: lon_in_cf(:)
    CFMS_GET_INTERP_DATA_TYPE_, pointer :: lat_in_cf(:)
    CFMS_GET_INTERP_DATA_TYPE_, pointer :: area_frac_dst_cf(:)

    call cFMS_set_current_interp(interp_id)

    if(C_ASSOCIATED(ilon_ptr) .and. PRESENT(ilon_shape)) &
        call cFMS_array_to_pointer(current_interp%ilon, ilon_shape, ilon_ptr)

    if(C_ASSOCIATED(jlat_ptr) .and. PRESENT(jlat_shape)) &
        call cFMS_array_to_pointer(current_interp%jlat, jlat_shape, jlat_ptr)

    if(C_ASSOCIATED(i_lon_ptr) .and. PRESENT(i_lon_shape)) &
        call cFMS_array_to_pointer(current_interp%i_lon, i_lon_shape, i_lon_ptr)

    if(C_ASSOCIATED(j_lat_ptr) .and. PRESENT(j_lat_shape)) &
        call cFMS_array_to_pointer(current_interp%j_lat, j_lat_shape, j_lat_ptr)
    
    if(C_ASSOCIATED(found_neighbors_ptr) .and. PRESENT(found_neighbors_shape)) &
        call cFMS_array_to_pointer(current_interp%found_neighbors, found_neighbors_shape, found_neighbors_ptr)
    
    if(C_ASSOCIATED(num_found_ptr) .and. PRESENT(num_found_shape)) &
        call cFMS_array_to_pointer(current_interp%num_found, num_found_shape, num_found_ptr)

    if(PRESENT(nlon_src)) nlon_src = current_interp%nlon_src

    if(PRESENT(nlat_src)) nlat_src = current_interp%nlat_src
    
    if(PRESENT(nlon_dst)) nlon_dst = current_interp%nlon_dst
    
    if(PRESENT(nlat_dst)) nlat_dst = current_interp%nlat_dst
    
    if(PRESENT(interp_method)) interp_method = current_interp%interp_method
    
    if(PRESENT(I_am_initialized)) I_am_initialized = current_interp%I_am_initialized

    if(PRESENT(version)) version = current_interp%version

    if(PRESENT(nxgrid)) nxgrid = current_interp%nxgrid

    if(C_ASSOCIATED(i_src_ptr) .and. PRESENT(i_src_shape)) then
        call C_F_POINTER(i_src_ptr, i_src_cf, shape=(/i_src_shape/))
        i_src_cf = current_interp%i_src
    end if
    
    if(C_ASSOCIATED(j_src_ptr) .and. PRESENT(j_src_shape)) then
        call C_F_POINTER(j_src_ptr, j_src_cf, shape=(/j_src_shape/))
        j_src_cf = current_interp%j_src
    end if

    if(C_ASSOCIATED(i_dst_ptr) .and. PRESENT(i_dst_shape)) then
        call C_F_POINTER(i_dst_ptr, i_dst_cf, shape=(/i_dst_shape/))
        i_dst_cf = current_interp%i_dst
    end if

    if(C_ASSOCIATED(j_dst_ptr) .and. PRESENT(j_dst_shape)) then
        call C_F_POINTER(j_dst_ptr, j_dst_cf, shape=(/j_dst_shape/))
        j_dst_cf = current_interp%j_dst
    end if

    if(C_ASSOCIATED(faci_ptr) .and. PRESENT(faci_shape)) &
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%faci, faci_shape, faci_ptr)
    
    if(C_ASSOCIATED(facj_ptr) .and. PRESENT(facj_shape)) &
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%facj, facj_shape, facj_ptr)
    
    if(C_ASSOCIATED(area_src_ptr) .and. PRESENT(area_src_shape)) &
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%area_src, area_src_shape, area_src_ptr)
    
    if(C_ASSOCIATED(area_dst_ptr) .and. PRESENT(area_dst_shape)) &
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%area_dst, area_dst_shape, area_dst_ptr)
    
    if(C_ASSOCIATED(wti_ptr) .and. PRESENT(wti_shape)) &
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%wti, wti_shape, wti_ptr)
    
    if(C_ASSOCIATED(wtj_ptr) .and. PRESENT(wtj_shape)) &
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%wtj, wtj_shape, wtj_ptr)
    
    if(C_ASSOCIATED(src_dist_ptr) .and. PRESENT(src_dist_shape)) &
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%src_dist, src_dist_shape, src_dist_ptr)
    
    if(C_ASSOCIATED(rat_x_ptr) .and. PRESENT(rat_x_shape)) &
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%rat_x, rat_x_shape, rat_x_ptr)
    
    if(C_ASSOCIATED(rat_y_ptr) .and. PRESENT(rat_y_shape)) &
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%rat_y, rat_y_shape, rat_y_ptr)
    
    if(C_ASSOCIATED(lon_in_ptr) .and. PRESENT(lon_in_shape)) then
        call C_F_POINTER(lon_in_ptr, lon_in_cf, shape=(/lon_in_shape/))
        lon_in_cf = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%lon_in
    end if

    if(C_ASSOCIATED(lat_in_ptr) .and. PRESENT(lat_in_shape)) then
        call C_F_POINTER(lat_in_ptr, lat_in_cf, shape=(/lat_in_shape/))
        lat_in_cf = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%lat_in
    end if

    if(C_ASSOCIATED(area_frac_dst_ptr) .and. PRESENT(area_frac_dst_shape)) then
        call C_F_POINTER(area_frac_dst_ptr, area_frac_dst_cf, shape=(/area_frac_dst_shape/))
        area_frac_dst_cf = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%area_frac_dst
    end if

    if(C_ASSOCIATED(mask_in_ptr) .and. PRESENT(mask_in_shape)) &
        call cFMS_array_to_pointer(current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%mask_in, mask_in_shape, mask_in_ptr)
    
    if(PRESENT(max_src_dist)) max_src_dist = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%max_src_dist
    
    if(PRESENT(is_allocated)) is_allocated = current_interp%CFMS_GET_INTERP_OBJ_DATA_TYPE_%is_allocated


    NULLIFY(i_src_cf)
    NULLIFY(j_src_cf)
    NULLIFY(i_dst_cf)
    NULLIFY(j_dst_cf)
    NULLIFY(lon_in_cf)
    NULLIFY(lat_in_cf)
    NULLIFY(area_frac_dst_cf)

end subroutine CFMS_GET_INTERP_NAME_


