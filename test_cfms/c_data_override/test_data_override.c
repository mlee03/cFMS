#include <stdio.h>
#include <stdlib.h>
#include <c_fms.h>
#include <c_data_override.h>
#include <c_mpp_domains_helper.h>

#define NX 384
#define NY 384

int main()
{

  int ndomain = 1;
  int nnest_domain = 0;
  int domain_id = 0;
  int calendar_type = NOLEAP;
  
  cFMS_init(NULL, NULL, &ndomain, &nnest_domain, &calendar_type);

  // define domain
  {
    int global_indices[4] = {0, NX-1, 0, NY-1};  
    int ehalo = 2;
    int whalo = 2;
    int shalo = 2;
    int nhalo = 2;
    
    cDomainStruct domain;
    cFMS_null_cdomain(&domain);

    int ndivs = cFMS_npes();
    domain.layout = (int *)malloc(2*sizeof(int));    
    cFMS_define_layout(global_indices, &ndivs, domain.layout);
    
    domain.domain_id = &domain_id;
    domain.global_indices = global_indices;
    domain.ehalo = &ehalo;
    domain.whalo = &whalo;
    domain.shalo = &shalo;
    domain.nhalo = &nhalo;
    
    cFMS_define_domains_easy(domain);
  }

  //data override init
  {
    int *ocn_domain_id = NULL;
    int *ice_domain_id = NULL;
    int *land_domain_id = NULL;
    int *land_domainUG_id = NULL;
    cFMS_data_override_init(&domain_id, ocn_domain_id, ice_domain_id, land_domain_id, land_domainUG_id, NULL);
  }

  //data override scalar
  {
    char gridname[NAME_LENGTH] = "ATM";
    char fieldname_code[NAME_LENGTH] = "co2";
    float data = -100.;
    bool *override = NULL;
    int *data_index = NULL;

    int year = 1;
    int month = 1;
    int day = 2;
    int hour = 0;
    int minute = 0;
    int second = 0;

    cFMS_data_override_set_time(&year, &month, &day, &hour, &minute, &second, NULL, NULL);

    cFMS_data_override_0d_cfloat(gridname, fieldname_code, &data, 
  }
  
  return EXIT_SUCCESS;
}
