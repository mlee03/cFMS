#ifndef C_HORIZ_INTERP_H
#define C_HORIZ_INTERP_H

extern int cFMS_create_xgrid_2dx2d_order1(int *nlon_in, int *nlat_in, int *nlon_out, int *nlat_out,
                                          double *lon_in, double *lat_in, double *lon_out, double *lat_out,
                                          double *mask_in, int *maxxgrid, int *i_in, int *j_int, int *i_out,
                                          int *j_out, double *xgrid_area);
extern int cFMS_get_maxxgrid();
extern void cFMS_horiz_interp_init();
extern void cFMS_horiz_interp_new_2d_cfloat();
extern void cFMS_horiz_interp_new_2d_cdouble();
extern void cFMS_get_interp_cfloat();
extern void cFMS_get_interp_cdouble();

#endif
