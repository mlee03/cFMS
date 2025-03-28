#ifndef C_HORIZ_INTERP_H
#define C_HORIZ_INTERP_H

#include <stdbool.h>

extern int cFMS_create_xgrid_2dx2d_order1(int *nlon_in, int *nlat_in, int *nlon_out, int *nlat_out,
                                          double *lon_in, double *lat_in, double *lon_out, double *lat_out,
                                          double *mask_in, int *maxxgrid, int *i_in, int *j_int, int *i_out,
                                          int *j_out, double *xgrid_area);

extern int cFMS_get_maxxgrid();

extern void cFMS_horiz_interp_init(int *ninterp);

extern void cFMS_set_current_interp(int *interp_id);

extern int cFMS_horiz_interp_new_2d_cfloat(float *lon_in_ptr, int *lon_in_shape, float *lat_in_ptr,
                                            int *lat_in_shape, float *lon_out_ptr, int *lon_out_shape,
                                            float *lat_out_ptr, int *lat_out_shape, char *interp_method,
                                            int *verbose, int *num_nbrs, float *max_dist, bool *src_modulo, 
                                            float *mask_in_ptr, int *mask_in_shape, float *mask_out_ptr,
                                            int* mask_out_shape, bool *is_latlon_in, bool *is_latlon_out, 
                                            int *interp_id);

extern int cFMS_horiz_interp_new_2d_cdouble(double *lon_in_ptr, int *lon_in_shape, double *lat_in_ptr,
                                            int *lat_in_shape, double *lon_out_ptr, int *lon_out_shape,
                                            double *lat_out_ptr, int *lat_out_shape, char *interp_method,
                                            int *verbose, int *num_nbrs, double *max_dist, bool *src_modulo, 
                                            double *mask_in_ptr, int *mask_in_shape, double *mask_out_ptr,
                                            int* mask_out_shape, bool *is_latlon_in, bool *is_latlon_out, 
                                            int *interp_id);

extern void cFMS_get_interp_cfloat(int *interp_id, int *nxgrid, int *ilon_ptr, int *ilon_shape, 
                                    int *jlat_ptr, int *jlat_shape, int *i_lon_ptr, int *i_lon_shape,
                                    int *j_lat_ptr, int *j_lat_shape, int *found_neighbors_ptr, 
                                    int *found_neighbors_shape, int *num_found_ptr, int *num_found_shape, 
                                    int *nlon_src, int *nlat_src, int *nlon_dst, int *nlat_dst, 
                                    int *interp_method, bool *I_am_initialized, int *version,
                                    int *i_src_ptr, int *i_src_shape, int *j_src_ptr, int *j_src_shape, 
                                    int *i_dst_ptr, int *i_dst_shape, int *j_dst_ptr, int *j_dst_shape, 
                                    float *faci_ptr, int *faci_shape, float *facj_ptr, int *facj_shape,
                                    float *area_src_ptr, int *area_src_shape, float *area_dst_ptr,
                                    int *area_dst_shape, float *wti_ptr, int *wti_shape, float *wtj_ptr,
                                    int *wtj_shape, float *src_dist_ptr, int *src_dist_shape, float *rat_x_ptr,
                                    int *rat_x_shape, float *rat_y_ptr, int *rat_y_shape, float *lon_in_ptr,
                                    int *lon_in_shape, float *lat_in_ptr, int *lat_in_shape, float *area_frac_dst_ptr, 
                                    int *area_frac_dst_shape, float *mask_in_ptr, int *mask_in_shape, float *max_src_dist, 
                                    bool *is_allocated);
                                   
extern void cFMS_get_interp_cdouble(int *interp_id, int *nxgrid, int *ilon_ptr, int *ilon_shape, 
                                    int *jlat_ptr, int *jlat_shape, int *i_lon_ptr, int *i_lon_shape,
                                    int *j_lat_ptr, int *j_lat_shape, int *found_neighbors_ptr, 
                                    int *found_neighbors_shape, int *num_found_ptr, int *num_found_shape, 
                                    int *nlon_src, int *nlat_src, int *nlon_dst, int *nlat_dst, 
                                    int *interp_method, bool *I_am_initialized, int *version,
                                    int *i_src_ptr, int *i_src_shape, int *j_src_ptr, int *j_src_shape, 
                                    int *i_dst_ptr, int *i_dst_shape, int *j_dst_ptr, int *j_dst_shape, 
                                    double *faci_ptr, int *faci_shape, double *facj_ptr, int *facj_shape,
                                    double *area_src_ptr, int *area_src_shape, double *area_dst_ptr,
                                    int *area_dst_shape, double *wti_ptr, int *wti_shape, double *wtj_ptr,
                                    int *wtj_shape, double *src_dist_ptr, int *src_dist_shape, double *rat_x_ptr,
                                    int *rat_x_shape, double *rat_y_ptr, int *rat_y_shape, double *lon_in_ptr,
                                    int *lon_in_shape, double *lat_in_ptr, int *lat_in_shape, double *area_frac_dst_ptr, 
                                    int *area_frac_dst_shape, double *mask_in_ptr, int *mask_in_shape, double *max_src_dist, 
                                    bool *is_allocated);


#endif
