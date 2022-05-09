add_library(engine
  src/test.cpp

  src/modules/world/module.cpp
  src/modules/world/quad_tree.cpp
)
add_library(engine::engine ALIAS engine)

target_link_libraries(engine PUBLIC
  flecs::flecs_static
  fmt::fmt
  glad::glad
  glfw::glfw
  glm::glm
  uv::uv_static
  lodepng::lodepng
  loose_quadtree::loose_quadtree
  spdlog::spdlog
  uvw::uvw
)

target_include_directories(engine PUBLIC include)