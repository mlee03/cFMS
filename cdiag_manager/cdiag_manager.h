#ifndef CDIAG_MANAGER_H
#define CDIAG_MANAGER_H

#include <stdbool.h>

extern const int DIAG_OTHER;
extern const int DIAG_OCEAN;
extern const int DIAG_ALL;

extern const int THIRTY_DAY_MONTHS;
extern const int GREGORIAN;
extern const int JULIAN;
extern const int NOLEAP;

extern void cFMS_diag_init(int *diag_model_subset, int *time_init, int *calendar_type, char *err_msg);

extern int cFMS_diag_axis_init_cfloat(char *name, int *naxis_data, float *axis_data, char *units, char *cart_name,
                                      char *long_name, int *direction, char *set_name, int *edges, char *aux,
                                      char *req, int *tile_count, int *domain_position);

extern int cFMS_diag_axis_init_cdouble(char *name, int *naxis_data, double *axis_data, char *units, char *cart_name,
                                       char *long_name, int *direction, char *set_name, int *edges, char *aux,
                                       char *req, int *tile_count, int *domain_position);

extern void cFMS_diag_end();

extern void cFMS_diag_set_field_init_time(int *year, int *month, int *day, int *hour, int *minute, int *second,
                                          int *tick, char *err_msg);


extern void cFMS_diag_set_field_curr_time(int *year, int *month, int *day, int *hour, int *minute, int *second,
                                          int *tick, char *err_msg); 

extern int cFMS_register_diag_field_scalar_int(char *module_name, char *field_name, char *long_name,
                                               char *units, int *missing_value, int *range,
                                               char *standard_name, bool *do_not_log, char *err_msg,
                                               int *area, int *volume, char *realm, bool *multiple_send_data);

extern int cFMS_register_diag_field_scalar_cfloat(char *module_name, char *field_name, char *long_name,
                                                  char *units, float *missing_value, float *range,
                                                  char *standard_name, bool *do_not_log, char *err_msg,
                                                  int *area, int *volume, char *realm, bool *multiple_send_data);

extern int cFMS_register_diag_field_scalar_cdouble(char *module_name, char *field_name, char *long_name,
                                                   char *units, double *missing_value, double *range,
                                                   char *standard_name, bool *do_not_log, char *err_msg,
                                                   int *area, int *volume, char *realm, bool *multiple_send_data);

extern int cFMS_register_diag_field_array_cfloat(char *module_name, char *field_name, int *axes, char *long_name,
                                                 char *units, float *missing_value, float *range, bool *mask_variant,
                                                 char *standard_name, bool *verbose, bool *do_not_log, char *err_msg,
                                                 char *interp_method, int *tile_count, int *area, int *volume,
                                                 char *realm, bool *multiple_send_data);

extern int cFMS_register_diag_field_array_cdouble(char *module_name, char *field_name, int *axes, char *long_name,
                                                  char *units, double *missing_value, double *range, bool *mask_variant,
                                                  char *standard_name, bool *verbose, bool *do_not_log, char *err_msg,
                                                  char *interp_method, int *tile_count, int *area, int *volume,
                                                  char *realm, bool *multiple_send_data);                                                 

#endif
