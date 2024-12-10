/***********************************************************************
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

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <mpi.h>
#include <errno.h>
#include <cfms.h>

#define SUCCESS 0
#define FAIL 1

#define NDOMAIN 2
int ndomain=NDOMAIN;
int domain_id[] = {0,1};

void test_cFMS_init();
void test_cFMS_define_domains();
void test_cFMS_define_io_domain();

int main() {

  int test_result;

  test_cFMS_init();
  test_cFMS_define_domains();
  test_cFMS_define_io_domain();
  
  cFMS_end();
  
  return SUCCESS;

}

void test_cFMS_init()
{
  //initialize MPI with mpp

  int mpi_flag=100;  

  cFMS_init(NULL, NULL, &ndomain);

  MPI_Initialized(&mpi_flag);  
  if(mpi_flag == 0) perror("FATAL: MPI has not been initialized in test_cFMS_init");
  
  cFMS_error(NOTE, "PASS cFMS_init...");  
  
}

void test_cFMS_define_domains()
{
  int global_indices[] = {1, 384, 1, 384};
  int layout[NDOMAIN] = {2,2}; //require 4 pes
  //int domain_id[NDOMAIN] = {1, 2};
  int npes = 4;
  int pelist[] = {0,1,2,3};
  int *xflags = NULL, *yflags = NULL;
  int *xhalo = NULL, *yhalo = NULL;
  int *xextent = NULL, *yextent = NULL;
  bool **maskmap = NULL;
  char name_domain[NDOMAIN][10] = {"domain1", "domain2"};
  bool *symmetry = NULL;
  int *memory_size = NULL;
  int *whalo = NULL, *ehalo = NULL, *shalo = NULL, *nhalo = NULL;
  bool *is_mosaic = NULL;
  int *tile_count = NULL, *tile_id = NULL;
  bool *complete = NULL;
  int *x_cyclic_offset = NULL, *y_cyclic_offset = NULL;

  cFMS_error(NOTE, "testing cFMS_define_domains");

  for( int idomain=0 ; idomain<NDOMAIN ; idomain++ ) {
    
    cFMS_set_npes(&npes);
    cFMS_define_domains(global_indices, layout, domain_id+idomain, pelist, xflags, yflags, xhalo, yhalo,
                        xextent, yextent, maskmap, name_domain[idomain], symmetry, memory_size, whalo, ehalo, shalo, nhalo,
                        is_mosaic, tile_count, tile_id, complete, x_cyclic_offset, y_cyclic_offset);
    
    //check if domain is initialized
    if( ! cFMS_domain_is_initialized(&domain_id[0]) ) cFMS_error(FATAL, "domain is not initialized");
    
  } //for idomain
  
  cFMS_error(NOTE, "PASS test_cFMS_define_domains");
}

void test_cFMS_define_io_domain()
{

  cFMS_error(NOTE, "testing cFMS_define_io_domain");

  for( int idomain=0 ; idomain<NDOMAIN; idomain++ ) {
    int io_layout[] = {idomain+1, idomain+1};
    cFMS_define_io_domain(io_layout, domain_id+idomain);
  }

  cFMS_error(NOTE, "PASS test_cFMS_define_io_domain");
  
}
