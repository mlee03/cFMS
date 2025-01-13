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
extern const int WEST;
extern const int EAST;
extern const int SOUTH;
extern const int NORTH;

extern void cFMS_init(int *localcomm, char *alt_input_nml_path, int *ndomain, int *nnest_domain);

extern void cFMS_end();

extern void cFMS_set_pelist_npes(int *npes_in);

#endif

                   
