#include <stdlib.h>
#include <stdio.h>
#include <cfms.h>
#include "test_cfms.h"

//this test is a direct translation of test_mpp_nesting


#define NDOMAIN 4
#define NNEST 3
#define NTILES_NEST_TOP 1

int nx, ny, npes;
int stackmax=10000000;
int whalo, ehalo, shalo, nhalo;
int ndomain, nnest, ntop;
int *refine_ratio;
int *istart_coarse, *jstart_coarse, *iend_coarse, *jend_coarse;
int *istart_fine, *jstart_fine, *iend_fine, *jend_fine;
int *icount_coarse, *jcount_coarse;
int *top_npes, *nest_npes;
int *top_tile_id, *nest_tile_id;


void test_cFMS_define_domains();
void set_parameters();


int main()
{

  cFMS_init(NULL,NULL,NULL);
  set_parameters();
  
  test_cFMS_define_domains();


  return 0;
  
}


void test_cFMS_define_domains()
{

  //world, global pelist
  int* global_pelist ; global_pelist = (int *)malloc(npes*sizeof(int));
  
  cFMS_set_npes(&npes);
  cFMS_get_current_pelist(global_pelist, NULL, NULL);

  // define domain for all top level
  for( int itop=0 ; itop<ntop; itop++ ) {
    
    //pelist
    int *top_pelist, start=0;
    top_pelist = (int *)malloc(top_npes[itop]*sizeof(int));
    for(int i=0 ; i<=itop-1; i++) start += top_npes[i];
    for(int i=0 ; i<top_npes[itop]; i++) top_pelist[i] = global_pelist[start+i];

    cFMS_set_npes(top_npes+itop);
    cFMS_declare_pelist(top_pelist, NULL, NULL);
    
    //top level define_domain
    if( any(top_npes[itop], top_pelist, cFMS_pe()) ) {
      
      DefineDomainStruct cdomain = DefineDomainStruct_default;
      bool symmetry = true;
      char name[] = "Cubic-Grid top level grid";
      int  global_indices[] = {1, nx, 1, ny};
    
      cFMS_set_npes(top_npes+itop);      
      cFMS_set_current_pelist(top_pelist, NULL);
    
      cdomain.layout = (int *)malloc(2*sizeof(int));  
      cFMS_define_layout(global_indices, top_npes, cdomain.layout);

      cdomain.global_indices = global_indices;
      cdomain.name    = name;
      cdomain.pelist  = top_pelist;
      cdomain.whalo = &whalo;
      cdomain.ehalo = &ehalo;
      cdomain.shalo = &shalo;
      cdomain.nhalo = &nhalo;
      cdomain.symmetry = &symmetry;
      cdomain.tile_id  = top_tile_id+itop;
      
      cFMS_define_domains_wrap(cdomain);
    
    } // if pe in top_pelist
    free(top_pelist);
  } // for each itop

  cFMS_set_current_pelist(NULL, NULL); //set to global pelist

  int start_top=0;
  for(int i=0 ; i<ntop ; i++) start_top += top_npes[i];
  
  // define domain for all nest region
  for(int inest=0 ; inest<nnest; inest++){

    // declare nest pelist
    int *nest_pelist, start=start_top;
    nest_pelist = (int *)malloc(nest_npes[inest]*sizeof(int));    
    for(int i=0; i<=inest-1; i++) start += nest_npes[i]; 
    for(int i=0; i<nest_npes[inest]; i++) nest_pelist[i] = global_pelist[start+i];
    cFMS_set_npes(nest_npes+inest);
    cFMS_declare_pelist(nest_pelist, NULL, NULL);

    if( any(nest_npes[inest], nest_pelist, cFMS_pe()) ){

      DefineDomainStruct cdomain = DefineDomainStruct_default;

      bool symmetry = true;
      char name[] = "Cubic-Grid fine grid";      
      int nx_fine = iend_fine[inest] - istart_fine[inest] + 1;
      int ny_fine = jend_fine[inest] - jstart_fine[inest] + 1;
      int nest_indices[] = {1, nx_fine, 1, ny_fine};

      cFMS_set_npes(nest_npes+inest);
      cFMS_set_current_pelist(nest_pelist, NULL);

      cdomain.layout = (int *)malloc(2*sizeof(2));
      cFMS_define_layout(nest_indices, nest_npes+inest, cdomain.layout);
      
      cdomain.global_indices = nest_indices;
      cdomain.name    = name;
      cdomain.pelist  = nest_pelist;
      cdomain.whalo = &whalo;
      cdomain.ehalo = &ehalo;
      cdomain.shalo = &shalo;
      cdomain.nhalo = &nhalo;
      cdomain.symmetry = &symmetry;
      cdomain.tile_id  = nest_tile_id+inest;

      cFMS_set_npes(nest_npes+inest);
      cFMS_set_current_pelist(nest_pelist, NULL);
      cFMS_define_domains_wrap(cdomain);
    }
    free(nest_pelist);
    cFMS_set_current_pelist(NULL, NULL);    
  }
    
}


