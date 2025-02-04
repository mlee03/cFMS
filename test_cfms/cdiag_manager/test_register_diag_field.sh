#!/bin/sh
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
# This is part of the GFDL FMS package. This is a shell script to
# execute tests in the test_fms/coupler directory.

# Set common test settings.
. ../test-lib.sh

if [ -f "input.nml" ] ; then rm -f input.nml ; fi
cat <<EOF > input.nml
&diag_manager_nml
    use_modern_diag = .true.
/
EOF

#from test_fms/test_diag_manager2.sh
cat <<EOF > diag_table.yaml
title: test_diag_manager
base_date: 2 1 1 0 0 0

diag_files:
- file_name: file1_forecast
  freq: 1 days
  time_units: hours
  unlimdim: time
  varlist:
  - module: atm_mod
    var_name: var1
    reduction: average
    kind: r4
    output_name: var1_min
  - module: atm_mod
    var_name: var1
    reduction: average
    kind: r4
    output_name: var2_max
EOF

test_expect_success "cdiag_maanger" 'mpirun -n 4  ./test_register_diag_field'
test_done

