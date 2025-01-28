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
#define PATH_LENGTH 128

extern const int NOTE;
extern const int WARNING;
extern const int FATAL;

/*
extern const int NAME_LENGTH;
extern const int MESSAGE_LENGTH;
extern const int PATH_LENGTH;
*/

extern const int GLOBAL_DATA_DOMAIN;
extern const int BGRID_NE;
extern const int CGRID_NE;
extern const int DGRID_NE;
extern const int AGRID;
extern const int FOLD_SOUTH_EDGE;
extern const int FOLD_NORTH_EDGE;
extern const int FOLD_WEST_EDGE;
extern const int FOLD_EAST_EDGE;  
extern const int CYCLIC_GLOBAL_DOMAIN;
extern const int NUPDATE;
extern const int EUPDATE;
extern const int XUPDATE;
extern const int YUPDATE;
extern const int NORTH;
extern const int NORTH_EAST;
extern const int EAST;
extern const int SOUTH_EAST;
extern const int CORNER;
extern const int CENTER;
extern const int SOUTH;
extern const int SOUTH_WEST;
extern const int WEST;
extern const int NORTH_WEST;
extern const int CYCLIC_GLOBAL_DOMAIN;

extern void cFMS_init(int *localcomm, char *alt_input_nml_path, int *ndomain, int *nnest_domain);

extern void cFMS_end();

extern void cFMS_set_pelist_npes(int *npes_in);

#endif

                   
