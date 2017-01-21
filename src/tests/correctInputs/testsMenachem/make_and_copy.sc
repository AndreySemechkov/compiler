#!/bin/bash
d=`pwd`
cd ../../../part3/
make clean
make
cp rx-cc $d
cd -
 
