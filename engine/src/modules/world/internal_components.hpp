#pragma once
#include <memory>
#include <unordered_map>
#include <flecs.h>
#include "IQuadTree.hpp"

namespace engine::components::world {

//using namespace module_impl::world;

struct WorldConroller {
  std::shared_ptr<module_impl::world::IQuadTree> tree;
};

struct TreeObject {};
struct UpdateTreeObject {};

};