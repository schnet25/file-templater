#!/bin/bash

BASE_DIR=$(pwd)
if [ -z "$1" ]; then
    PREFIX=/opt/basketbit
else
    PREFIX="$1"
fi
MAKETHREADS="-j4"

# make sure directory exists
mkdir -p ${PREFIX}/lib/pkgconfig
if [ ! -d "${PREFIX}/lib/pkgconfig" ]; then
    echo "Could not create directory '${PREFIX}/lib/pkgconfig'. Please check user permissions";
    exit 1
fi

BOOST_VERSION=1.59.0
if [[ "x$(pkg-config --modversion --silence-errors boost)" == "x${BOOST_VERSION}" ]]; then
    echo "skipping boost install"
else
    echo "building boost ${BOOST_VERSION}"
    tar xf boost_1_59_0.tar.bz2 ; sync
    cd boost_1_59_0
    rm -rf ${PREFIX}/include/boost ${PREFIX}/lib/libboost_*
    ./bootstrap.sh --prefix=${PREFIX} && ./b2 install ${MAKETHREADS} --prefix=${PREFIX} --with-filesystem --with-system --with-program_options
    success=$?
    cd ${BASE_DIR}
    if [ $success -eq 0 ] ; then 
        sed -e s/@version@/${BOOST_VERSION}/g boost.pc.in | sed -e "s|@prefix@|$PREFIX|g" > boost.pc
        mv boost.pc ${PREFIX}/lib/pkgconfig/
    fi
fi

JSONCPP_VERSION=0.9.4
if [[ "x$(pkg-config --modversion --silence-errors jsoncpp)" == "x${JSONCPP_VERSION}" ]]; then
    echo "skipping jsoncpp install"
else 
    echo "building jsoncpp ${JSONCPP_VERSION}"
    tar xf jsoncpp-0.9.4.tar.xz 
    cd jsoncpp-0.9.4
    rm -rf ${PREFIX}/include/json ${PREFIX}/lib/libjsoncpp*
    mkdir -p build &&
    cd build &&
    cmake -DJSONCPP_LIB_BUILD_STATIC=ON -DJSONCPP_LIB_BUILD_SHARED=ON -DCMAKE_INSTALL_PREFIX=${PREFIX} -G "Unix Makefiles" .. &&
    make ${MAKETHREADS} && make install 
    cd ${BASE_DIR}
fi

