#ifndef C_HORIZ_INTERP_H
#define C_HORIZ_INTERP_H

#include <stdbool.h>

extern int cFMS_create_xgrid_2dx2d_order1(int *nlon_in, int *nlat_in, int *nlon_out, int *nlat_out,
                                          double *lon_in, double *lat_in, double *lon_out, double *lat_out,
                                          double *mask_in, int *maxxgrid, int *i_in, int *j_int, int *i_out,
                                          int *j_out, double *xgrid_area);
extern int cFMS_get_maxxgrid();
extern void cFMS_horiz_interp_init();
extern void cFMS_horiz_interp_new_2d_cfloat(float *lon_in_ptr, int *lon_in_shape, float *lat_in_ptr,
                                            int *lat_in_shape, float *lon_out_ptr, int *lon_out_shape,
                                            float *lat_out_ptr, int *lat_out_shape, float *mask_in_ptr,
                                            int *mask_in_shape, float *mask_out_ptr, int* mask_out_shape,
                                            int *verbose, char *interp_method, int *num_nbrs, float *max_dist,
                                            bool *src_modulo, bool *is_latlon_in, bool *is_latlon_out, int *interp_id);
extern void cFMS_horiz_interp_new_2d_cdouble(double *lon_in_ptr, int *lon_in_shape, double *lat_in_ptr,
                                             int *lat_in_shape, double *lon_out_ptr, int *lon_out_shape,
                                             double *lat_out_ptr, int *lat_out_shape, double *mask_in_ptr,
                                             int *mask_in_shape, double *mask_out_ptr, int* mask_out_shape,
                                             int *verbose, char *interp_method, int *num_nbrs, double *max_dist,
                                             bool *src_modulo, bool *is_latlon_in, bool *is_latlon_out, int *interp_id);
extern void cFMS_get_interp_cfloat(int *ilon_ptr, int *ilon_shape, int *jlat_ptr, int *jlat_shape, 
                                   int *i_lon_ptr, int *i_lon_shape, int *j_lat_ptr, int *j_lat_shape,
                                   bool *found_neighbors_ptr, int *found_neighbors_shape, int *num_found_ptr,
                                   int *num_found_shape, int *nlon_src, int *nlat_src, int *nlon_dst,
                                   int *nlat_dst, int *interp_method, bool *I_am_initialized, int *version,
                                   int *nxgrid, int *i_src, int *j_src, int *i_dst, int *j_dst,
                                   float *faci_ptr, int *faci_shape, float *facj_ptr, int *facj_shape,
                                   float *area_src_ptr, int *area_src_shape, float *area_dst_ptr,
                                   int *area_dst_shape, float *wti_ptr, int *wti_shape, float *wtj_ptr,
                                   int *wtj_shape, float *src_dist_ptr, int *src_dist_shape, float *rat_x_ptr,
                                   int *rat_x_shape, float *rat_y_ptr, int *rat_y_shape, float *lon_in,
                                   float *lat_in, float *area_frac_dst, float *mask_in_ptr, int *mask_in_shape,
                                   float *max_src_dist, bool *is_allocated, int *interp_id);
extern void cFMS_get_interp_cdouble(int *ilon_ptr, int *ilon_shape, int *jlat_ptr, int *jlat_shape, 
                                    int *i_lon_ptr, int *i_lon_shape, int *j_lat_ptr, int *j_lat_shape,
                                    bool *found_neighbors_ptr, int *found_neighbors_shape, int *num_found_ptr,
                                    int *num_found_shape, int *nlon_src, int *nlat_src, int *nlon_dst,
                                    int *nlat_dst, int *interp_method, bool *I_am_initialized, int *version,
                                    int *nxgrid, int *i_src, int *j_src, int *i_dst, int *j_dst,
                                    float *faci_ptr, int *faci_shape, float *facj_ptr, int *facj_shape,
                                    float *area_src_ptr, int *area_src_shape, float *area_dst_ptr,
                                    int *area_dst_shape, float *wti_ptr, int *wti_shape, float *wtj_ptr,
                                    int *wtj_shape, float *src_dist_ptr, int *src_dist_shape, float *rat_x_ptr,
                                    int *rat_x_shape, float *rat_y_ptr, int *rat_y_shape, float *lon_in,
                                    float *lat_in, float *area_frac_dst, float *mask_in_ptr, int *mask_in_shape,
                                    float *max_src_dist, bool *is_allocated, int *interp_id);

#endif
