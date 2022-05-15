#pragma once
#include <flecs.h>

namespace engine::modules {

struct uv_loop {
  uv_loop(flecs::world&);
};

};