#include <stdlib.h>
#include <stdio.h>
#include <cfms.h>
#include "test_cfms.h"

//this test is a direct translation of test_mpp_nesting


#define NDOMAIN 4
#define NNEST 3
#define NTILES_NEST_TOP 1

int nx=20;
int ny=20;
int stackmax=10000000;
int whalo = 2;
int ehalo = 2;
int shalo = 2;
int nhalo = 2;
int ndomain = NDOMAIN;
int nnest = NNEST;
int refine_ratio[NNEST];
int istart_coarse[NNEST], jstart_coarse[NNEST], iend_coarse[NNEST], jend_coarse[NNEST];
int istart_fine[NNEST], jstart_fine[NNEST], iend_fine[NNEST], jend_fine[NNEST];
int icount_coarse[NNEST], jcount_coarse[NNEST];
int nx_fine[NNEST], ny_fine[NNEST];
int top_npes[NTILES_NEST_TOP];
int nest_npes[NNEST];
int tile_id[NNEST] = {2,3,4};


void test_cFMS_define_domains();
void set_nest_variables();


int main()
{

  cFMS_init(NULL,NULL,&ndomain);
  set_nest_variables();
  test_cFMS_define_domains();
  return 0;
  
}


void test_cFMS_define_domains()
{

  int domain_id = 0;
  
  //world, global pelist
  int npes = cFMS_npes();
  int* global_pelist ; global_pelist = (int *)malloc(npes*sizeof(int));

  cFMS_set_npes(&npes);
  cFMS_get_current_pelist(global_pelist, NULL, NULL);

  int isc_fine, iec_fine, jsc_fine, jec_fine;
  int isd_fine, ied_fine, jsd_fine, jed_fine;

  //top level pelist
  int *top_pelist ; top_pelist = (int *)malloc(top_npes[0]*sizeof(int));
  for(int i=0 ; i<top_npes[0]; i++) top_pelist[i] = global_pelist[i];
  cFMS_set_npes(top_npes);  
  cFMS_declare_pelist(top_pelist, NULL, NULL);

  //top level define_domain
  if( any(top_npes[0], top_pelist, cFMS_pe()) ) {

    DefineDomainStruct cdomain = DefineDomainStruct_default;
    bool symmetry = true;
    int tile_id   = 1;
    int global_indices[] = {1, nx, 1, ny};
    char name[] = "Cubic-Grid top level grid";
    
    cFMS_set_npes(top_npes);
    cFMS_set_current_pelist(top_pelist, NULL);
    
    cdomain.layout = (int *)malloc(2*sizeof(int));  
    cFMS_define_layout(global_indices, top_npes, cdomain.layout);

    cdomain.global_indices = global_indices;
    cdomain.name    = name;
    cdomain.pelist  = top_pelist;
    cdomain.domain_id = &domain_id;
    cdomain.whalo = &whalo;
    cdomain.ehalo = &ehalo;
    cdomain.shalo = &shalo;
    cdomain.nhalo = &nhalo;
    cdomain.symmetry = &symmetry;
    cdomain.tile_id  = &tile_id;

    cFMS_define_domains_wrap(cdomain);
    
    // get indices
    int *xsize=NULL, *xmax_size=NULL, *ysize=NULL, *ymax_size=NULL, *tile_count=NULL, *position=NULL;
    bool *x_is_global=NULL, *y_is_global=NULL;    
    cFMS_get_compute_domain(&domain_id, &isc_fine, &iec_fine, &jsc_fine, &jec_fine,
                            xsize, xmax_size, ysize, ymax_size, x_is_global, y_is_global, tile_count, position);
    cFMS_get_data_domain(&domain_id, &isd_fine, &ied_fine, &jsd_fine, &jed_fine,
                         xsize, xmax_size, ysize, ymax_size, x_is_global, y_is_global, tile_count, position);
    
  } // top level define_domain for pe in top_pelist

  cFMS_set_current_pelist(NULL, NULL); //set to global pelist

  
  for(int inest=0 ; inest<nnest; inest++){

    int *nest_pelist; nest_pelist = (int *)malloc(nest_npes[inest]*sizeof(int));
    int start=top_npes[0];
    for(int i=1; i<=inest; i++) start += nest_npes[i-1]; 
    for(int i=0 ; i<nest_npes[inest]; i++) nest_pelist[i] = global_pelist[start+i];
    cFMS_set_npes(nest_npes+inest);
    cFMS_declare_pelist(nest_pelist, NULL, NULL);
    
    if( any(nest_npes[inest], nest_pelist, cFMS_pe()) ){

      DefineDomainStruct cdomain = DefineDomainStruct_default;
      int nest_indices[] = {1, nx_fine[inest], 1, ny_fine[inest]};
      bool symmetry = true;
      char name[] = "Cubic-Grid fine grid";
      
      cdomain.layout = (int *)malloc(2*sizeof(2));
      cFMS_define_layout(nest_indices, nest_npes+inest, cdomain.layout);

      cdomain.global_indices = nest_indices;
      cdomain.name    = name;
      cdomain.pelist  = nest_pelist;
      cdomain.domain_id = &domain_id;
      cdomain.whalo = &whalo;
      cdomain.ehalo = &ehalo;
      cdomain.shalo = &shalo;
      cdomain.nhalo = &nhalo;
      cdomain.symmetry = &symmetry;
      cdomain.tile_id  = tile_id+inest;

      cFMS_set_npes(nest_npes+inest);
      cFMS_set_current_pelist(nest_pelist, NULL);
      cFMS_define_domains_wrap(cdomain);
    }
    free(nest_pelist);
    cFMS_set_current_pelist(NULL, NULL);
  }
    
}

void set_nest_variables()
{  

  //initialize
  for(int inest=0 ; inest<nnest; inest++) {
    istart_fine[inest] = 0;
    iend_fine[inest]   = -1;
    jstart_fine[inest] = 0;
    jend_fine[inest]   = -1;
    iend_coarse[inest] = -1;
    jend_coarse[inest] = -1;
  }

  for(int inest=0; inest<nnest; inest++){
    refine_ratio[inest] = 2;
    nest_npes[inest] = 2;
  }
  nest_npes[nnest-1] = 1;
  
  istart_coarse[0] = 4;  istart_coarse[1] = 3; istart_coarse[2] = 5;
  icount_coarse[0] = 12; icount_coarse[1] = 5; icount_coarse[2] = 6;
  jstart_coarse[0] = 4;  jstart_coarse[1] = 3; jstart_coarse[2] = 6;
  jcount_coarse[0] = 12; jcount_coarse[1] = 6; jcount_coarse[2] = 8;
  
  for(int inest=0 ; inest<nnest; inest++) {
    iend_coarse[inest] = istart_coarse[inest] + icount_coarse[inest] - 1;
    jend_coarse[inest] = jstart_coarse[inest] + jcount_coarse[inest] - 1;
    istart_fine[inest] = 1;
    jstart_fine[inest] = 1;
    iend_fine[inest] = icount_coarse[inest]*refine_ratio[inest];
    jend_fine[inest] = jcount_coarse[inest]*refine_ratio[inest];
    nx_fine[inest] = iend_fine[inest] - istart_fine[inest] + 1;
    ny_fine[inest] = jend_fine[inest] - jstart_fine[inest] + 1;
  }

  top_npes[0] = 2;
  
}

