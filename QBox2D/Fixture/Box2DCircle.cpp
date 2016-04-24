#include "Box2DCircle.hpp"
#include <QJsonObject>
#include "Geometry/Circle.hpp"
#include "Graphics/Primitives.hpp"

Box2DCircle::Box2DCircle(Item* parent) : QFixture(parent), m_radius() {}

std::vector<QPointF> Box2DCircle::vertices() const {
  const size_t accuracy = 8;

  std::vector<QPointF> v;
  for (size_t i = 0; i < accuracy; i++) {
    qreal angle = i * 2 * M_PI / accuracy;
    v.push_back(QPointF(cos(angle) * radius(), sin(angle) * radius()));
  }

  v.push_back(v.front());

  return v;
}

bool Box2DCircle::write(QJsonObject& obj) const {
  QFixture::write(obj);
  obj["class"] = QString("Box2DCircle");
  obj["radius"] = radius();
  return true;
}

bool Box2DCircle::read(const QJsonObject& obj) {
  QFixture::read(obj);
  m_radius = obj["radius"].toDouble();
  return true;
}

std::unique_ptr<b2Shape> Box2DCircle::createShape() const {
  std::unique_ptr<b2Shape> shape(std::make_unique<b2CircleShape>());
  b2CircleShape* circle = static_cast<b2CircleShape*>(shape.get());
  circle->m_radius = m_radius;
  circle->m_p.Set(position().x(), position().y());

  return shape;
}

std::unique_ptr<SceneGraph::Node> Box2DCircle::synchronize(
    std::unique_ptr<SceneGraph::Node> root) {
  if (!root) {
    root = std::make_unique<CircleNode>(QPointF(), radius());
    static_cast<CircleNode*>(root.get())->setColor(Qt::green);
  }

  return root;
}
