#include <stdlib.h>
#include <stdio.h>
#include <c_fms.h>
#include <c_horiz_interp.h>
#include <c_mpp_domains_helper.h>

#define NX 8
#define NY 8
#define NPES 4
#define WHALO 2
#define EHALO 2
#define NHALO 2
#define SHALO 2
#define NI_SRC 360
#define NJ_SRC 180
#define NI_DST 144
#define NJ_DST 72

int main()
{
    // domain info
    int domain_id = 0;
    int isc, iec, jsc, jec;
    int xsize_c = 0;
    int ysize_c = 0;
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

    // grid data - might need to move to separate test call
    int nlon_in, nlat_in, nlon_out, nlat_out;
    float dlon_src, dlat_src, dlon_dst, dlat_dst;
    float lon_src_beg = 0.;
    float lon_src_end = 360.;
    float lat_src_beg = -90.;
    float lat_src_end = 90.;
    float lon_dst_beg = 0.0;
    float lon_dst_end = 360.;
    float lat_dst_beg = -90.;
    float lat_dst_end = 90.;
    float D2R = 3.14/180.;

    dlon_src = (lon_src_end-lon_src_beg)/(float)NI_SRC;
    dlat_src = (lat_src_end-lat_src_beg)/(float)NJ_SRC;
    dlon_dst = (lon_dst_end-lon_dst_beg)/(float)NI_DST;
    dlat_dst = (lat_dst_end-lat_dst_beg)/(float)NJ_DST;

    float *lon_in_1d = (float *)malloc(NI_SRC*sizeof(float));
    float *lat_in_1d = (float *)malloc(NJ_SRC*sizeof(float));
    float *lon_out_1d = (float *)malloc((iec-isc)*sizeof(float));
    float *lat_out_1d = (float *)malloc((jec-jsc)*sizeof(float));

    for(int i = 0; i<NI_SRC; i++) lon_in_1d[i] = (lon_src_beg + (float)i*dlon_src)*D2R;
    for(int i = 0; i<NJ_SRC; i++) lat_in_1d[i] = (lat_src_beg + (float)i*dlat_src)*D2R;
    for(int i = 0; i<(iec-isc); i++) lon_out_1d[i] = (lon_dst_beg + (float)i*dlon_dst)*D2R;
    for(int i = 0; i<(jec-jsc); i++) lat_out_1d[i] = (lat_dst_beg + (float)i*dlat_dst)*D2R;

    float **lon_in_2d = (float **)malloc(NI_SRC*sizeof(float *));
    for(int i = 0; i<NI_SRC; i++)
    {
        lon_in_2d[i] = (float *)malloc(NJ_SRC*sizeof(float));
        for(int j = 0; j<NJ_SRC; j++)
        {
            lon_in_2d[i][j] = lon_in_1d[i];
        }
    }
    int lon_in_shape = {NI_SRC, NJ_SRC};

    float **lat_in_2d = (float **)malloc(NI_SRC*sizeof(float *));
    for(int i = 0; i<NI_SRC; i++)
    {
        lat_in_2d[i] = (float *)malloc(NJ_SRC*sizeof(float));
        for(int j = 0; j<NJ_SRC; j++)
        {
            lat_in_2d[i][j] = lat_in_1d[j];
        }
    }
    int lat_in_shape = {NI_SRC, NJ_SRC};

    float **lon_out_2d = (float **)malloc((iec-isc)*sizeof(float *));
    for(int i = 0; i<(iec-isc); i++)
    {
        lon_out_2d[i] = (float *)malloc((jec-jsc)*sizeof(float));
        for(int j = 0; j<(jec-jsc); j++)
        {
            lon_out_2d[i][j] = lon_out_1d[i];
        }
    }
    int lon_out_shape = {(iec-isc), (jec-jsc)};

    float **lat_out_2d = (float **)malloc((iec-isc)*sizeof(float *));
    for(int i = 0; i<(iec-isc); i++)
    {
        lat_out_2d[i] = (float *)malloc((jec-jsc)*sizeof(float));
        for(int j = 0; j<(jec-jsc); j++)
        {
            lat_out_2d[i][j] = lat_out_1d[i];
        }
    }
    int lat_out_shape = {(iec-isc), (jec-jsc)};

    cFMS_horiz_interp_conserve_new_2dx2d_cfloat(lon_in_2d, lon_in_shape, lat_in_2d, lat_in_shape, lon_out_2d,
                                                lon_out_shape, lat_out_2d, lat_out_shape, )
    

    cFMS_init(NULL,NULL,NULL,NULL);

    cFMS_horiz_interp_init();

    define_domain(&domain_id);

    cFMS_get_compute_domain(domain_id, &isc, &iec, &jsc, &jec, &xsize_c, xmax_size, &ysize_c, ymax_size,
        x_is_global, y_is_global, tile_count, position, &whalo, &shalo);

    

    cFMS_end();

    return EXIT_SUCCESS;
}

void define_domain(int *domain_id)
{
  int global_indices[4] = {0, NI_SRC-1, 0, NJ_SRC-1};
  int npes = NPES;
  int cyclic_global_domain = CYCLIC_GLOBAL_DOMAIN;
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
  cdomain.yflags = &cyclic_global_domain;

  cFMS_define_domains_easy(cdomain);
}