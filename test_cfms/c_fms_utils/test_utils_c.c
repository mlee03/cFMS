#include <stdio.h>
#include <stdlib.h>

#define NX 10
#define NY 5
#define NZ 2

// array(NX, NY, NZ)


void test_(int *c_shape, double *c_pointer)
{

  c_shape[0] = NX;
  c_shape[1] = NY;
  c_shape[2] = NZ;
  
  int ijk = 0;
  for(int i=0; i<NX; i++) {
    for(int j=0; j<NY; j++) {
      for(int k=0; k<NZ; k++) {
        c_pointer[ijk] =(i+1)*100. + (j+1)*10. + k+1;
        ijk++;
      }
    }
  }

}
  

