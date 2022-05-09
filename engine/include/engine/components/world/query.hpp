#pragma once
#include <vector>
#include <flecs.h>
#include <glm/vec2.hpp>

namespace engine::components::world {

//Прямоугольник в который вписан объект (для построения дерева квадратов)
struct BBox {
  glm::vec2 botleft;
  glm::vec2 topright;
};

//Запрос без задержки, обрабатывается в том же (по возможности) кадре
struct QueryNoDelay {};
 //Запрос завершен, если нужно обновить, то убрать этот флаг
struct QueryDone {};
//Удаляет компонент запроса с энтити, а объект вектора возвращает в пулл для последующего переиспользования
//Удалять можно и ручками, но тогда вектор деаллоцируется
struct QueryDelete {}; 

struct QueryIntersectsRegion {
  std::vector<flecs::entity> entities;
};

struct QueryInsideRegion {
  std::vector<flecs::entity> entities;
};

struct QueryContainsRegion {
  std::vector<flecs::entity> entities;
};

}