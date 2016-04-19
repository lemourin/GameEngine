#include "Box2DPolygon.hpp"
#include <QJsonArray>
#include <QJsonObject>
#include "Graphics/Primitives.hpp"
#include "Utility/Utility.hpp"

Box2DPolygon::Box2DPolygon(SceneGraph::Item* parent)
    : Fixture(parent), m_texture(this), m_normalMap() {
  setTexture(&m_texture);
  setNormalMap(&m_normalMap);
}

void Box2DPolygon::setVertices(const std::vector<QPointF>& pts) {
  m_texture.setVertices(pts);
  m_normalMap.setVertices(pts);

  m_vertices = pts;
  m_vertices.push_back(m_vertices.front());
}

void Box2DPolygon::setTextureScale(QVector2D scale) {
  m_texture.setTextureScale(scale);
  m_normalMap.setTextureScale(scale);
}

bool Box2DPolygon::read(const QJsonObject& obj) {
  Fixture::read(obj);

  QPointF scale(Utility::Json::toPoint(obj["textureScale"].toObject()));
  setTextureScale((QVector2D)scale);

  std::vector<QPointF> pts;
  QJsonArray array = obj["vertices"].toArray();
  for (int i = 0; i < array.size(); i++)
    pts.push_back(Utility::Json::toPoint(array[i].toObject()));

  setVertices(pts);
  return true;
}

bool Box2DPolygon::write(QJsonObject& obj) const {
  Fixture::write(obj);
  obj["class"] = QString("Box2DPolygon");
  obj["textureScale"] = Utility::Json::toObject(textureScale().toPointF());

  QJsonArray array;
  std::vector<QPointF> pts = vertices();
  for (int i = 0; i < (int)pts.size() - 1; i++)
    array.append(Utility::Json::toObject(pts[i]));

  obj["vertices"] = array;
  return true;
}

std::unique_ptr<b2Shape> Box2DPolygon::createShape() const {
  int vertexCount = m_vertices.size() - 1;
  assert(vertexCount >= 3 && vertexCount <= b2_maxPolygonVertices);

  std::vector<b2Vec2> vertices(vertexCount);
  for (int i = 0; i < vertexCount; i++)
    vertices[i].Set(m_vertices[i].x(), m_vertices[i].y());

  auto shape = std::make_unique<b2PolygonShape>();
  shape->Set(vertices.data(), vertexCount);

  return shape;
}

std::unique_ptr<SceneGraph::Node> Box2DPolygon::synchronize(
    std::unique_ptr<SceneGraph::Node> root) {
  if (!root) {
    root = std::make_unique<ConvexPolygonNode>(vertices());
    static_cast<ConvexPolygonNode*>(root.get())->setColor(Qt::blue);
  }

  return root;
}
