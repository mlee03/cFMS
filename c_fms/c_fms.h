#ifndef CFMS_H
#define CFMS_H

#include <stdbool.h>

#define NAME_LENGTH 64 
#define MESSAGE_LENGTH 128

extern const int NOTE;
extern const int WARNING;
extern const int FATAL;

extern int GLOBAL_DATA_DOMAIN;
extern int BGRID_NE;
extern int CGRID_NE;
extern int DGRID_NE;
extern int AGRID;
extern int FOLD_SOUTH_EDGE;
extern int FOLD_NORTH_EDGE;
extern int FOLD_WEST_EDGE;
extern int FOLD_EAST_EDGE;  
extern int CYCLIC_GLOBAL_DOMAIN;
extern int NUPDATE;
extern int EUPDATE;
extern int XUPDATE;
extern int YUPDATE;
extern int NORTH;
extern int NORTH_EAST;
extern int EAST;
extern int SOUTH_EAST;
extern int CORNER;
extern int CENTER;
extern int SOUTH;
extern int SOUTH_WEST;
extern int WEST;
extern int NORTH_WEST;
extern int CYCLIC_GLOBAL_DOMAIN;

extern void cFMS_init(int *localcomm, char *alt_input_nml_path, int *ndomain, int *nnest_domain);

extern void cFMS_end();

extern void cFMS_set_pelist_npes(int *npes_in);

extern void cFMS_error(int errortype, char *errormsg);

extern void cFMS_declare_pelist(int *pelist, char *name, int *commID);

extern void cFMS_get_current_pelist(int *pelist, char *name, int *commID);

extern int cFMS_npes();

extern int cFMS_pe();

extern void cFMS_set_current_pelist(int *pelist, bool *no_sync);

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

extern void cFMS_get_compute_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                    int *xsize, int *xmax_size, int *ysize, int *ymax_size,
                                    bool *x_is_global, bool *y_is_global, int *tile_count, int *position,
                                    int *whalo, int *shalo);
  
extern void cFMS_get_data_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                 int *xsize, int *xmax_size, int *ysize, int *ymax_size,
                                 bool *x_is_global, bool *y_is_global, int *tile_count, int *position,
                                 int *whalo, int *shalo);

extern void cFMS_get_domain_name(char *domain_name_c, int *domain_id);

extern void cFMS_get_domain_pelist(int pelist[], int *domain_id);

extern void cFMS_get_layout(int layout[2], int *domain_id);

extern void cFMS_set_compute_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                    int *xsize, int *ysize, bool *x_is_global, bool *y_is_global, int *tile_count,
                                    int *whalo, int *shalo);

extern void cFMS_set_data_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                 int *xsize, int *ysize, bool *x_is_global, bool *y_is_global, int *tile_count,
                                 int *whalo, int *shalo);

extern void cFMS_set_global_domain(int *domain_id, int *xbegin, int *xend, int *ybegin, int *yend,
                                   int *xsize, int *ysize, int *tile_count);

extern void cFMS_update_domains_float_2d(int *field_shape, float **field, int *domain_id, int *flags, int *complete,
                                         int *position, int *whalo, int *ehalo, int *shalo, int *nhalo,
                                         char *name, int *tile_count);

#endif
