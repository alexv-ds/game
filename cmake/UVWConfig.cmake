message("----- CONFIGURING UVW -----")
option(USE_LIBCPP OFF)
#set(BUILD_UVW_LIBS ON CACHE BOOL "")
#set(FETCH_LIBUV_DEFAULT OFF CACHE BOOL "")
#set(FETCH_LIBUV OFF CACHE BOOL "")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../third_party/uvw)


