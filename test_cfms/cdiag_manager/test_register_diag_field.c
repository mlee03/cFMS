#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <cfms.h>
#include <cdiag_manager.h>

#define NX 8
#define NY 8
#define NZ 1

void set_domain(int *domain_id);

int main() 
{

  int domain_id = 0;
  int id_x, id_y, id_z, id_z2;

  int id_var2;
  int var2_shape[2] = {NX, NY};
  float *var2;

  var2 = (float *)malloc(NX*NY*sizeof(float));
  int ij = 0;
  for(int i=0; i<NX; i++) {
    for(int j=0; j<NY; j++) {
      var2[ij] = i*10 + j;
      ij++;
    }
  }
  
  cFMS_init(NULL, NULL, NULL, NULL);  
  
  // define domain
  {
    cDomainStruct cdomain;
    int global_indices[4] = {0, NX-1, 0, NY-1};
    int layout[2] = {1,1};
    int io_layout[2] = {1,1};
    cFMS_null_cdomain(&cdomain);  
    cdomain.domain_id = &domain_id;
    cdomain.global_indices = global_indices;
    cdomain.layout = layout;
    cFMS_define_domains_easy(cdomain);
    cFMS_define_io_domain(io_layout,&domain_id);

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
  
  // register_diag_field var2
  {
    char module_name[NAME_LENGTH] = "atm_mod";
    char field_name[NAME_LENGTH] = "var_2d";
    int axes[5] = {id_y, id_x, 0, 0, 0};
    char long_name[NAME_LENGTH] = "Var in a lon/lat domain";
    char units[NAME_LENGTH] = "muntin";
    float missing_value = -99.99;
    float range[2] = {-1000., 1000.};
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
    int day = 18;
    int hour = 15;
    int minute = 37;
    int second = 11;
    int *tick = NULL;
    
    cFMS_diag_set_field_init_time(&year, &month, &day, &hour, &minute, &second, tick, err_msg);
    id_var2 = cFMS_register_diag_field_array_cfloat(module_name, field_name, axes, long_name, units, &missing_value, range,
                                                    mask_variant, standard_name, verbose, do_not_log, err_msg, interp_method,
                                                    tile_count, area, volume, realm, multiple_send_data);
    int ddays = 0;
    int dseconds = 60*60;
    int dticks = 0;
    cFMS_diag_set_field_timestep(&id_var2, &dseconds, &ddays, &dticks,  NULL);
  }

  // cFMS_diag_set_time_end
  {
    int year = 2025;
    int month = 2;
    int day = 19;
    int hour = 15;
    int minute = 37;
    int second = 11;
    int *tick = NULL;
    cFMS_diag_set_time_end(&year, &month, &day, &hour, &minute, &second, tick, NULL);    
  }
    
  // send_data
  for(int itime=0; itime<24; itime++) {    

    int ij = 0;
    for(int i=0; i<NX; i++){
      for(int j=0; j<NY; j++){
        var2[ij] = -1.0 * var2[ij];
        ij++;
      }
    }
    cFMS_diag_advance_field_time(&id_var2);
    cFMS_diag_send_data_2d_cfloat(&id_var2, var2_shape, var2, NULL);
    cFMS_diag_send_complete(&id_var2, NULL);
  }
  
  cFMS_diag_end();
  
  cFMS_end();
  return EXIT_SUCCESS;
  
}
