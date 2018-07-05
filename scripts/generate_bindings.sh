#! /bin/bash
#
# generate Lua bindings for all platforms
#

WD=$(dirname $0)



###

cd $WD/../swig

make ios ATTRIBUTES=false $@
make linuxarm ATTRIBUTES=false $@
make desktop ATTRIBUTES=false $@
