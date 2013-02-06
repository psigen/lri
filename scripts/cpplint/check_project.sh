#!/bin/bash
#
# Runs cpplint on every C++ header and source file in the repository.
#
pushd `dirname $0` > /dev/null
./cpplint.py `find ../.. -name "*.h"` `find ../.. -name "*.cpp"`
popd > /dev/null
