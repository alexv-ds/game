message("----- CONFIGURING GLWF -----")
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)
option(GLFW_USE_HYBRID_HPG ON)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../third_party/glfw)


