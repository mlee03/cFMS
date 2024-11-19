#include <stdlib.h>
#include <stdio.h>
#include <cfms.h>
#include "test_cfms.h"

//this test is a direct translation of test_mpp_nesting

int nx=64;
int ny=64;
int stackmax=10000000;
int whalo = 2;
int ehalo = 2;
int shalo = 2;
int nhalo = 2;
int ndomain = 4;

void test_cFMS_define_domains();

int main()
{

  cFMS_init(NULL,NULL,&ndomain);
  test_cFMS_define_domains();
  return 0;
  
}


void test_cFMS_define_domains()
{

  int npes = cFMS_npes();
  int* pelist_global ; pelist_global = (int *)malloc(npes*sizeof(int));

  cFMS_set_npes(&npes);
  cFMS_get_current_pelist(pelist_global, NULL, NULL);

  int npes_top = 1;
  int pelist_top[1];
  for(int i=0 ; i<npes_top; i++) pelist_top[i] = pelist_global[i];
  cFMS_set_npes(&npes_top);  
  cFMS_declare_pelist(pelist_top, NULL, NULL);

  if( any(npes_top, pelist_top, cFMS_pe()) ) {

    DefineDomainStruct cdomain = DefineDomainStruct_default;
    bool symmetry = true;
    int tile_id   = 1;
    int domain_id = 0;
    int global_indices[] = {1, nx, 1, ny};
    char name[] = "Cubic-Grid top level grid";
    
    cFMS_set_npes(&npes_top);
    cFMS_set_current_pelist(pelist_top, NULL);
    
    cdomain.layout = (int *)malloc(2*sizeof(int));  
    cFMS_define_layout(global_indices, &npes_top, cdomain.layout);

    cdomain.global_indices = global_indices;
    cdomain.name    = name;
    cdomain.pelist  = pelist_top;
    cdomain.domain_id = &domain_id;
    cdomain.whalo = &whalo;
    cdomain.ehalo = &ehalo;
    cdomain.shalo = &shalo;
    cdomain.nhalo = &nhalo;
    cdomain.symmetry = &symmetry;
    cdomain.tile_id  = &tile_id;

    cFMS_define_domains_wrap(cdomain);

  } // if pe==1
  
  

}


