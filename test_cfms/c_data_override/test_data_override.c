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

  cFMS_init(NULL, NULL, &ndomain, &nnest_domain);

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
    int mode = CDOUBLE_MODE; //for r8
    cFMS_data_override_init(&domain_id, ocn_domain_id, ice_domain_id, land_domain_id, land_domainUG_id, &mode);
  }
    
  return EXIT_SUCCESS;
}
