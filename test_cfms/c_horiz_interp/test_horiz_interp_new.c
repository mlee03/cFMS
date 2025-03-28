#include <stdlib.h>
#include <stdio.h>
#include <c_fms.h>
#include <c_horiz_interp.h>
#include <c_mpp_domains_helper.h>
#include <math.h>

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

/*
Adapted from test_horiz_interp :: test_assign
*/

int main()
{
    float *lat_in_1D, *lon_in_1D;
    float *lat_in_2D, *lon_in_2D;
    float *lat_out_1D, *lon_out_1D;
    float *lat_out_2D, *lon_out_2D;
    float *lon_src_1d, *lat_src_1d;
    float *lon_dst_1d, *lat_dst_1d;
    int nlon_in, nlat_in;
    int nlon_out, nlat_out;
    float dlon_src, dlat_src, dlon_dst, dlat_dst;

    float lon_src_beg = 0.;
    float lon_src_end = 360.;
    float lat_src_beg = -90.;
    float lat_src_end = 90.;
    float lon_dst_beg = 0.;
    float lon_dst_end = 360.;
    float lat_dst_beg = -90.;
    float lat_dst_end = 90.;
    float D2R = 3.14/180.;
    float SMALL = 1.0e-10;

    char interp_method[MESSAGE_LENGTH] = "conservative";

    dlon_src = (lon_src_end-lon_src_beg)/NI_SRC;
    dlat_src = (lat_src_end-lat_src_beg)/NJ_SRC;
    dlon_dst = (lon_dst_end-lon_dst_beg)/NI_DST;
    dlat_dst = (lat_dst_end-lat_dst_beg)/NJ_DST;

    cDomainStruct domain;  
    int domain_id = 0;
    int ndiv = 2;
    int global_indices[] = {0,NI_DST,0,NJ_DST};
    
    cFMS_init(NULL,NULL,NULL,NULL,NULL);
    cFMS_null_cdomain(&domain);

    //set domain 
   { 
    domain.global_indices = global_indices;
    domain.domain_id = &domain_id;
    
    domain.layout = (int *)malloc(2*sizeof(int));
    cFMS_define_layout(global_indices, &ndiv, domain.layout);
    
    cFMS_define_domains_easy(domain);
    if( !cFMS_domain_is_initialized(&domain_id) ) cFMS_error(FATAL, "error in setting domain");
   }

     int isc = 0;
     int iec = 0;
     int jsc = 0;
     int jec = 0;
    
    cFMS_get_compute_domain(&domain_id, &isc, &iec, &jsc, &jec,
                            NULL, NULL, NULL, NULL,
                            NULL, NULL, NULL, NULL,
                            NULL, NULL);

    int lon_in_1d_size = NI_SRC+1;
    int lat_in_1d_size = NJ_SRC+1;
    int lon_out_1d_size = iec+1-isc;
    int lat_out_1d_size = jec+1-jsc;

    lon_in_1D = (float *)malloc(lon_in_1d_size*sizeof(float));
    for(int i=0; i<lon_in_1d_size; i++) lon_in_1D[i] = (lon_src_beg + (i-1)*dlon_src)*D2R;

    lat_in_1D = (float *)malloc(lat_in_1d_size*sizeof(float));
    for(int j=0; j<lat_in_1d_size; j++) lat_in_1D[j] = (lat_src_beg + (j-1)*dlat_src)*D2R;

    lon_out_1D = (float *)malloc(lon_out_1d_size*sizeof(float));
    for(int i=0; i<lon_out_1d_size; i++) lon_out_1D[i] = (lon_dst_beg + (i-1)*dlon_dst)*D2R;

    lat_out_1D = (float *)malloc(lat_out_1d_size*sizeof(float));
    for(int j=0; j<lat_out_1d_size; j++) lat_out_1D[j] = (lat_dst_beg + (j-1)*dlat_dst)*D2R;


    int in_2d_size = (NI_SRC+1)*(NJ_SRC+1);
    int out_2d_size = (iec+1-isc)*(jec+1-jsc);

    lon_in_2D = (float *)malloc(in_2d_size*sizeof(float));
    for(int i=0; i<lon_in_1d_size; i++)
    {
        for(int j=0; j<lat_in_1d_size; j++)
        {
            lon_in_2D[lat_in_1d_size*i + j] = lon_in_1D[i];
        }
    }
    int lon_in_shape[2] = {lon_in_1d_size, lat_in_1d_size};

    lat_in_2D = (float *)malloc(in_2d_size*sizeof(float));
    for(int i=0; i<lon_in_1d_size; i++)
    {
        for(int j=0; j<lat_in_1d_size; j++)
        {
            lat_in_2D[lat_in_1d_size*i + j] = lat_in_1D[j];
        }
    }
    int lat_in_shape[2] = {lon_in_1d_size, lat_in_1d_size};

    lon_out_2D = (float *)malloc(out_2d_size*sizeof(float));
    for(int i=0; i<lon_out_1d_size; i++)
    {
        for(int j=0; j<lat_out_1d_size; j++)
        {
            lon_out_2D[lat_out_1d_size*i + j] = lon_out_1D[i];
        }
    }
    int lon_out_shape[2] = {lon_out_1d_size, lat_out_1d_size};

    lat_out_2D = (float *)malloc(out_2d_size*sizeof(float));
    for(int i=0; i<lon_out_1d_size; i++)
    {
        for(int j=0; j<lat_out_1d_size; j++)
        {
            lat_out_2D[lat_out_1d_size*i + j] = lat_out_1D[j];
        }
    }
    int lat_out_shape[2] = {lon_out_1d_size, lat_out_1d_size};

    cFMS_horiz_interp_init(NULL);

    cFMS_horiz_interp_new_2d_cfloat(lon_in_2D, lon_in_shape, lat_in_2D, lat_in_shape,
                                    lon_out_2D, lon_out_shape, lat_out_2D, lat_out_shape,
                                    interp_method, NULL, NULL, NULL, NULL,
                                    NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    
    cFMS_end();

    free(domain.layout);
    free(lon_in_1D);
    free(lat_in_1D);
    free(lon_out_1D);
    free(lat_out_1D);
    free(lon_in_2D);
    free(lat_in_2D);
    free(lon_out_2D);
    free(lat_out_2D);


    return EXIT_SUCCESS;
}

