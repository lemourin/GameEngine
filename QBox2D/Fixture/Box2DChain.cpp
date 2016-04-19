#include "Box2DChain.hpp"
#include <QJsonObject>
#include "Graphics/Primitives.hpp"

Box2DChain::Box2DChain(SceneGraph::Item* parent) : Box2DPolygon(parent) {}

bool Box2DChain::write(QJsonObject& obj) const {
  Box2DPolygon::write(obj);
  obj["class"] = QString("Box2DChain");
  return true;
}

std::unique_ptr<b2Shape> Box2DChain::createShape() const {
  int vertexCount = m_vertices.size() - 1;

  auto chainShape = std::make_unique<b2ChainShape>();
  std::vector<b2Vec2> vertices(vertexCount);
  for (int i = 0; i < vertexCount; i++)
    vertices[i].Set(m_vertices[i].x(), m_vertices[i].y());
  chainShape->CreateLoop(vertices.data(), vertexCount);

  return chainShape;
}

std::unique_ptr<SceneGraph::Node> Box2DChain::synchronize(
    std::unique_ptr<SceneGraph::Node> node) {
  if (!node) {
    node = std::make_unique<PolygonNode>(
        std::vector<QPointF>(m_vertices.begin(), m_vertices.end() - 1));
    static_cast<PolygonNode*>(node.get())->setColor(Qt::red);
  }

  return node;
}
