#***********************************************************************
#*                   GNU Lesser General Public License
#*
#* This file is part of the GFDL Flexible Modeling System (FMS).
#*
#* FMS is free software: you can redistribute it and/or modify it under
#* the terms of the GNU Lesser General Public License as published by
#* the Free Software Foundation, either version 3 of the License, or (at
#* your option) any later version.
#*
#* FMS is distributed in the hope that it will be useful, but WITHOUT
#* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
#* for more details.
#*
#* You should have received a copy of the GNU Lesser General Public
#* License along with FMS.  If not, see <http://www.gnu.org/licenses/>.
#***********************************************************************

# This is an automake file for the fms directory of the FMS
# package.

# Ed Hartnett 2/22/19

# Include .h and .mod files.
AM_CPPFLAGS = -I. -I./include
AM_FCFLAGS = $(FC_MODINC). $(FC_MODOUT)$(MODDIR)

# Build these uninstalled convenience libraries.
noinst_LTLIBRARIES = libcfms.la

# Each convenience library depends on its source.
libcfms_la_SOURCES = cfms.F90 cmpp.F90 cmpp_domains.F90

cfms_mod@cmpp_domains_smod.smod: cmpp_domains.F90 cfms_mod.mod cfms_mod.smod
cfms_mod@cmpp_smod.smod: cmpp.F90 cfms_mod.mod cfms_mod.smod
cfms_mod.mod, cfms_mod.smod: cfms.F90 

# Mod files are built and then installed as headers.
MODFILES = cfms_mod.mod #cfms_mod.smod cfms_mod@cmpp_smod.smod cfms_mod@cmpp_domains_smod.smod
BUILT_SOURCES = $(MODFILES)
nodist_include_HEADERS =  $(FMS_INC_FILES) $(MODFILES)

include_HEADERS = cfms.h cmpp.h cmpp_domains.h

include $(top_srcdir)/mkmods.mk
