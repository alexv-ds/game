#pragma once
#include <memory>
#include <mutex>
#include <functional>
#include <concurrentqueue.h>
#include <uvw/loop.h>

namespace engine::components::uv_loop {

struct Loop {
  using Task = std::function<void(flecs::world&, uvw::Loop&)>;
  using TaskQueue = moodycamel::ConcurrentQueue<Task>;

  std::shared_ptr<TaskQueue> task_queue;
  std::shared_ptr<uvw::Loop> loop;
  std::shared_ptr<std::recursive_mutex> loop_mutex;
};


}