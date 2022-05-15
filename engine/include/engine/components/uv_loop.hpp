#pragma once
#include <memory>
#include <functional>
#include <concurrentqueue.h>
#include <uvw/loop.h>

namespace engine::components::uv_loop {

struct Loop {
  using Task = std::function<void(uvw::Loop&)>;

  std::shared_ptr<moodycamel::ConcurrentQueue<Task>> task_queue;
  std::shared_ptr<uvw::Loop> loop;
};


}