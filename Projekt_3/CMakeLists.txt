cmake_minimum_required(VERSION 3.11)

set(PROJECT_NAME "graf")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CXX_GNU_COMPILE_FLAGS "-std=c++11 -Wall -pedantic -Wextra -Werror")
set(CXX_CLANG_COMPILE_FLAGS "-std=c++11 -Wall -pedantic -Wextra -Werror")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  list(APPEND CMAKE_CXX_FLAGS  ${CXX_GNU_COMPILE_FLAGS})
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  list(APPEND CMAKE_CXX_FLAGS  ${CXX_CLANG_COMPILE_FLAGS})
endif()

add_executable(graf src/main.cpp)

target_include_directories(graf PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
