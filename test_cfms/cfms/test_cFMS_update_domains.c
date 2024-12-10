#include <stdio.h>
#include <stdlib.h>
#include <cfms.h>

#define NX 64
#define NY 64

#define E6 1000000
#define E3 1000

int test_cFMS_update_domains_i32();

int main()
{

  cFMS_init(NULL,NULL,NULL);
  test_cFMS_update_domains_i32();
  
  return 0;
  
}

int test_cFMS_update_domains_i32()
{

  int nhalo=2, shalo=2, whalo=2, ehalo=2;
  bool symmetry = true;
  int global_indices[4] = {1,NX,1,NY};   
  DefineDomainStruct cdomain = DefineDomainStructDefault;

  int npes = cFMS_npes();
  cdomain.global_indices = global_indices;
  cdomain.whalo = &whalo;
  cdomain.ehalo = &ehalo;
  cdomain.shalo = &shalo;
  cdomain.nhalo = &nhalo;
  cdomain.layout = (int *)malloc(2*sizeof(int));
  cFMS_define_layout(cdomain.global_indices, &npes, cdomain.layout);
  cFMS_define_domains_wrap(cdomain);
  
  int idata_global[NY+ehalo+whalo][NX+nhalo+shalo];
  int field_shape[2], **idata;
  int isc, iec, jsc, jec, isd, ied, jsd, jed;
  int *xsize=NULL, *xmax_size=NULL, *ysize=NULL, *ymax_size=NULL, *tile_count=NULL, *position=NULL, *flags=NULL;
  bool *x_is_global=NULL, *y_is_global=NULL, *complete=NULL;
  char *name=NULL;

  for( int j=shalo; j<NY; j++) {
    for( int i=whalo; i<NX; i++) {
      idata_global[j][i] = i*E3 + j;
    }
  }
  
  cFMS_get_compute_domain(cdomain.domain_id, &isc, &iec, &jsc, &jec, xsize, xmax_size,
                          ysize, ymax_size, x_is_global, y_is_global, tile_count, position, &whalo, &shalo);
  cFMS_get_data_domain(cdomain.domain_id, &isd, &ied, &jsd, &jed, xsize, xmax_size,
                       ysize, ymax_size, x_is_global, y_is_global, tile_count, position, &whalo, &shalo);
  
  field_shape[0] = (iec-isc);
  field_shape[1] = (jec-jsc);  
  idata = (int **)malloc(field_shape[1]*sizeof(int));
  for(int j=0; j<NY; j++) {
    idata[j] = (int *)malloc(field_shape[0]*sizeof(int));
  }

  for(int j=jsd; j<jed; j++) {
    for(int i=isd; i<ied; i++) {
      idata[j][i] = idata_global[j][i];
    }
  }
  
  cFMS_update_domains_cint_2d(field_shape, idata, cdomain.domain_id, flags, complete, position,
                              &whalo, &ehalo, &shalo, &nhalo, name, tile_count);
  

  
      

  
}
