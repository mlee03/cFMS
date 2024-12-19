11;rgb:fcfc/e8e8/e8e8/************************************************************************
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
#include <cmpp_domains_structs.h>

extern void cFMS_define_domains(int global_indices[4], int layout[2], int *domain_id, int pelist[], 
                                int *xflags, int *yflags, int *xhalo, int *yhalo, int xextent[], int yextent[],
                                bool **maskmap, char *name, bool *symmetry, int memory_size[2],
                                int *whalo, int *ehalo, int *shalo, int *nhalo, bool *is_mosaic,
                                int *tile_count, int *tile_id, bool *complete, int *x_cyclic_offset, int *y_cyclic_offset);

extern void cFMS_define_io_domain(int io_layout[2], int *domain_id);

extern void cFMS_define_layout(int global_indices[4], int *ndivs, int layout[2]);

extern void cFMS_define_nest_domains(int *num_nest, int *ntiles, int nest_level[], int tile_fine[], int tile_course[],
                                     int istart_coarse[], int icount_coarse[], int jstart_coarse[], int jcount_coarse[],
                                     int npes_nest_tile[], int x_refine[], int y_refine[], int *nest_domain_id,
                                     int* domain_id, int *extra_halo, char *name);

extern bool cFMS_domain_is_initialized(int *domain_id);

extern void cFMS_define_domains_easy(cDomainStruct cdomain);

extern void cFMS_define_nest_domains_easy(cNestDomainStruct cnestdomain);

extern void cFMS_set_compute_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                    int *xsize, int *ysize, bool *x_is_global, bool *y_is_global, int *tile_count);

extern void cFMS_set_data_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                 int *xsize, int *ysize, bool *x_is_global, bool *y_is_global, int *tile_count);

extern void cFMS_set_global_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                   int *xsize, int *ysize, int *tile_count);

void cFMS_define_domains_easy(cDomainStruct cdomain)
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

void cFMS_define_nest_domains_easy(cNestDomainStruct cnestdomain)
{

  cFMS_define_nest_domains(cnestdomain.num_nest,
                           cnestdomain.ntiles,
                           cnestdomain.nest_level,
                           cnestdomain.tile_fine,
                           cnestdomain.tile_coarse,
                           cnestdomain.istart_coarse,
                           cnestdomain.icount_coarse,
                           cnestdomain.jstart_coarse,
                           cnestdomain.jcount_coarse,
                           cnestdomain.npes_nest_tile,
                           cnestdomain.x_refine,
                           cnestdomain.y_refine,
                           cnestdomain.nest_domain_id,
                           cnestdomain.domain_id,
                           cnestdomain.extra_halo,
                           cnestdomain.name);
}

#endif

                   
      
