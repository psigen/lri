#!/bin/sh

# Create a lockfile
lockfile -r 0 ./lri_build.lock || exit 1

# Run cmake in the base directory
make CMAKE=`pwd`/tools/cmake/bin/cmake CMAKE_PREFIX_PATH=`pwd`/tools/protobuf

# Remove this lockfile
rm -f ./lri_build.lock
