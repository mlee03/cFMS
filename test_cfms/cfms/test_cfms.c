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
#include <mpi.h>
#include <cfms.h>

int test_cfms_init();

int main() {

  int test_result;
  
  test_result = test_cfms_init();
  if(test_result != 0) return 1;

  return 0;

}

int test_cfms_init()
{
  //initialize MPI with mpp

  int ndomain=2;
  int mpi_flag=100;  
  
  cfms_init(NULL, NULL, &ndomain);

  MPI_Initialized(&mpi_flag);  
  if(mpi_flag == 0) return 1;
  
  return 0;
}

int test_cmfs_
