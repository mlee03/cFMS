#!/bin/bash

set -x

curr_dir=$PWD
install_fms=$curr_dir/FMS/gnuFMS

cd FMS
autoreconf -iv
./configure --enable-portable-kinds --prefix=$install_fms
make install
cd $curr_dir

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$install_fms/lib"
export FCFLAGS="$FCFLAGS -I$install_fms/include"
export CFLAGS="$CFLAGS -I$install_fms/include"
export LDFLAGS="$LDFLAGS -lFMS -L$install_dir/lib"

autoreconf -iv
./configure --prefix=$curr_dir/cgnuFMS
make check
