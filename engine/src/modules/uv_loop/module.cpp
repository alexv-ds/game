#include <engine/modules/uv_loop.hpp>
#include <engine/components/uv_loop.hpp>

namespace engine::modules {

uv_loop::uv_loop(flecs::world& world) {
  world.module<uv_loop>("::engine::uv_loop");

  //engine/components/uv_loop.hpp
  world.component<components::uv_loop::Loop>();

  //systems
  {
    world.system<components::uv_loop::Loop>("systems::UpdateLoop")
      .kind(flecs::OnLoad)
      .term<components::uv_loop::Loop>().singleton()
      .multi_threaded(false)
      .each([](flecs::entity entity, components::uv_loop::Loop& loop) {
        components::uv_loop::Loop::Task task = nullptr;
        while (loop.task_queue->try_dequeue(task)) {
          task(*loop.loop);
        }
        loop.loop->run<uvw::Loop::Mode::NOWAIT>();
      });
  }

  world.set<components::uv_loop::Loop>({
    .task_queue = std::make_shared<moodycamel::ConcurrentQueue<components::uv_loop::Loop::Task>>(),
    .loop = uvw::Loop::create()
  });



}


}
