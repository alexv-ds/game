#pragma once

namespace engine::components::timer {

struct Timer {
  float timeout = 0.0f;
};

//Потребитель таймера его может убрать
struct TimerEvent {};

}