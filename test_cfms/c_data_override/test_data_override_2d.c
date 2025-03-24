#include <stdio.h>
#include <stdlib.h>
#include <c_fms.h>
#include <c_data_override.h>
#include <c_mpp_domains_helper.h>

#define NX 360
#define NY 180

#define TEST_NTIMES 11

int main()
{

  int ndomain = 1;
  int nnest_domain = 0;
  int domain_id = 0;
  int ehalo = 2;
  int whalo = 2;
  int shalo = 2;
  int nhalo = 2;  
  int calendar_type = NOLEAP;
  int is, ie, js, je, xsize, ysize;

  cFMS_init(NULL, NULL, &ndomain, &nnest_domain, &calendar_type);

  // define domain
  {
    int global_indices[4] = {0, NX-1, 0, NY-1};  
    
    cDomainStruct domain;
    cFMS_null_cdomain(&domain);

    domain.layout = (int *)malloc(2*sizeof(int));    
    domain.layout[0] = 2;
    domain.layout[1] = 3;
    
    domain.domain_id = &domain_id;
    domain.global_indices = global_indices;
    domain.ehalo = &ehalo;
    domain.whalo = &whalo;
    domain.shalo = &shalo;
    domain.nhalo = &nhalo;

    cFMS_define_domains_easy(domain);
  }

  //get_data_domain
  {
    int *xmax_size = NULL;
    int *ymax_size = NULL;
    bool *x_is_global = NULL;
    bool *y_is_global = NULL;
    int *tile_count = NULL;
    int *position = NULL;

    cFMS_get_compute_domain(&domain_id, &is, &ie, &js, &je, &xsize, xmax_size, &ysize, ymax_size,
                            x_is_global, y_is_global, tile_count, position, NULL, NULL);
  }

  //answers for each pe
  {
    int ij = 0;
    float *answers; //answers for time = 4  
    answers = (float *)malloc(xsize*ysize*sizeof(float));
    for(int i=is+1; i<ie+1; i++) {
      for(int j=js+1; j<je+1; j++) {
        answers[ij++] = (float)(362-i)*1000 + (float)180*j + (float)400;
      }
    }
  }
  
  //data override init
  {
    int *atm_domain_id = NULL;
    int *ice_domain_id = NULL;
    int *land_domain_id = NULL;
    int *land_domainUG_id = NULL;
    cFMS_data_override_init(atm_domain_id, &domain_id, ice_domain_id, land_domain_id, land_domainUG_id, NULL);
  }

  // data override 2d
  {
    char gridname[NAME_LENGTH] = "OCN";
    char fieldname[NAME_LENGTH] = "runoff_increasing";
    int data_shape[2];
    float *data = NULL;
    bool override = false;

    int year = 1;
    int month = 1;
    int day = 4;
    int hour = 0;
    int minute = 0;
    int second = 0;

    data_shape[0] = xsize;
    data_shape[1] = ysize;
    data = (float *)malloc(xsize*ysize*sizeof(float));
    
    cFMS_data_override_set_time(&year, &month, &day, &hour, &minute, &second, NULL, NULL);
    cFMS_data_override_2d_cfloat(gridname, fieldname, data_shape, data, &override, NULL, NULL, NULL, NULL);

    for(int ij=0; ij<10; ij++) {
      printf("pe=%d, ij=%d, data=%f\n", cFMS_pe(), ij, data[ij]);
    }
    
  }
  
  return EXIT_SUCCESS;
}
