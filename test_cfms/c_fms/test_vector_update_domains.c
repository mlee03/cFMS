#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#include <c_fms.h>
#include <c_mpp_domains_helper.h>

//Adapted from test_mpp_update_domains_real.F90 - Folded xy_halo

#define NX 8
#define NY 8
#define NZ 2
#define NPES 1
#define WHALO 2
#define EHALO 2
#define NHALO 2
#define SHALO 2

void define_domain(int *domain_id);
void test_vector_double3d(int *domain_id);

int main()
{
  int domain_id = 0;

  cFMS_init(NULL,NULL,NULL,NULL,NULL);

  define_domain(&domain_id);
  cFMS_set_current_pelist(NULL,NULL);

  test_vector_double3d(&domain_id);

  cFMS_end();
  return EXIT_SUCCESS;

}

void define_domain(int *domain_id)
{
  int global_indices[4] = {0, NX-1, 0, NY-1};
  int npes = NPES;
  int cyclic_global_domain = CYCLIC_GLOBAL_DOMAIN;
  int fold_north_edge = FOLD_NORTH_EDGE;
  int whalo=WHALO;
  int ehalo=EHALO;
  int nhalo=NHALO;
  int shalo=SHALO;
  
  cDomainStruct cdomain;
  
  cFMS_null_cdomain(&cdomain);

  cdomain.layout = (int *)calloc(2, sizeof(int));
  cFMS_define_layout(global_indices, &npes, cdomain.layout);

  cdomain.global_indices = global_indices;
  cdomain.domain_id = domain_id;
  cdomain.whalo = &whalo;
  cdomain.ehalo = &ehalo;
  cdomain.shalo = &shalo;
  cdomain.nhalo = &nhalo;
  cdomain.xflags = &cyclic_global_domain;
  cdomain.yflags = &fold_north_edge;

  cFMS_define_domains_easy(cdomain);
}

void test_vector_double3d(int *domain_id)
{
    int isc, iec, jsc, jec;
    int isd, ied, jsd, jed;
    int xsize_c = 0;
    int xsize_d = 0;
    int ysize_c = 0;
    int ysize_d = 0;
    int whalo = WHALO;
    int ehalo = EHALO;
    int shalo = SHALO;
    int nhalo = NHALO;

    int *xmax_size  = NULL;
    int *ymax_size  = NULL;
    int *tile_count = NULL;
    int *position   = NULL;
    bool *x_is_global = NULL;
    bool *y_is_global = NULL;  

    // get compute domain indices
    cFMS_get_compute_domain(domain_id, &isc, &iec, &jsc, &jec, &xsize_c, xmax_size, &ysize_c, ymax_size,
                            x_is_global, y_is_global, tile_count, position, &whalo, &shalo);

    // get data domain sizes
    cFMS_get_data_domain(domain_id, &isd, &ied, &jsd, &jed, &xsize_d, xmax_size, &ysize_d, ymax_size,
                         x_is_global, y_is_global, tile_count, position, &whalo, &shalo);

    double *global_data = (double *)calloc(xsize_d*ysize_d*NZ,sizeof(double));
    double *x_data = (double *)calloc(xsize_d*ysize_d*NZ,sizeof(double));
    int x_shape[3] = {NZ, ysize_d, xsize_d};
    double *y_data = (double *)calloc(xsize_d*ysize_d*NZ,sizeof(double));
    int y_shape[3] = {NZ, ysize_d, xsize_d};

    for(int k = 0; k<NZ; k++)
    {
        for(int j = NHALO; j<NY+SHALO; j++)
        {
            for(int i = EHALO; i<NX+WHALO; i++)
            {
                global_data[k*xsize_d*ysize_d + j*xsize_d + i] = k + i*1e-3 + j*1e-6;
            }
        }
    }

    // fill in north edge, cyclic east, and west edge

    for(int k = 0; k<NZ; k++)
    {
        for(int j = NHALO; j<NY+SHALO; j++)
        {
            for(int i = 0; i<WHALO; i++)
            {
                global_data[k*xsize_d*ysize_d + j*xsize_d + i] = global_data[k*xsize_d*ysize_d + j*xsize_d + NX + i];
                global_data[k*xsize_d*ysize_d + j*xsize_d + NX + EHALO + i] = global_data[k*xsize_d*ysize_d + j*xsize_d + EHALO + i];
            }
        }
    }

    for(int k = 0; k<NZ; k++)
    {
        for(int j = 0; j<2; j++)
        {
            for(int i = 0; i<EHALO+NX+WHALO; i++)
            {
                global_data[k*xsize_d*ysize_d + (j + NHALO + NY)*xsize_d + i] = -global_data[k*xsize_d*ysize_d + (NY-j)*xsize_d + EHALO+NX - i];
                global_data[k*xsize_d*ysize_d + (NY+NHALO+j)*xsize_d + EHALO + NX + WHALO] = -global_data[k*xsize_d*ysize_d + (NY+NHALO-j)*xsize_d + NX + 1];
            }
        }
    }

    for(int k = 0; k<NZ; k++)
    {
        for(int j = 0; j<ysize_c; j++)
        {
            for(int i = 0; i<xsize_c; i++)
            {
                x_data[k*xsize_d*ysize_d + (j + NHALO)*xsize_d + (i + EHALO)] = global_data[k*xsize_d*ysize_d + (j+NHALO)*xsize_d + (i+EHALO)];
                y_data[k*xsize_d*ysize_d + (j + NHALO)*xsize_d + (i + EHALO)] = global_data[k*xsize_d*ysize_d + (j+NHALO)*xsize_d + (i+EHALO)];
            }
        }
    }

    // for(int k = 0; k < NZ; k++)
    // {
    //     for(int j = 0; j < 5; j++)
    //     {
    //         for(int i = 0; i < 5; i++)
    //         {
    //             printf("before: x_data = %f, y_data = %f\n", x_data[k*xsize_d*ysize_d + j*xsize_d + i], y_data[k*xsize_d*ysize_d + j*xsize_d + i]);
    //         }
    //     }
    // }

    int *flags = NULL;
    int gridtype = BGRID_NE;
    int *complete = NULL;
    char *name = NULL;

    cFMS_v_update_domains_double_3d(x_shape, x_data, y_shape, y_data, domain_id, flags,
                                     &gridtype, complete, &whalo, &ehalo, &shalo, &nhalo,
                                     name, tile_count);

    // printf("\n");
                                     
    // for(int k = 0; k < NZ; k++)
    // {
    //     for(int j = 0; j < 5; j++)
    //     {
    //         for(int i = 0; i < 5; i++)
    //         {
    //             printf("after: x_data = %f, y_data = %f\n", x_data[k*xsize_d*ysize_d + j*xsize_d + i], y_data[k*xsize_d*ysize_d + j*xsize_d + i]);
    //         }
    //     }
    // }

    free(global_data);
    free(x_data);
    free(y_data);




}