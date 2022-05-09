#include <flecs.h>
#include <engine/modules/world.hpp>

int main(int argc, char const *argv[]) {
  flecs::world world;
  world.import<engine::modules::world>();

  world.app().enable_rest().run();
}