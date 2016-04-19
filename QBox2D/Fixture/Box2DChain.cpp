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

SceneGraph::Node* Box2DChain::synchronize(SceneGraph::Node* old) {
  PolygonNode* node = static_cast<PolygonNode*>(old);
  if (!node) {
    node = new PolygonNode(
        std::vector<QPointF>(m_vertices.begin(), m_vertices.end() - 1));
    node->setColor(Qt::red);
  }

  return node;
}
