#pragma once
#include <glm/vec2.hpp>

namespace engine::components::world {

//При обновлении этих компонентов вызвать OnSet

struct Position : glm::vec2 {};

struct Scale : glm::vec2 {};

struct Rotation {
  float angle = 0; //deg
};



}