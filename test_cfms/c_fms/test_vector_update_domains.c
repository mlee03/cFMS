#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#include <c_fms.h>
#include <c_mpp_domains_helper.h>

//Adapted from test_mpp_update_domains_real.F90 - Folded xy_halo - CGRID_NE
/*
F -1 0 | 1 2 3 4 5 6 7 8 | 9 10
C  0 1 | 2 3 4 5 6 7 8 9 | 10 11
*/

#define NX 8
#define NY 8
#define NPES 1
#define WHALO 2
#define EHALO 2
#define NHALO 2
#define SHALO 2

void define_domain(int *domain_id);
void test_vector_double2d(int *domain_id);

int main()
{
  int domain_id = 0;

  cFMS_init(NULL,NULL,NULL,NULL,NULL);

  define_domain(&domain_id);
  cFMS_set_current_pelist(NULL,NULL);

  test_vector_double2d(&domain_id);

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

void test_vector_double2d(int *domain_id)
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

    
    /*
      allocate(global1r8(1-xhalo:nx+xhalo, 1-yhalo:ny+yhalo, nz))
      allocate(global2r8(1-xhalo:nx+xhalo, 1-yhalo:ny+yhalo, nz))
      global1r8(:,:,:) = 0.0
      global2r8(:,:,:) = 0.0
    */
    double *global_data1 = (double *)calloc(xsize_d*ysize_d,sizeof(double));
    double *global_data2 = (double *)calloc(xsize_d*ysize_d,sizeof(double));

    /*
      allocate(xr8 (isd:ied+shift,jsd:jed,nz), yr8 (isd:ied,jsd:jed+shift,nz) )
      xr8(:,:,:) = 0.; yr8(:,:,:) = 0.
    */
    double *x_data = (double *)calloc(xsize_d*ysize_d,sizeof(double));
    int x_shape[2] = {xsize_d, ysize_d};
    double *y_data = (double *)calloc(xsize_d*ysize_d,sizeof(double));
    int y_shape[2] = {xsize_d, ysize_d};

    /*
    do k = 1,nz
      do j = 1,ny
        do i = 1,nx
          global1r8(i,j,k) = 1 + i*1e-3 + j*1e-6
          global2r8(i,j,k) = 1 + i*1e-3 + j*1e-6
        end do
    end do
    */
    for(int i = WHALO; i<NX+WHALO; i++)
    {
        for(int j = SHALO; j<NY+SHALO; j++)
        {
                global_data1[i*ysize_d + j] = 1 + i*1e-3 + j*1e-6;
                global_data2[i*ysize_d + j] = 1 + i*1e-3 + j*1e-6;
        }
    }

    /*
    global1r8(1-xhalo:0,                   1:ny,:) =  global1r8(nx-xhalo+1:nx,                     1:ny,:)
    global1r8(nx+1:nx+xhalo,               1:ny,:) =  global1r8(1:xhalo,                           1:ny,:)
    global2r8(1-xhalo:0,                   1:ny,:) =  global2r8(nx-xhalo+1:nx,                     1:ny,:)
    global2r8(nx+1:nx+xhalo,               1:ny,:) =  global2r8(1:xhalo,                           1:ny,:)
    global1r8(1-xhalo:nx+xhalo-1, ny+1:ny+yhalo,:) = -global1r8(nx+xhalo-1:1-xhalo:-1, ny:ny-yhalo+1:-1,:)
    global1r8(nx+xhalo,           ny+1:ny+yhalo,:) = -global1r8(nx-xhalo,              ny:ny-yhalo+1:-1,:)
    global2r8(1-xhalo:nx+xhalo,   ny+1:ny+yhalo,:) = -global2r8(nx+xhalo:1-xhalo:-1,   ny-1:ny-yhalo:-1,:)
    */
    for(int i=0; i<WHALO; i++)
    {
        for(int j=SHALO; j<NY+SHALO; j++)
        {
                global_data1[i*ysize_d + j] = global_data1[(NX+i)*ysize_d + j];
                global_data1[(i + NX + WHALO)*ysize_d + j] = global_data1[(WHALO + i)*ysize_d + j];
                global_data2[i*ysize_d + j] = global_data2[(NX + i)*ysize_d + j];
                global_data2[(NX + WHALO + i)*ysize_d + j] = global_data2[(WHALO + i)*xsize_d + j];
        }
    }
    for(int i=0; i<NX+EHALO+1; i++)
    {
        for(int j=0; j<NHALO; j++)
        {
                global_data1[i*ysize_d + j+NY+SHALO] = -global_data1[(NX+EHALO-i)*ysize_d + NY + 1 - j];
                global_data1[(NX+WHALO+1)*ysize_d + j + NY + SHALO] = -global_data1[(NX-1)*ysize_d + NY - 1 - j];
        }
    }
    for(int i=0; i<WHALO+NX+EHALO; i++)
    {
        for(int j=0; j<NHALO; j++)
        {
                global_data2[i*ysize_d + j + NY + SHALO] = -global_data2[(WHALO+NX+1-i)*ysize_d + NY - j];
        }
    }
    
    /*
    xr8(is:ie+shift,js:je,      :) = global1r8(is:ie+shift,js:je,      :)
    yr8(is:ie      ,js:je+shift,:) = global2r8(is:ie,      js:je+shift,:)
    */
    for(int i = WHALO; i<WHALO+NX; i++)
    {
        for(int j = SHALO; j<SHALO+NY; j++)
        {
            x_data[i*ysize_d + j] = global_data1[i*ysize_d + j];
            y_data[i*ysize_d + j] = global_data2[i*ysize_d + j];
        }
    }

    int *flags = NULL;
    int gridtype = CGRID_NE;
    int *complete = NULL;
    char *name = NULL;

    cFMS_v_update_domains_double_2d(x_shape, x_data, y_shape, y_data, domain_id, flags,
                                     &gridtype, complete, &whalo, &ehalo, &shalo, &nhalo,
                                     name, tile_count);

    int element;
    for(int i = 0; i<12; i++)
    {
        for(int j = 0; j<12; j++)
        {
            element = i*ysize_d + j;
            printf("xd[%d][%d] = %f, gd_1[%d][%d] = %f\n", i,j,x_data[element],i,j,global_data1[element]);
            if(x_data[element] != global_data1[element]) printf("[%d][%d] does not match\n", i, j);
            // printf("gd_1[%d][%d] = %f\n", i,j,global_data1[element]);
        }
    }

    /*
    global2r8(nx/2+1:nx,     ny+shift,:) = -global2r8(nx/2:1:-1, ny+shift,:)
    global2r8(1-xhalo:0,     ny+shift,:) = -global2r8(nx-xhalo+1:nx, ny+shift,:)
    global2r8(nx+1:nx+xhalo, ny+shift,:) = -global2r8(1:xhalo,       ny+shift,:)
    */
    for(int i = 0; i<EHALO+WHALO; i++)
    {
        global_data2[(NY+1)*xsize_d + NX - WHALO + i] = -global_data2[(NY+1)*xsize_d + NX - WHALO - 1 -i];
    }
    for(int i = 0; i<WHALO; i++)
    {
        global_data2[(NY+1)*xsize_d + i] = -global_data2[(NY+1)*xsize_d + NX + i];
        global_data2[(NY+1)*xsize_d + NX + WHALO + i] = -global_data2[(NY+1)*xsize_d + WHALO + i];
    }

    // int element;
    // for(int k = 0; k<NZ; k++)
    // {
    //     for(int j = 0; j<5; j++)
    //     {
    //         for(int i = 0; i<5; i++)
    //         {
    //             element = k*ysize_d*xsize_d + j*xsize_d + i;
    //             printf("x_data[%d][%d][%d] = %f, gd_1[%d][%d][%d] = %f\n", k,j,i,x_data[element],k,j,i,global_data1[element]);
    //         }
    //     }
    // }


    free(global_data1);
    free(global_data2);
    free(x_data);
    free(y_data);




}