#include "Box2DEdge.hpp"
#include "Graphics/Primitives.hpp"

Box2DEdge::Box2DEdge(Item* parent) : QFixture(parent) {}

std::vector<QPointF> Box2DEdge::vertices() const {
  QPointF p1(m_edgeShape.m_vertex1.x, m_edgeShape.m_vertex1.y);
  QPointF p2(m_edgeShape.m_vertex2.x, m_edgeShape.m_vertex2.y);

  return {p1, p2};
}

std::unique_ptr<b2Shape> Box2DEdge::createShape() const {
  return std::make_unique<b2EdgeShape>(m_edgeShape);
}

std::unique_ptr<SceneGraph::Node> Box2DEdge::synchronize(
    std::unique_ptr<SceneGraph::Node> root) {
  if (!root) {
    std::vector<QPointF> v = vertices();
    root = std::make_unique<EdgeNode>(v[0], v[1]);
  }

  return root;
}
