cmake_minimum_required(VERSION 3.22.1)
project(Game VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(/W3)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "")
endif()

find_package(FLECS REQUIRED)
find_package(FMT REQUIRED)
find_package(GLAD REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)
find_package(LIBUV REQUIRED)
find_package(LODEPNG REQUIRED)
find_package(LOOSEQUADTREE REQUIRED)
find_package(SPDLOG REQUIRED)
find_package(UVW REQUIRED)
find_package(CONCURRENTQUEUE REQUIRED)


add_subdirectory(engine)
add_subdirectory(game)
