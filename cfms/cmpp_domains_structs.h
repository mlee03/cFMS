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
#ifndef CMPP_DOMAINS_STRUCT_H
#define CMPP_DOMAINS_STRUCT_H

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
} cDomainStruct;

cDomainStruct cDomainStruct_init = {
  .domain_id = NULL,
  .pelist = NULL,
  .xflags = NULL,
  .yflags = NULL,
  .xhalo = NULL,
  .yhalo = NULL,
  .xextent = NULL,
  .yextent = NULL,
  .maskmap = NULL,
  .name = NULL,
  .symmetry = NULL,
  .memory_size = NULL,
  .whalo = NULL,
  .ehalo = NULL,
  .shalo = NULL,
  .nhalo = NULL,
  .is_mosaic = NULL,
  .tile_count = NULL,
  .tile_id = NULL,
  .complete = NULL,
  .x_cyclic_offset = NULL,
  .y_cyclic_offset = NULL
}; 

typedef struct {
  int *num_nest;
  int *ntiles;
  int *nest_level;
  int *tile_fine;
  int *tile_coarse;
  int *istart_coarse;
  int *icount_coarse;
  int *jstart_coarse;
  int *jcount_coarse;
  int *npes_nest_tile;
  int *x_refine;
  int *y_refine;
  int *nest_domain_id;
  int *domain_id;
  int *extra_halo;
  char *name;
} cNestDomainStruct;

cNestDomainStruct cNestDomain_init = {
  .num_nest = NULL,
  .ntiles = NULL,
  .nest_level = NULL,
  .tile_fine = NULL,
  .tile_coarse = NULL,
  .istart_coarse = NULL,
  .icount_coarse = NULL,
  .jstart_coarse = NULL,
  .jcount_coarse = NULL,
  .npes_nest_tile = NULL,
  .x_refine = NULL,
  .y_refine = NULL,
  .nest_domain_id = NULL,
  .domain_id = NULL,
  .extra_halo = NULL,
  .name = NULL,
};
                                        
#endif
