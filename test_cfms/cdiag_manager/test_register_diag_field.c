#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <cfms.h>
#include <cdiag_manager.h>

void set_domain(int *domain_id);
void test_cFMS_diag_init();
void test_cFMS_diag_axis_init_cfloat(int *domain_id);
void test_cFMS_register_diag_field_scalar_int();

int main() 
{

  int domain_id = 0;
  
  cFMS_init(NULL, NULL, NULL, NULL);  
  set_domain(&domain_id);
  
  test_cFMS_diag_init();
  test_cFMS_diag_axis_init_cfloat(&domain_id);
  test_cFMS_register_diag_field_scalar_int();

  return EXIT_SUCCESS;

}

void set_domain(int *domain_id)
{

  cDomainStruct cdomain;
  int global_indices[4] = {0, 96, 0, 96};
  int layout[2] = {2,2};

  cFMS_null_cdomain(&cdomain);  
  cdomain.domain_id = domain_id;
  cdomain.global_indices = global_indices;
  cdomain.layout = layout;

  cFMS_define_domains_easy(cdomain);
  
}

void test_cFMS_diag_init()
{
  int  diag_model_subset = DIAG_ALL;
  int  time_init[6] = {2025, 1, 27, 14, 10, 0};
  int  calendar_type = NOLEAP;
  char err_msg[NAME_LENGTH] = "None";

  cFMS_diag_init(&diag_model_subset, time_init, &calendar_type, err_msg);
  
}

void test_cFMS_diag_axis_init_cfloat(int *domain_id)
{

  cFMS_set_current_domain(domain_id);

  // x-axis
  {
    char   name[NAME_LENGTH] = "lon";
    int    naxis_data = 193;
    float *axis_data;
    char   units[NAME_LENGTH] = "degrees_E";
    char   cart_name[NAME_LENGTH] = "x";
    char   long_name[NAME_LENGTH] = "longitude edges";
    char  *set_name = NULL;
    int   *direction = NULL;
    int   *edges = NULL;
    char   aux[NAME_LENGTH] = "none";
    char   req[NAME_LENGTH] = "none";
    int    tile_count = 0;
    int   *domain_position=NULL;
    
    axis_data = (float *)malloc(naxis_data*sizeof(float));
    for(int i=0 ; i<naxis_data; i++) axis_data[i] = 6.28/naxis_data * i;    
    
    int axis_id = cFMS_diag_axis_init_cfloat(name, &naxis_data, axis_data, units, cart_name, long_name, set_name, 
                                             direction, edges, aux, req, &tile_count, domain_position);
  }

    // y-axis
  {
    char   name[NAME_LENGTH] = "lat";
    int    naxis_data = 193;
    float *axis_data;
    char   units[NAME_LENGTH] = "degrees_N";
    char   cart_name[NAME_LENGTH] = "y";
    char   long_name[NAME_LENGTH] = "latitude_edges";
    char  *set_name = NULL;
    int   *direction = NULL;
    int   *edges = NULL;
    char   aux[NAME_LENGTH] = "none";
    char   req[NAME_LENGTH] = "none";
    int    tile_count = 0;
    int   *domain_position=NULL;
    
    axis_data = (float *)malloc(naxis_data*sizeof(float));
    for(int i=0 ; i<naxis_data; i++) axis_data[i] = -3.14 + 6.28/naxis_data * i;    
    
    int axis_id = cFMS_diag_axis_init_cfloat(name, &naxis_data, axis_data, units, cart_name, long_name,
                                             set_name, direction, edges, aux, req, &tile_count, domain_position);
  }
  
}

void test_cFMS_register_diag_field_scalar_int()
{
  char    module_name[NAME_LENGTH] = "atm_mod";
  char    field_name[NAME_LENGTH] = "var1";
  char    long_name[NAME_LENGTH] = "var1 long name";
  char    units[NAME_LENGTH] = "var1 units";
  char    standard_name[NAME_LENGTH] = "var1 standard name";
  int     missing_value = -99;
  int     range[2] = {-10,10};
  bool   *do_not_log = NULL;
  char    err_msg[NAME_LENGTH] = "NONE";
  int     area = 1;
  int     volume = 1;
  char   *realm = NULL;
  bool   *multiple_send_data = NULL;
  
  int seconds = 40;
  int days    = 14;
  int ticks   = 2;

  cFMS_diag_set_field_init_time(&seconds, &days, &ticks);  

  int field_id = cFMS_register_diag_field_scalar_int(module_name, field_name, long_name, units, &missing_value,
                                                     range, standard_name, do_not_log, err_msg, &area,
                                                     &volume, realm, multiple_send_data);

}



  
  

