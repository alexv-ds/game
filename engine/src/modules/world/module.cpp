#include <engine/modules/world.hpp>
#include <engine/components/world/transform.hpp>
#include <engine/components/world/entity_type.hpp>
#include <engine/components/world/query.hpp>
#include "internal_components.hpp"
#include <cstdio>

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
  ecs.component<components::world::WorldSquareObject>();

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

  //set singleton
  ecs.set<components::world::WorldConroller>({module_impl::world::IQuadTree::create_quad_tree()});

  //observers
  /*ecs.observer<components::world::BBox>("observers::OnAddSetBBox")
    .event(flecs::OnAdd)
    .event(flecs::OnSet)
    .each([] (flecs::entity entity) {
      entity.add<components::world::UpdateTree>();
      entity.remove<components::world::RemoveTree>();
    });
  ecs.observer<components::world::BBox>("observers::OnRemoveBBox")
    .event(flecs::OnRemove)
    .each([] (flecs::entity entity) {
      entity.remove<components::world::UpdateTree>();
      entity.add<components::world::RemoveTree>();
    });*/
  ecs.system<const components::world::Position>("systems::InitTreeObject")
    .kind(flecs::OnUpdate)
    .term<components::world::TreeObject>().oper(flecs::Not)
    .each([](flecs::entity entity, const components::world::Position&) {
      entity.add<components::world::TreeObject>();
      entity.add<components::world::UpdateTreeObject>();
    });

  ecs.system<const components::world::TreeObject>("systems::CleanupTreeObject")
    .kind(flecs::OnUpdate)
    .term<components::world::Position>().oper(flecs::Not)
    .each([](flecs::entity entity, const components::world::TreeObject&) {
      entity.remove<components::world::TreeObject>();
      entity.remove<components::world::UpdateTreeObject>();
    });

  ecs.observer<>("observers::OnRemoveTreeObject")
    .event(flecs::OnRemove)
    .term<components::world::TreeObject>()
    .each([](flecs::entity entity) {
      const components::world::WorldConroller* controller = entity.world().get<components::world::WorldConroller>();
      //entity.world().get_mut()
    });
 

}



}