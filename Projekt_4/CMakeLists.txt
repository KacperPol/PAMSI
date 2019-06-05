cmake_minimum_required(VERSION 3.11)

set(PROJECT_NAME "tictactoe")

set(SFML_DIR "/home/kpolataj/SFML/lib/cmake/SFML")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CXX_GNU_COMPILE_FLAGS "-Wall -pedantic -Wextra -Werror")
set(CXX_CLANG_COMPILE_FLAGS "-Wall -pedantic -Wextra -Werror")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  list(APPEND CMAKE_CXX_FLAGS  ${CXX_GNU_COMPILE_FLAGS})
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  list(APPEND CMAKE_CXX_FLAGS  ${CXX_CLANG_COMPILE_FLAGS})
endif()

find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

add_executable(tictactoe src/Main.cpp src/BoardManager.cpp src/Coordinates.cpp src/GameManager.cpp src/GameOptionsManager.cpp src/MinMaxManager.cpp src/MyStdIn.cpp)

target_link_libraries(tictactoe sfml-graphics sfml-audio sfml-system sfml-window)

target_include_directories(tictactoe PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
