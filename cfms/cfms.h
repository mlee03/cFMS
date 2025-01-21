/************************************************************************
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
#ifndef CFMS_H
#define CFMS_H

#include <stdbool.h>
#include <cmpp.h>
#include <cmpp_domains.h>

#define NAME_LENGTH 64 
#define MESSAGE_LENGTH 128

extern const int NOTE;
extern const int WARNING;
extern const int FATAL;

extern int GLOBAL_DATA_DOMAIN;
extern int BGRID_NE;
extern int CGRID_NE;
extern int DGRID_NE;
extern int AGRID;
extern int FOLD_SOUTH_EDGE;
extern int FOLD_NORTH_EDGE;
extern int FOLD_WEST_EDGE;
extern int FOLD_EAST_EDGE;  
extern int CYCLIC_GLOBAL_DOMAIN;
extern int NUPDATE;
extern int EUPDATE;
extern int XUPDATE;
extern int YUPDATE;
extern int NORTH;
extern int NORTH_EAST;
extern int EAST;
extern int SOUTH_EAST;
extern int CORNER;
extern int CENTER;
extern int SOUTH;
extern int SOUTH_WEST;
extern int WEST;
extern int NORTH_WEST;
extern int CYCLIC_GLOBAL_DOMAIN;

extern void cFMS_init(int *localcomm, char *alt_input_nml_path, int *ndomain, int *nnest_domain);

extern void cFMS_end();

extern void cFMS_set_pelist_npes(int *npes_in);

#endif

                   
