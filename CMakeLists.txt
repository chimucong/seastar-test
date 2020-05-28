cmake_minimum_required(VERSION 3.10.2)
list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
include (Cooking OPTIONAL)

project(seastar_test)
set(CMAKE_BUILD_TYPE Debug)

#set(ENV{PKG_CONFIG_PATH} "${CMAKE_SOURCE_DIR}/../cmc-seastar/build")

#find_package(PkgConfig)

#pkg_search_module(SEASTARPC REQUIRED seastar)

find_package(Seastar REQUIRED)
add_executable(my_program my_program.cc)

target_link_libraries(my_program PRIVATE Seastar::seastar)
