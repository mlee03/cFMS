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

extern void cfms_init(int *localcomm, char *alt_input_nml_path_ptr, int *ndomain);

extern void cfms_end();

extern void cfms_get_domain_name(int *domain_id, char *domain_name_c);

extern void cfms_set_npes(int *npes_in);

extern void cfms_define_domains2D(int *global_indices, int *layout, int *domain_id, int *pelist, 
                                  int *xflags, int *yflags, int *xhalo, int *yhalo, int **xextent, int **yextent,
                                  bool **maskmap, char *name_c, bool *symmetry, int *memory_size,
                                  int *whalo, int *ehalo, int *shalo, int *nhalo, bool *is_mosaic,
                                  int *tile_count, int *tile_id, bool *complete, int *x_cyclic_offset, int *y_cyclic_offset);

extern void cfms_define_io_domain2D(int *io_layout, int *domain_id);

extern void cfms_set_compute_domain2D(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                      int *xsize, int *ysize, bool *x_is_global, bool *y_is_global, int *tile_count);

extern void cfms_set_data_domain2D(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                   int *xsize, int *ysize, bool *x_is_global, bool *y_is_global, int *tile_count);

extern void cfms_set_global_domain2D(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                     int *xsize, int *ysize, int *tile_count);

extern void cfms_define_nest_domain(int *num_nest, int *nest_level, int *tile_fine, int *tile_course,
                                    int *istart_coarse, int *icount_coarse, int *jstart_coarse, int *jcount_coarse,
                                    int *npes_nest_tile, int *x_refine, int *y_refine, int *domain_id,
                                    int *extra_halo, char *name_ptr);


                                     

                                  
                                   


#endif

                   
