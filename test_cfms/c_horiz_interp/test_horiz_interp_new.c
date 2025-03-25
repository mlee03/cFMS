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
Adapted from test_horiz_interp.F90
*/

int main()
{
    float dlon_src, dlat_src, dlon_dst, dlat_dst;
    float lon_src_beg = 0.;
    float lon_src_end = 360.;
    float lat_src_beg = -90.;
    float lat_src_end = 90.;
    float lon_dst_beg = -280.;
    float lon_dst_end = 80.;
    float lat_dst_beg = -90.;
    float lat_dst_end = 90.;
    float D2R = 3.14/180.;
    float SMALL = 1.0e-10;

    cDomainStruct domain;  
    int domain_id = 0;
    int ndiv = 2;
    int global_indices[] = {0,NI_DST,0,NJ_DST};
    int whalo = 2;
    int ehalo = 2;
    int shalo = 2;
    int nhalo = 2;
    char name[NAME_LENGTH] = "test domain";
    
    cFMS_init(NULL,NULL,NULL,NULL,NULL);
    cFMS_null_cdomain(&domain);

    //set domain 
   { 
    domain.global_indices = global_indices;
    domain.domain_id = &domain_id;
    domain.whalo = &whalo;
    domain.ehalo = &ehalo;
    domain.shalo = &shalo;
    domain.nhalo = &nhalo;
    domain.name = name;
    
    domain.layout = (int *)malloc(2*sizeof(int));
    cFMS_define_layout(global_indices, &ndiv, domain.layout);
    
    cFMS_define_domains_easy(domain);
    if( !cFMS_domain_is_initialized(&domain_id) ) cFMS_error(FATAL, "error in setting domain");
   }

    int isc = 0;
    int iec = 0;
    int jsc = 0;
    int jec = 0;
    int xsize_check = 0;
    int xmax_size_check = 0;
    int ysize_check = 0;
    int ymax_size_check = 0;
    bool x_is_global_check;
    bool y_is_global_check;
    int *position=NULL;
    
    cFMS_get_compute_domain(&domain_id, &isc, &iec, &jsc, &jec,
                            NULL, NULL, NULL, NULL,
                            NULL, NULL, NULL, NULL,
                            NULL, NULL);

    float *lon2d_src = (float *)malloc((NI_SRC+1)*(NJ_SRC+1)*sizeof(float));
    float *lat2d_src = (float *)malloc((NI_SRC+1)*(NJ_SRC+1)*sizeof(float));
    float *lon1d_src = (float *)malloc((NI_SRC+1)*sizeof(float));
    float *lat1d_src = (float *)malloc((NJ_SRC+1)*sizeof(float));
    float *data_src = (float *)malloc(NI_SRC*NJ_SRC*sizeof(float));

    float *lon2d_dst = (float *)malloc((iec+1-isc)*(jec+1-jec)*sizeof(float));
    float *lat2d_dst = (float *)malloc((iec+1-isc)*(jec+1-jec)*sizeof(float));
    float *lon1d_dst = (float *)malloc((iec+1-isc)*sizeof(float));
    float *lat1d_dst = (float *)malloc((jec+1-jsc)*sizeof(float));
    float *data1_dst = (float *)malloc((iec-isc)*(jec-jsc)*sizeof(float));
    float *data2_dst = (float *)malloc((iec-isc)*(jec-jsc)*sizeof(float));
    float *data3_dst = (float *)malloc((iec-isc)*(jec-jsc)*sizeof(float));
    float *data4_dst = (float *)malloc((iec-isc)*(jec-jsc)*sizeof(float));

    cFMS_horiz_interp_init();

    for(int i=0; i<NI_SRC+1; i++) lon1d_src[i] = (lon_src_beg + (float)(i-1)*dlon_src)*D2R;

    for(int j=0; j<NJ_SRC+1; j++) lat1d_src[j] = (lat_src_beg + (float)(j-1)*dlat_src)*D2R;

    for(int i=0; i<(iec+1-isc); i++) lon1d_dst[i] = (lon_dst_beg + (float)(i-1)*dlon_dst)*D2R;

    for(int j=0; j<(jec+1-jsc); j++) lat1d_dst[j] = (lat_dst_beg + (float)(j-1)*dlat_dst)*D2R;

    int ij = 0;
    while(ij < (NI_SRC+1)*(NJ_SRC+1))
    {
        for(int i=0; i<NI_SRC+1; i++)
        {
            for(int iter=ij; iter<ij+NI_SRC+1; iter++) lon2d_src[iter] = lon1d_src[i];
            ij += NJ_SRC+1;
        }
    }

    ij = 0;
    while(ij < (NI_SRC+1)*(NJ_SRC+1))
    {
        for(int j=0; j<NJ_SRC+1; j++)
        {
            for(int iter=ij; iter<ij+NJ_SRC+1; iter++) lat2d_src[iter] = lat1d_src[j];
            ij += NI_SRC+1;
        }
    }

    ij = 0;
    while(ij < (iec+1-isc)*(jec+1-jsc))
    {
        for(int i=0; i<(iec+1-isc); i++)
        {
            for(int iter=ij; iter<ij+(iec+1-isc); iter++) lon2d_dst[iter] = lon1d_dst[i];
            ij += (jec+1-jsc);
        }
    }

    ij = 0;
    while(ij < (iec+1-isc)*(jec+1-jsc))
    {
        for(int j=0; j<(jec+1-jsc); j++)
        {
            for(int iter=ij; iter<ij+(jec+1-jsc); iter++) lat2d_dst[iter] = lat1d_dst[j];
            ij += (iec+1-isc);
        }
    }

    // set up source data
    ij = 0;
    for(int j=0; j<NJ_SRC; j++)
    {
        for(int i=0; i<NJ_SRC; i++)
        {
            
        }
    }




    // cFMS_set_current_interp(&domain_id);

    // cFMS_get_interp_cdouble(
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL,
    //     NULL
    // );
    
    cFMS_end();

    return EXIT_SUCCESS;
}

