#include <cstdio>
#include <flecs.h>
#include <engine/modules/world.hpp>
#include <engine/components/world/transform.hpp>
#include <engine/components/world/entity_type.hpp>
#include <engine/components/world/query.hpp>
#include <engine/components/timer.hpp>
#include <engine/modules/timer.hpp>

using namespace engine::components;

int main(int argc, char const *argv[]) {
  flecs::world world;
  world.import<engine::modules::world>();
  world.import<engine::modules::timer>();

  world.entity()
    .set<engine::components::timer::Timer>({2.0f});

  world.app().enable_rest().run();
}