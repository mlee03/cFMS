/************************************************************************
!*                   GNU Lesser General Public License
!*
!* This file is part of the GFDL Flexible Modeling System (FMS).
!*
!* FMS is free software: you can redistribute it and/or modify it under
!* the terms of the GNU Lesser General Public License as published by
!* the Free Software Foundation, either version 3 of the License, or (at
!* your option) any later version.
!*
!* FMS is distributed in the hope that it will be useful, but WITHOUT
!* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
!* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
!* for more details.
!*
!* You should have received a copy of the GNU Lesser General Public
!* License along with FMS.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************/
#ifndef CMPP_DOMAINS_H
#define CMPP_DOMAINS_H

#include <stdbool.h>

enum DatatypeEnum{ inttype=1, floattype=3, doubletype=4 };
enum DatatypeEnum Datatype;

//DefineDomainStruct is not defined as an interoperable Fortran derived type
//to avoid dynamic allocation of arrays using iso_Fortran_bindings and complicating
//usage for users.
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

DefineDomainStruct DefineDomainStructDefault = {
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

extern void cFMS_define_domains(int global_indices[4], int layout[2], int *domain_id, int pelist[], 
                                int *xflags, int *yflags, int *xhalo, int *yhalo, int xextent[], int yextent[],
                                bool **maskmap, char *name_c, bool *symmetry, int memory_size[2],
                                int *whalo, int *ehalo, int *shalo, int *nhalo, bool *is_mosaic,
                                int *tile_count, int *tile_id, bool *complete, int *x_cyclic_offset, int *y_cyclic_offset);

extern void cFMS_define_io_domain(int io_layout[2], int *domain_id);

extern void cFMS_define_layout(int global_indices[4], int *ndivs, int layout[2]);

extern void cFMS_define_nest_domain(int *num_nest, int nest_level[], int tile_fine[], int tile_course[],
                                    int istart_coarse[], int icount_coarse[], int jstart_coarse[], int jcount_coarse[],
                                    int npes_nest_tile[], int x_refine[], int y_refine[], int* domain_id,
                                    int *extra_halo, char *name_ptr);

extern bool cFMS_domain_is_initialized(int *domain_id);

extern void cFMS_get_domain_layout(int layout[2], int *domain_id);

extern void cFMS_get_domain_name(char *domain_name_c, int *domain_id);

extern void cFMS_get_domain_pelist(int pelist[], int *domain_id, int *pos);

extern void cFMS_define_domains_wrap(DefineDomainStruct cdomain);

void cFMS_define_domains_wrap(DefineDomainStruct cdomain)
{
  cFMS_define_domains(cdomain.global_indices,
                      cdomain.layout,
                      cdomain.domain_id,
                      cdomain.pelist,
                      cdomain.xflags, cdomain.yflags,
                      cdomain.xhalo, cdomain.yhalo,
                      cdomain.xextent, cdomain.yextent,
                      cdomain.maskmap,
                      cdomain.name,
                      cdomain.symmetry,
                      cdomain.memory_size,
                      cdomain.whalo, cdomain.ehalo, cdomain.shalo, cdomain.nhalo,
                      cdomain.is_mosaic,
                      cdomain.tile_count, cdomain.tile_id,
                      cdomain.complete,
                      cdomain.x_cyclic_offset, cdomain.y_cyclic_offset);
}

#endif

                   
      