void test_nest_halo_update()
{

  

}
  
void set_parameters()
{  

  nx = 20;
  ny = 20;
  stackmax = 10000000;
  whalo = 2;
  ehalo = 2;
  shalo = 2;
  nhalo = 2;
  ndomain = 1;
  nnest = 3;
  ntop=1;

  npes = cFMS_npes();
  
  top_npes = (int *)malloc(nnest * sizeof(int));
  top_npes[0] = 2;
  
  nest_npes = (int *)malloc(nnest * sizeof(int));
  for(int inest=0 ; inest<nnest; inest++) nest_npes[inest] = 2;
  nest_npes[nnest-1] = 1;

  top_tile_id = (int *)malloc(ntop * sizeof(int));
  top_tile_id[0] = 1;
  
  nest_tile_id = (int *)malloc(nnest * sizeof(int));
  nest_tile_id[0] = 2; nest_tile_id[1] = 3; nest_tile_id[2] = 4;
  
  refine_ratio = (int *)malloc(nnest*sizeof(int));  
  for(int inest=0; inest<nnest; inest++) refine_ratio[inest] = 2;  
  
  istart_fine = (int *)malloc(nnest*sizeof(int));
  iend_fine   = (int *)malloc(nnest*sizeof(int));
  jstart_fine = (int *)malloc(nnest*sizeof(int));
  jend_fine   = (int *)malloc(nnest*sizeof(int));
  istart_coarse = (int *)malloc(nnest*sizeof(int));
  iend_coarse   = (int *)malloc(nnest*sizeof(int));
  jstart_coarse = (int *)malloc(nnest*sizeof(int));
  jend_coarse   = (int *)malloc(nnest*sizeof(int));
  icount_coarse = (int *)malloc(nnest*sizeof(int));
  jcount_coarse = (int *)malloc(nnest*sizeof(int));

  istart_coarse[0] = 4;  istart_coarse[1] = 3; istart_coarse[2] = 5;
  icount_coarse[0] = 12; icount_coarse[1] = 5; icount_coarse[2] = 6;
  jstart_coarse[0] = 4;  jstart_coarse[1] = 3; jstart_coarse[2] = 6;
  jcount_coarse[0] = 12; jcount_coarse[1] = 6; jcount_coarse[2] = 8;
  
  for(int inest=0 ; inest<nnest; inest++) {
    iend_coarse[inest] = istart_coarse[inest] + icount_coarse[inest] - 1;
    jend_coarse[inest] = jstart_coarse[inest] + jcount_coarse[inest] - 1;
    istart_fine[inest] = 1; iend_fine[inest] = icount_coarse[inest]*refine_ratio[inest];
    jstart_fine[inest] = 1; jend_fine[inest] = jcount_coarse[inest]*refine_ratio[inest];
  }
  
}

