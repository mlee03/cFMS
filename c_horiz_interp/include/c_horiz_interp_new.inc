subroutine CFMS_HORIZ_INTERP_NEW_2D_ (lon_in_ptr, lon_in_shape, lat_in_ptr, lat_in_shape, &
                                               lon_out_ptr, lon_out_shape, lat_out_ptr, lat_out_shape, &
                                               verbose, interp_method, num_nbrs, max_dist, src_modulo, &
                                               mask_in_ptr, mask_in_shape, mask_out_ptr, mask_out_shape, &
                                               is_latlon_in, is_latlon_out, interp_id) bind(C, CFMS_HORIZ_INTERP_NEW_2D_BINDC_)

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
    integer, intent(in), optional :: verbose
    character(c_char), intent(in), optional :: interp_method(MESSAGE_LENGTH)
    integer, intent(in), optional :: num_nbrs
    CFMS_HORIZ_INTERP_NEW_2D_OBJ_DATA_TYPE_, intent(in), optional :: max_dist
    logical(c_bool), intent(in), optional :: src_modulo
    logical(c_bool), intent(in), optional :: is_latlon_in
    logical(c_bool), intent(in), optional :: is_latlon_out

    character(MESSAGE_LENGTH-1) :: interp_method_f

    CFMS_HORIZ_INTERP_NEW_2D_DATA_TYPE_, allocatable :: lon_in(:,:)
    CFMS_HORIZ_INTERP_NEW_2D_DATA_TYPE_, allocatable :: lat_in(:,:)
    CFMS_HORIZ_INTERP_NEW_2D_DATA_TYPE_, allocatable :: lon_out(:,:)
    CFMS_HORIZ_INTERP_NEW_2D_DATA_TYPE_, allocatable :: lat_out(:,:)
    CFMS_HORIZ_INTERP_NEW_2D_DATA_TYPE_, allocatable :: mask_in(:,:)
    CFMS_HORIZ_INTERP_NEW_2D_DATA_TYPE_, allocatable :: mask_out(:,:)

    allocate(lon_in(lon_in_shape(1), lon_in_shape(2)))
    allocate(lat_in(lat_in_shape(1), lat_in_shape(2)))
    allocate(lon_out(lon_out_shape(1), lon_out_shape(2)))
    allocate(lat_out(lat_out_shape(1), lat_out_shape(2)))
    allocate(mask_in(mask_in_shape(1), mask_in_shape(2)))
    allocate(mask_out(mask_out_shape(1), mask_out_shape(2)))

    call cFMS_pointer_to_array(lon_in_ptr, lon_in_shape, lon_in)
    call cFMS_pointer_to_array(lat_in_ptr, lat_in_shape, lat_in)
    call cFMS_pointer_to_array(lon_out_ptr, lon_out_shape, lon_out)
    call cFMS_pointer_to_array(lat_out_ptr, lat_out_shape, lat_out)
    call cFMS_pointer_to_array(mask_in_ptr, mask_in_shape, mask_in)
    call cFMS_pointer_to_array(mask_out_ptr, mask_out_shape, mask_out)

    call cFMS_set_current_interp(interp_id)

    if(present(interp_method)) interp_method_f = fms_c2f_string(interp_method)

    call fms_horiz_interp_new(Interp=current_interp, lon_in=lon_in, lat_in=lat_in, &
                              lat_out=lat_out, verbose=verbose, interp_method=interp_method_f, &
                              num_nbrs=num_nbrs, max_dist=max_dist, src_modulo=src_modulo, &
                              mask_in=mask_in, mask_out=mask_out, is_latlon_in=is_latlon_in, &
                              is_latlon_out=is_latlon_out)

end subroutine CFMS_HORIZ_INTERP_NEW_2D_


  







