# Downloads and installs POCO libraries
cmake_minimum_required(VERSION 2.6)
project(poco_builder C CXX)

# Add dependency for ExternalProject
include(ExternalProject)

# Download and compile SFML using an external project
ExternalProject_Add(poco_EXTERNAL
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --no-tests --no-samples --static --shared --prefix=<INSTALL_DIR>
    BUILD_COMMAND make POCO_BASE=<SOURCE_DIR> POCO_TARGET_OSNAME=${CMAKE_SYSTEM_NAME} POCO_TARGET_OSARCH=${CMAKE_SYSTEM_PROCESSOR} POCO_BUILD=${CMAKE_CURRENT_BINARY_DIR}
    INSTALL_COMMAND make install
)

# Recover project paths for additional settings
ExternalProject_Get_Property(poco_EXTERNAL SOURCE_DIR BINARY_DIR INSTALL_DIR)

# Tell cmake that the external project generated a library so we
# can add dependencies here instead of later
add_library(poco UNKNOWN IMPORTED)
set_property(TARGET poco
  PROPERTY IMPORTED_LOCATION
  ${INSTALL_DIR}/lib/libPocoFoundation.a
  )
add_dependencies(poco poco_EXTERNAL)

# Set properties as per FindModules
set(poco_FOUND 
  TRUE
  CACHE INTERNAL "" FORCE 
)

set(poco_INCLUDE_DIRS 
  "${INSTALL_DIR}/include"
  CACHE INTERNAL "" FORCE
)

set(poco_LIBRARIES
  "${INSTALL_DIR}/lib/libPocoNet.a"
  "${INSTALL_DIR}/lib/libPocoFoundation.a"
  "${INSTALL_DIR}/lib/libPocoUtil.a"
  "${INSTALL_DIR}/lib/libPocoXML.a"
  "pthread" # TODO: may have to change this later for Windows
  CACHE INTERNAL "" FORCE
)

set(poco_DEFINITIONS
  CACHE INTERNAL "" FORCE
)
