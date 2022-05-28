#include <cassert>
#include <spdlog/spdlog.h>
#include <uvw/timer.h>
#include <engine/modules/uv_loop.hpp>
#include <engine/modules/timer.hpp>
#include <engine/components/uv_loop.hpp>
#include <engine/components/timer.hpp>

namespace {

struct UV_TimerHandle {
  std::shared_ptr<uvw::TimerHandle> handle;
  std::shared_ptr<engine::components::uv_loop::Loop::TaskQueue> task_queue;

  ~UV_TimerHandle() {
    if (handle) {
      assert(task_queue != nullptr);
      auto handle_var_in_scope = handle;
      task_queue->enqueue([handle_var_in_scope] (flecs::world& world, uvw::Loop& loop) {
        handle_var_in_scope->close();
      });
    }
  }

};

}

namespace engine::modules {

timer::timer(flecs::world& world) {
  world.import<uv_loop>();
  world.module<timer>("::engine::timer");

  //engine/components/timer.hpp
  world.component<components::timer::Timer>()
    .member<float>("timeout");
  world.component<components::timer::TimerEvent>();

  world.component<UV_TimerHandle>("internal::UV_TimerHandle");

  //Systems
  world.system<const components::timer::Timer>("systems::InitTimer")
    .kind(flecs::OnLoad)
    .term<UV_TimerHandle>().oper(flecs::Not)
    .each([](flecs::entity e, const components::timer::Timer& timer) {
      SPDLOG_INFO("Boop");
      //loop безопасен для использования из нескольких потоков
      components::uv_loop::Loop* loop = const_cast<components::uv_loop::Loop*>(e.world().get<components::uv_loop::Loop>());
      if (!loop) {
        return;
      }
      const std::lock_guard lock_guard(*loop->loop_mutex);
      std::shared_ptr<uvw::TimerHandle> handle = loop->loop->resource<uvw::TimerHandle>();
      flecs::id_t entity_id = e;
      e.set<UV_TimerHandle>({
        .handle = handle,
        .task_queue = loop->task_queue
      });
      //set callbacks
      handle->on<uvw::ErrorEvent>([entity_id, task_queue = loop->task_queue](const uvw::ErrorEvent& err, uvw::TimerHandle& handle) {
        SPDLOG_ERROR("TimerHandle error: {}, recreate timer", err.what());
        task_queue->enqueue([entity_id](flecs::world& world, uvw::Loop&) {
          flecs::entity entity = world.entity(entity_id);
          if (entity.is_alive()) {
            entity.remove<UV_TimerHandle>();
          }
        });
      });
      handle->on<uvw::TimerEvent>([entity_id, task_queue = loop->task_queue](const uvw::TimerEvent&, uvw::TimerHandle& handle) {
        SPDLOG_INFO("HI FROM TIMER EVENT");
        task_queue->enqueue([entity_id](flecs::world& world, uvw::Loop&) {
          flecs::entity entity = world.entity(entity_id);
          if (entity.is_alive()) {
            entity.add<components::timer::TimerEvent>();
          }
        });
      });
      //run timer
      SPDLOG_INFO("START TIMER");
      using namespace std::chrono_literals;
      handle->start(1s, 1s);
    });
}

}