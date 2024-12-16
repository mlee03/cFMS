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
#ifndef CMPP_H
#define CMPP_H

#include <stdbool.h>

extern void cFMS_error(int errortype, char *errormsg);

extern void cFMS_declare_pelist(int *pelist, char *name, int *commID);

extern void cFMS_get_current_pelist(int *pelist, char *name, int *commID);

extern int cFMS_npes();

extern int cFMS_pe();

extern void cFMS_set_current_pelist(int *pelist, bool *no_sync);

#endif
