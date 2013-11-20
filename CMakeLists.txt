project(LRI)
cmake_minimum_required(VERSION 2.8.8)

# Define project version information
set(LRI_MAJOR_VERSION 0)
set(LRI_MINOR_VERSION 1)
set(LRI_PATCH_VERSION 0)
set(LRI_VERSION
  ${LRI_MAJOR_VERSION}.${LRI_MINOR_VERSION}.${LRI_PATCH_VERSION})

# Define current build architecture
set(arch ${})

# Enable C++11 support.
add_definitions(-std=c++11)

# Add included cmake modules
set(CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_MODULE_PATH}
  CACHE
  PATH "CMake modules search path"
  )

# Compile externals first
add_subdirectory(ext)

# Print output to indicate type of build
message(STATUS "Compiling LRI sources...")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Arch: ${CMAKE_SYSTEM_PROCESSOR}")

# Set default flags and output paths
set(CMAKE_CXX_FLAGS "-mmmx -msse -msse2 -msse3 -msse4.1 ")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Add default include directories 
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Set up Protocol Buffers
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
set(PROTOBUF_IMPORT_DIRS ${PROTOBUF_INCLUDE_DIRS})

# Set up ZeroMQ
# (TODO: Make this package optional)
find_package(ZeroMQ REQUIRED)
include_directories(${ZEROMQ_INCLUDE_DIRS})

# Build core message types
file(GLOB PROTO_FILES "proto/*.proto")
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
add_library(proto ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(proto ${PROTOBUF_LIBRARIES})

# Build UDB based LRI discovery library
add_library(lri_udp_discovery
    src/discovery/discovery_udp.cc
    src/discovery/zmq_discovery_socket.cc)
add_dependencies(lri_udp_discovery proto)
target_link_libraries(lri_udp_discovery ${ZEROMQ_LIBRARIES} proto)

# Build simple tester executables
add_executable(udp_tester src/test/udp_tester.cc)
target_link_libraries(udp_tester ${ZEROMQ_LIBRARIES})

# Perform unit tests
#enable_testing()
#add_subdirectory(test)
