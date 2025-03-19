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

make test_data_override_ongrid
mkdir INPUT

#generate input for scalar
cat <<EOF > input.nml
&test_data_override_ongrid_nml
  test_case=3
  write_only=.True.
/
EOF

cat <<_EOF > data_table.yaml
data_table:
 - grid_name: ATM
   fieldname_in_model: co2
   override_file:
   - fieldname_in_file: co2
     file_name: INPUT/scalar.nc
     interp_method: none
   factor : 1.0
_EOF
fi

./test_data_override_ongrid

test_expect_success "c_data_override" 'mpirun -n 1  ./test_data_override'
test_done

