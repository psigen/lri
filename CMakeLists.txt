
project(LRI)
cmake_minimum_required(VERSION 2.6)

set(arch ${})

# Compiles externals first
add_subdirectory(ext)

message(STATUS "Compiling LRI sources...")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Arch: ${CMAKE_SYSTEM_PROCESSOR}")

set(CMAKE_CXX_FLAGS "-mmmx -msse -msse2 -msse3 -msse4.1 ")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Add POCO global dependencies
add_definitions(${poco_DEFINITIONS})
include_directories(${poco_INCLUDE_DIRS})

# Set up Protocol Buffers
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/proto)
set(PROTOBUF_IMPORT_DIRS ${PROTOBUF_INCLUDE_DIRS})
file(GLOB PROTO_FILES "proto/*.proto")
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
add_library(libproto ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(libproto ${PROTOBUF_LIBRARIES})

# Build our own stuff
add_executable(udp_server_tester src/test/udp_server_tester.cc)
add_dependencies(udp_server_tester poco_EXTERNAL)
target_link_libraries(udp_server_tester ${poco_LIBRARIES})
