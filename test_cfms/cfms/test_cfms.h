#ifndef TEST_CFMS_H_
#define TEST_CMFS_H_

#define TRUE 1
#define FALSE 0

typedef struct {
  int* global_indices;
  int* layout;
  int* domain_id;
  int* pelist;
  int* xflags;
  int* yflags;
  int* xhalo;
  int* yhalo;
  int* xextent;
  int* yextent;
  bool** maskmap;
  char* name;
  bool* symmetry;
  int *memory_size; //memory_size[2]
  int* whalo;
  int* ehalo;
  int* shalo;
  int* nhalo;
  bool* is_mosaic;
  int* tile_count;
  int* tile_id;
  bool* complete;
  int* x_cyclic_offset;
  int* y_cyclic_offset;
} DefineDomainStruct;

DefineDomainStruct DefineDomainStruct_default = {
  .domain_id=NULL,
  .pelist=NULL,
  .xflags=NULL,
  .yflags=NULL,
  .xhalo=NULL,
  .yhalo=NULL,
  .xextent=NULL,
  .yextent=NULL,
  .maskmap=NULL,
  .name=NULL,
  .symmetry=NULL,
  .memory_size=NULL,
  .whalo=NULL,
  .ehalo=NULL,
  .shalo=NULL,
  .nhalo=NULL,
  .is_mosaic=NULL,
  .tile_count=NULL,
  .tile_id=NULL,
  .complete=NULL,
  .x_cyclic_offset=NULL,
  .y_cyclic_offset=NULL
}; 


void cFMS_define_domains_wrap(DefineDomainStruct ddstruct)
{
  cFMS_define_domains(ddstruct.global_indices,
                      ddstruct.layout,
                      ddstruct.domain_id,
                      ddstruct.pelist,
                      ddstruct.xflags, ddstruct.yflags,
                      ddstruct.xhalo, ddstruct.yhalo,
                      ddstruct.xextent, ddstruct.yextent,
                      ddstruct.maskmap,
                      ddstruct.name,
                      ddstruct.symmetry,
                      ddstruct.memory_size,
                      ddstruct.whalo, ddstruct.ehalo, ddstruct.shalo, ddstruct.nhalo,
                      ddstruct.is_mosaic,
                      ddstruct.tile_count, ddstruct.tile_id,
                      ddstruct.complete,
                      ddstruct.x_cyclic_offset, ddstruct.y_cyclic_offset);
}
    
int any(int n, int* array, int value)
{
  for(int i=0 ; i<n ; i++){
    if(value == array[i]) return TRUE;
  }
  return FALSE;
}
                            

#endif
