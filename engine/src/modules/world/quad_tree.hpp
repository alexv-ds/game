#pragma once
#include <memory>
#include <vector>
#include <flecs.h>
#include <LooseQuadtree.h>
#include <engine/components/world/query.hpp>
#include <engine/components/world/transform.hpp>
#include <engine/noncopyable.hpp>
#include "IQuadTree.hpp"

namespace engine::module_impl::world {

class QuadTreeObject {
public:
  QuadTreeObject(flecs::entity_t holder, const components::world::BBox& bbox);
  flecs::entity_t holder;
  loose_quadtree::BoundingBox<float> bbox;
};


class BBoxExtractor {
public:
  static void ExtractBoundingBox(const QuadTreeObject* object, loose_quadtree::BoundingBox<float>* bbox);
};

class QuadTree : public IQuadTree, public noncopyable {
public:
  using Query = loose_quadtree::LooseQuadtree<float, QuadTreeObject, BBoxExtractor>::Query;
public:
  void update(const flecs::entity&, const components::world::BBox&) override;
  void remove(const flecs::entity&) override;
  void query_intersects(std::vector<flecs::entity>& out, const components::world::BBox&, const flecs::world&) override;
  void query_inside(std::vector<flecs::entity>& out, const components::world::BBox&, const flecs::world&) override;
  void query_contains(std::vector<flecs::entity>& out, const components::world::BBox&, const flecs::world&) override;
  ~QuadTree();

private:
  loose_quadtree::LooseQuadtree<float, QuadTreeObject, BBoxExtractor> tree;
  std::unordered_map<flecs::entity_t, std::unique_ptr<QuadTreeObject>> objects;
};

}