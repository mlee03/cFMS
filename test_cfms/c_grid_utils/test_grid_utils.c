#include <stdio.h>
#include <stdlib.h>
#include <c_grid_utils.h>
#include <c_constants.h>

int main()
{

  int nlon = 100;
  int nlat = 100;
  double *lon;
  double *lat;
  double *area;

  double lon_start, lat_start;
  double lon_end, lat_end;
  double dlon, dlat;
  
  lon = (double *)malloc((nlon+1) * sizeof(double));
  lat = (double *)malloc((nlat+1) * sizeof(double));
  area = (double *)malloc(nlon*nlat*sizeof(double));

  lon_start = 0.0;
  lon_end = -5.0*PI / 4.0;
  lat_start = -PI / 4.0;
  lat_end = PI / 4.0;
  
  dlon = (lon_end-lon_start)/nlon;
  dlat = (lat_end-lat_start)/nlat;
  
  for(int i=0; i<nlon+1; i++) lon[i] = lon_start + dlon*i;
  for(int i=0; i<nlat+1; i++) lat[i] = lat_start + dlat*i;
  
  cFMS_get_grid_area(&nlon, &nlat, lon, lat, area);
  
  return EXIT_SUCCESS;
}

