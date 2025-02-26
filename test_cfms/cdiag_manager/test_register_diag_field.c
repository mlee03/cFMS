#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <cfms.h>
#include <cdiag_manager.h>

#define NX 96
#define NY 96
#define NZ 5

void set_domain(int *domain_id);

int main() 
{

  int domain_id = 0;
  int id_x, id_y, id_z, id_z2;
  int id_var1, id_var2, id_var6, id_var7;
  
  cFMS_init(NULL, NULL, NULL, NULL);  

  // define domain
  {
    cDomainStruct cdomain;
    int global_indices[4] = {0, 96, 0, 96};
    int layout[2] = {2,2};
    cFMS_null_cdomain(&cdomain);  
    cdomain.domain_id = &domain_id;
    cdomain.global_indices = global_indices;
    cdomain.layout = layout;
    cFMS_define_domains_easy(cdomain);
  }
  
  // diag manager init
  {
    int  diag_model_subset = DIAG_ALL;
    int  time_init[6] = {2025, 1, 27, 14, 10, 0};
    int  calendar_type = NOLEAP;
    char err_msg[NAME_LENGTH] = "None";
    cFMS_diag_init(&diag_model_subset, time_init, &calendar_type, err_msg);
  }

  //diag axis init x
  {    
    char name[NAME_LENGTH] = "x";
    int naxis_data = NX;
    double x[NX];
    char units[NAME_LENGTH] = "point_E";
    char cart_name[NAME_LENGTH] = "x";
    char long_name[NAME_LENGTH] = "point_E";
    char set_name[NAME_LENGTH] = "land";
    int *direction = NULL;
    int *edges = NULL;
    char *aux = NULL;
    char *req = NULL;
    int *tile_count = NULL;
    int *domain_position = NULL;

    for(int i=0; i<NX; i++) x[i] = i;
    
    id_x = cFMS_diag_axis_init_cdouble(name, &naxis_data, x, units, cart_name, long_name, direction, 
                                       set_name, edges, aux, req, tile_count, domain_position);
  }
  
  //diag axis init y
  {    
    char name[NAME_LENGTH] = "y";
    int naxis_data = NY;
    double y[NY];
    char units[NAME_LENGTH] = "point_N";
    char cart_name[NAME_LENGTH] = "y";
    char long_name[NAME_LENGTH] = "point_N";
    char set_name[NAME_LENGTH] = "land";
    int *direction = NULL;
    int *edges = NULL;
    char *aux = NULL;
    char *req = NULL;
    int *tile_count = NULL;
    int *domain_position = NULL;

    for(int j=0; j<NY; j++) y[j] = j;
    
    id_y = cFMS_diag_axis_init_cdouble(name, &naxis_data, y, units, cart_name, long_name, direction, 
                                       set_name, edges, aux, req, tile_count, domain_position);
  }

  //diag axis init z2
  {    
    char name[NAME_LENGTH] = "z_edge";
    int naxis_data = NZ;
    double z[NZ];
    char units[NAME_LENGTH] = "point_Z";
    char cart_name[NAME_LENGTH] = "z";
    char long_name[NAME_LENGTH] = "point_Z";
    char *set_name = NULL;
    int *direction = NULL;
    int *edges = NULL;
    char *aux = NULL;
    char *req = NULL;
    int *tile_count = NULL;
    int *domain_position = NULL;

    for(int k=0; k<NZ; k++) z[k] = k;
    
    id_z2 = cFMS_diag_axis_init_cdouble(name, &naxis_data, z, units, cart_name, long_name, direction,
                                        set_name, edges, aux, req, tile_count, domain_position);
  }
    
  //diag axis init z
  {    
    char name[NAME_LENGTH] = "z";
    int naxis_data = NZ;
    double z[NZ];
    char units[NAME_LENGTH] = "point_Z";
    char cart_name[NAME_LENGTH] = "z";
    char long_name[NAME_LENGTH] = "point_Z";
    char *set_name = NULL;
    int *direction = NULL;
    int edges = id_z2;
    char *aux = NULL;
    char *req = NULL;
    int *tile_count = NULL;
    int *domain_position = NULL;

    for(int k=0; k<NZ; k++) z[k] = k;
    
    id_z = cFMS_diag_axis_init_cdouble(name, &naxis_data, z, units, cart_name, long_name, direction,
                                       set_name, &edges, aux, req, tile_count, domain_position);
  }

  //diag_axis_add_attribute
  {
  }

  // register_diag_field var1
  {
    char module_name[NAME_LENGTH] = "ocn_mod";
    char field_name[NAME_LENGTH] = "var1";
    int axes[5] = {id_x, id_y, 0, 0, 0};
    char long_name[NAME_LENGTH] = "Var in a lon/lat domain";
    char units[NAME_LENGTH] = "muntin";
    double missing_value = -99.99;
    double range[2] = {-1000.0, 1000.0};
    bool *mask_variant = NULL;
    char *standard_name = NULL;
    bool *verbose = NULL;
    bool *do_not_log = NULL;
    char *interp_method = NULL;
    int *tile_count = NULL;
    int *area = NULL;
    int *volume = NULL;
    char *realm = NULL;
    bool *multiple_send_data = NULL;

    char err_msg[MESSAGE_LENGTH]="None";
    
    int year = 2025;
    int month = 2;
    int day = 18 ;
    int hour = 15;
    int minute = 37;
    int second = 11;
    int *tick = NULL;
    
    cFMS_diag_set_field_init_time(&year, &month, &day, &hour, &minute, &second, tick, err_msg);
    id_var1 = cFMS_register_diag_field_array_cdouble(module_name, field_name, axes, long_name, units, &missing_value, range,
                                                     mask_variant, standard_name, verbose, do_not_log, err_msg, interp_method,
                                                     tile_count, area, volume, realm, multiple_send_data);
  }

  // register_diag_field var2
  {
    char module_name[NAME_LENGTH] = "ocn_mod";
    char field_name[NAME_LENGTH] = "var2";
    int axes[5] = {id_y, id_x, 0, 0, 0};
    char long_name[NAME_LENGTH] = "Var in a lon/lat domain with flipped dimensions";
    char units[NAME_LENGTH] = "muntin";
    double missing_value = -99.99;
    double range[2] = {-1000.0, 1000.0};
    bool *mask_variant = NULL;
    char *standard_name = NULL;
    bool *verbose = NULL;
    bool *do_not_log = NULL;
    char *interp_method = NULL;
    int *tile_count = NULL;
    int *area = NULL;
    int *volume = NULL;
    char *realm = NULL;
    bool *multiple_send_data = NULL;

    char err_msg[MESSAGE_LENGTH];
    
    int year = 2025;
    int month = 2;
    int day = 18 ;
    int hour = 15;
    int minute = 37;
    int second = 11;
    int *tick = NULL;
    
    cFMS_diag_set_field_init_time(&year, &month, &day, &hour, &minute, &second, tick, err_msg);      
    id_var2 = cFMS_register_diag_field_array_cdouble(module_name, field_name, axes, long_name, units, &missing_value, range,
                                                     mask_variant, standard_name, verbose, do_not_log, err_msg, interp_method,
                                                     tile_count, area, volume, realm, multiple_send_data);    
  }

  // register_diag_field var6
  {
    char module_name[NAME_LENGTH] = "atm_mod";
    char field_name[NAME_LENGTH] = "var6";
    int axes[5] = {id_z, 0, 0, 0, 0};
    char long_name[NAME_LENGTH] = "Var not domain decomposed";
    char units[NAME_LENGTH] = "muntin";
    double missing_value = -99.99;
    double range[2] = {-1000.0, 1000.0};
    bool *mask_variant = NULL;
    char *standard_name = NULL;
    bool *verbose = NULL;
    bool *do_not_log = NULL;
    char *interp_method = NULL;
    int *tile_count = NULL;
    int *area = NULL;
    int *volume = NULL;
    char *realm = NULL;
    bool *multiple_send_data = NULL;

    char err_msg[NAME_LENGTH];
    
    int year = 2025;
    int month = 2;
    int day = 18 ;
    int hour = 15;
    int minute = 37;
    int second = 11;
    int *tick = NULL;
    
    cFMS_diag_set_field_init_time(&year, &month, &day, &hour, &minute, &second, tick, err_msg);      
    id_var6 = cFMS_register_diag_field_array_cdouble(module_name, field_name, axes, long_name, units, &missing_value, range,
                                                     mask_variant, standard_name, verbose, do_not_log, err_msg, interp_method,
                                                     tile_count, area, volume, realm, multiple_send_data);    
  }

  //var7
  {
    char module_name[NAME_LENGTH] = "land_mod";
    char field_name[NAME_LENGTH] = "var1";
    char long_name[NAME_LENGTH] = "Some scalar var";
    char units[NAME_LENGTH] = "muntin";
    double missing_value = -99.99;
    double range[2] = {-1000.0, 1000.0};
    char *standard_name = NULL;
    bool *do_not_log = NULL;
    int *area = NULL;
    int *volume = NULL;
    char *realm = NULL;
    bool *multiple_send_data = NULL;

    char err_msg[NAME_LENGTH];
    
    int year = 2025;
    int month = 2;
    int day = 18 ;
    int hour = 15;
    int minute = 37;
    int second = 11;
    int *tick = NULL;
    
    cFMS_diag_set_field_init_time(&year, &month, &day, &hour, &minute, &second, tick, err_msg);      
    id_var7 = cFMS_register_diag_field_scalar_cdouble(module_name, field_name, long_name, units, &missing_value,
                                                      range, standard_name, do_not_log, err_msg, area, volume,
                                                      realm, multiple_send_data);
  }

  //cFMS_diag_end
  {
    int year = 2025;
    int month = 2;
    int day = 25 ;
    int hour = 7;
    int minute = 49;
    int second = 7;
    int *tick = NULL;
    char *err_msg = NULL;
        
    cFMS_diag_set_field_curr_time(&year, &month, &day, &hour, &minute, &second, tick, err_msg);
    cFMS_diag_end();
  }
  
  cFMS_end();
  return EXIT_SUCCESS;
  
}
