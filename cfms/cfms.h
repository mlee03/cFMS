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
#ifndef CFMS_H
#define CFMS_H

#include <stdbool.h>

extern const int NOTE;
extern const int WARNING;
extern const int FATAL;

extern void cFMS_set_npes(int *npes_in);

extern void cFMS_init(int *localcomm, char *alt_input_nml_path_ptr, int *ndomain);

extern void cFMS_end();

extern void cFMS_error(int errortype, char *errormsg_c);

extern int cFMS_pe();
extern int cFMS_npes();

extern void cFMS_declare_pelist(int *pelist, char *name_c, int *commID);

extern void cFMS_set_current_pelist(int *pelist, bool *no_sync);

extern void cFMS_get_current_pelist(int *pelist, char *name_c, int *commID);

extern void cFMS_define_layout(int global_indices[4], int *ndivs, int layout[2]);

extern void cFMS_define_domains(int global_indices[4], int layout[2], int *domain_id, int pelist[], 
                                int *xflags, int *yflags, int *xhalo, int *yhalo, int xextent[], int yextent[],
                                bool **maskmap, char *name_c, bool *symmetry, int memory_size[2],
                                int *whalo, int *ehalo, int *shalo, int *nhalo, bool *is_mosaic,
                                int *tile_count, int *tile_id, bool *complete, int *x_cyclic_offset, int *y_cyclic_offset);

extern void cFMS_define_io_domain(int io_layout[2], int *domain_id);

extern void cFMS_set_compute_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                    int *xsize, int *ysize, bool *x_is_global, bool *y_is_global, int *tile_count);

extern void cFMS_set_data_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                 int *xsize, int *ysize, bool *x_is_global, bool *y_is_global, int *tile_count);

extern void cFMS_set_global_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                   int *xsize, int *ysize, int *tile_count);

extern void cFMS_define_nest_domain(int *num_nest, int nest_level[], int tile_fine[], int tile_course[],
                                    int istart_coarse[], int icount_coarse[], int jstart_coarse[], int jcount_coarse[],
                                    int npes_nest_tile[], int x_refine[], int y_refine[], int* domain_id,
                                    int *extra_halo, char *name_ptr);


extern void cFMS_get_domain_name(char *domain_name_c, int *domain_id);

extern void cFMS_get_domain_pelist(int pelist[], int *domain_id, int *pos);

extern void cFMS_get_domain_layout(int layout[2], int *domain_id);

extern void cFMS_get_compute_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                    int *xsize, int *xmax_size, int *ysize, int *ymax_size,
                                    bool *x_is_global, bool *y_is_global, int *tile_count, int *position);
  
extern void cFMS_get_data_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                 int *xsize, int *xmax_size, int *ysize, int *ymax_size,
                                 bool *x_is_global, bool *y_is_global, int *tile_count, int *position);

extern bool cFMS_domain_is_initialized(int *domain_id);

#endif

                   
