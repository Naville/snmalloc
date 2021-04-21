#!/bin/bash

mkdir build
cd build

if [[ "$CXX" == clang++* ]]; then
    CMAKE_CXX_FLAGS+=" -stdlib=libstdc++";
fi

cmake \
  $CMAKE_ARGS \
  -GNinja \
  -DSNMALLOC_CI_BUILD=ON \
  -DSNMALLOC_RUST_SUPPORT=ON \
  -DSNMALLOC_QEMU_WORKAROUND=ON \
  -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
  -DCMAKE_CXX_FLAGS="$CMAKE_CXX_FLAGS" \
  ${SNMALLOC_SRC-..}
ninja