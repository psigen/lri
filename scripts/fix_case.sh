#!/bin/sh
#
# Converts all CMake commands to lowercase.  Useful for cleaning up 
# CMakeLists.txt with mixed case conventions.
#
# Adapted from:
# http://www.cmake.org/pipermail/cmake/2008-May/021752.html
#

command_list=`cmake --help-command-list | grep -v 'cmake version '`

fix_case ()
{
    LC_COMMAND=$1
    UC_COMMAND=`echo $LC_COMMAND | tr '[a-z]' '[A-Z]'`
    echo "Replacing \"$UC_COMMAND\" with \"$LC_COMMAND\"..."
    find . -name CMakeLists.txt -exec sed -i s/$UC_COMMAND\
*\(/$LC_COMMAND\(/ {} \;
    find . -name \*.cmake       -exec sed -i s/$UC_COMMAND\
*\(/$LC_COMMAND\(/ {} \;
}

for command in $command_list
do
    fix_case $command
done

