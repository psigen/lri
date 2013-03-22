# Downloads and installs the latest SFML snapshot
cmake_minimum_required(VERSION 2.6)

# Add dependency for ExternalProject
include(ExternalProject)

# Download and compile SFML using an external project
ExternalProject_Add(poco_EXTERNAL
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --no-tests --no-samples --static --shared --prefix=<INSTALL_DIR>
    BUILD_COMMAND make POCO_BASE=<SOURCE_DIR>
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND make install
)

# Recover project paths for additional settings
ExternalProject_Get_Property(poco_EXTERNAL SOURCE_DIR BINARY_DIR INSTALL_DIR)

# Tell cmake that the external project generated a library so we
# can add dependencies here instead of later
add_library(poco UNKNOWN IMPORTED)
set_property(TARGET poco
  PROPERTY IMPORTED_LOCATION
  ${INSTALL_DIR}/lib/libpoco.a
  )
add_dependencies(poco poco_EXTERNAL)

# Set properties as per FindModules
set(poco_FOUND 
  TRUE
  CACHE INTERNAL "" FORCE 
)

set(poco_INCLUDE_DIRS 
  "${INSTALL_DIR}/Foundation/include"
  CACHE INTERNAL "" FORCE
)

set(poco_LIBRARIES
  "${INSTALL_DIR}/lib/libpoco.a"
  CACHE INTERNAL "" FORCE
)

set(poco_DEFINITIONS
  ""
  CACHE INTERNAL "" FORCE
)

