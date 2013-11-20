# Downloads and installs google-test libraries
cmake_minimum_required(VERSION 2.8.7)
project(gtest_builder C CXX)

# Add dependency for ExternalProject
include(ExternalProject)

# Download and compile google test using an external project
ExternalProject_Add(gtest_EXTERNAL
    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk
    CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
               -Dgtest_force_shared_crt=ON
     PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
# Disable install step
    INSTALL_COMMAND ""
)

# Recover project paths for additional settings
ExternalProject_Get_Property(gtest_EXTERNAL SOURCE_DIR BINARY_DIR INSTALL_DIR)

# Tell cmake that the external project generated a library so we
# can add dependencies here instead of later
add_library(gtest UNKNOWN IMPORTED)
set_property(TARGET gtest
  PROPERTY IMPORTED_LOCATION
  ${INSTALL_DIR}/libgtest.a
  )
add_dependencies(gtest gtest_EXTERNAL)

# Set properties as per FindModules
set(gtest_FOUND
  TRUE
  CACHE INTERNAL "" FORCE
)

set(gtest_INCLUDE_DIRS
  "${SOURCE_DIR}/include"
  CACHE INTERNAL "" FORCE
)

set(gtest_LIBRARIES
  "${BINARY_DIR}/libgtest.a"
  CACHE INTERNAL "" FORCE
)

set(gtest_DEFINITIONS
  CACHE INTERNAL "" FORCE
)




