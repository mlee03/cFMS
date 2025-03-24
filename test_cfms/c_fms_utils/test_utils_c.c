#include <stdio.h>
#include <stdlib.h>
#include <c_fms.h>

#define NX 10
#define NY 5
#define NZ 2

extern void test_3d_cdouble(int *array_shape, double *c_pointer);

int main()
{

  double *array_3d;
  int shape[3] = {NX, NY, NZ};
  int ijk;
  
  array_3d = (double *)malloc(NX*NY*NZ*sizeof(double));
  
  ijk = 0;
  for(int i=0; i<NX; i++){
    for(int j=0; j<NY; j++){
      for(int k=0; k<NZ; k++){
        array_3d[ijk++] = i*100. + j*10. + k*1.;
      }
    }
  }

  test_3d_cdouble(shape, array_3d);
  
  ijk = 0;
  for(int i=0; i<NX; i++){
    for(int j=0; j<NY; j++){
      for(int k=0; k<NZ; k++){
        if(array_3d[ijk++] != -i*100. - j*10. - k*1.) {
          cFMS_error(FATAL, "ERROR CONVERTING ARRAY TO POINTER");
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  
  return EXIT_SUCCESS;
  
}
