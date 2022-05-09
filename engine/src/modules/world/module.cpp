#include <engine/modules/world.hpp>
#include <engine/components/world/transform.hpp>
#include <engine/components/world/entity_type.hpp>
#include <engine/components/world/query.hpp>
#include "internal_components.hpp"

namespace engine::modules {

world::world(flecs::world& ecs) {
  ecs.module<world>("::engine::world");
  
  //engine/components/transform.hpp
  ecs.component<components::world::Position>()
    .member<float>("x")
    .member<float>("y");
  ecs.component<components::world::Scale>()
    .member<float>("x")
    .member<float>("y");
  ecs.component<components::world::Rotation>()
    .member<float>("angle");

  //engine/components/world/entity_type.hpp
  ecs.component<components::world::Square>();

  //engine/components/world/query.hpp
  ecs.component<components::world::BBox>();
  ecs.component<components::world::QueryNoDelay>();
  ecs.component<components::world::QueryDone>();
  ecs.component<components::world::QueryDelete>();
  ecs.component<components::world::QueryIntersectsRegion>();
  ecs.component<components::world::QueryInsideRegion>();
  ecs.component<components::world::QueryContainsRegion>();

  //internal_components.hpp
  ecs.component<components::world::WorldConroller>("internal::WorldController");
  //ecs.set<components::world::WorldConroller>({});
}



}