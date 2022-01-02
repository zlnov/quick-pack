cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set (project_name "quick_pack")

project(${project_name} VERSION 1.0.1 DESCRIPTION "")
add_library(${project_name} SHARED
  src/address/address_detail_manager.cpp
  src/address/address_detail.cpp
  src/address/address.cpp
  src/network/broker-recv.cpp
  src/network/broker-other.cpp
  src/network/broker-send.cpp
  src/network/broker-add.cpp
  src/network/broker-structor.cpp
  src/socket/socket_detail.cpp
  src/socket/socket_detail_manager.cpp
)

# flatbuffers include
get_filename_component(PROJECT_TOP_DIR ../ ABSOLUTE)
include_directories(${PROJECT_TOP_DIR}/flatbuffers/include)
# flatbuffers built c++ include
include_directories(${CMAKE_SOURCE_DIR}/build/include/flatbuffers)
# normal includes
include_directories(${CMAKE_SOURCE_DIR}/src)
set_target_properties(${project_name} PROPERTIES VERSION 2.0.0)

set_target_properties(${project_name} PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
