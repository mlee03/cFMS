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

if [ -d INPUT ] ; then rm -rf INPUT; fi
mkdir INPUT

#generate input for bilinear 2d
cat <<EOF > input.nml
&test_data_override_ongrid_nml
  test_case=2
/
&data_override_nml
  use_data_table_yaml = .True.
/
EOF

cat <<_EOF > data_table.yaml
data_table:
- grid_name: OCN
  fieldname_in_model: runoff
  override_file:
  - fieldname_in_file: runoff
    file_name: ./INPUT/array_2d.nc
    interp_method: bilinear
  factor: 1.0
_EOF

./test_data_override_ongrid

test_expect_success "c_data_override_2d" 'mpirun -n 4  ./test_data_override_2d'
test_done

#rm -rf INPUT test_data_override_ongrid
