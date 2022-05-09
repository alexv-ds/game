#include "quad_tree.hpp"

namespace engine::module_impl::world {

std::shared_ptr<IQuadTree> IQuadTree::create_quad_tree() {
  return std::make_shared<QuadTree>();
}

inline loose_quadtree::BoundingBox<float> to_quadtree_bbox(const components::world::BBox& bbox) {
  return {bbox.botleft.x, bbox.topright.y, bbox.topright.x - bbox.botleft.x, bbox.topright.y - bbox.botleft.y};
}

QuadTreeObject::QuadTreeObject(flecs::id_t holder,
                const components::world::BBox& bbox):

                holder(holder),
                bbox(to_quadtree_bbox(bbox))
{}


void BBoxExtractor::ExtractBoundingBox(const QuadTreeObject* object, loose_quadtree::BoundingBox<float>* bbox) {
  (*bbox) = object->bbox;
}


QuadTree::~QuadTree() {
  this->tree.ForceCleanup();
  this->objects.clear();
}

void QuadTree::update(const flecs::entity& entity, const components::world::BBox& bbox) {
  if (auto it = this->objects.find(entity); it != this->objects.end()) {
    it->second->bbox = to_quadtree_bbox(bbox);
    this->tree.Update(it->second.get());
  } else {
    std::unique_ptr object = std::make_unique<QuadTreeObject>(entity, bbox);
    this->tree.Insert(object.get());
    this->objects.insert({entity, std::move(object)});
  }
}

void QuadTree::remove(const flecs::entity& entity) {
  if (auto it = this->objects.find(entity); it != this->objects.end()) {
    this->tree.Remove(it->second.get());
    this->objects.erase(it);
  }
}

void fill_out(std::vector<flecs::entity>& out, QuadTree::Query& query, const flecs::world& world) {
  while (!query.EndOfQuery()) {
    out.push_back(world.entity(query.GetCurrent()->holder));
    query.Next();
  }
}

void QuadTree::query_intersects(std::vector<flecs::entity>& out,
                                const components::world::BBox& bbox, 
                                const flecs::world& world)
{
  Query query = this->tree.QueryIntersectsRegion(to_quadtree_bbox(bbox));
  fill_out(out, query, world);
}

void QuadTree::query_inside(std::vector<flecs::entity>& out,
                                const components::world::BBox& bbox, 
                                const flecs::world& world)
{
  Query query = this->tree.QueryInsideRegion(to_quadtree_bbox(bbox));
  fill_out(out, query, world);
}


void QuadTree::query_contains(std::vector<flecs::entity>& out,
                                const components::world::BBox& bbox, 
                                const flecs::world& world)
{
  Query query = this->tree.QueryContainsRegion(to_quadtree_bbox(bbox));
  fill_out(out, query, world);
}

}