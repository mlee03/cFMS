#!/bin/bash

set -x

curr_dir=$PWD
install_fms=$curr_dir/FMS/gnuFMS

cd FMS
autoreconf -iv
export FCFLAGS="$FCFLAGS -fPIC"
export CFLAGS="$CFLAGS -fPIC"
./configure --enable-portable-kinds --with-yaml --prefix=$install_fms
make install
cd $curr_dir

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$install_fms/lib"
export FCFLAGS="$FCFLAGS -I$install_fms/include -fPIC"
export CFLAGS="$CFLAGS -I$install_fms/include -fPIC"
export LDFLAGS="$LDFLAGS -lFMS -L$install_fms/lib"

autoreconf -iv
./configure --prefix=$curr_dir/cgnuFMS
make check
