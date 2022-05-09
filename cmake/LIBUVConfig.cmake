message("----- CONFIGURING LIBUV -----")
set(BUILD_TESTING OFF CACHE BOOL "")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../third_party/libuv)
add_library(uv::uv_static ALIAS uv_a)
add_library(uv::uv ALIAS uv)


