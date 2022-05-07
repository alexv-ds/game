message("----- CONFIGURING LODEPNG -----")
set(BUILD_TESTING OFF CACHE BOOL "")
add_library(lodepng
  ${CMAKE_CURRENT_LIST_DIR}/../third_party/lodepng/lodepng.cpp
)
target_include_directories(lodepng PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../third_party/lodepng)
add_library(lodepng::lodepng ALIAS lodepng)

