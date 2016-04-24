#ifndef BOX2DCIRCLE_HPP
#define BOX2DCIRCLE_HPP

#include "QBox2D/QFixture.hpp"

class Box2DCircle : public QFixture {
 private:
  float m_radius;

 protected:
  std::unique_ptr<b2Shape> createShape() const;
  std::unique_ptr<SceneGraph::Node> synchronize(
      std::unique_ptr<SceneGraph::Node>);

 public:
  explicit Box2DCircle(SceneGraph::Item* = nullptr);

  inline float radius() const { return m_radius; }
  inline void setRadius(float radius) { m_radius = radius; }

  std::vector<QPointF> vertices() const;

  bool write(QJsonObject&) const;
  bool read(const QJsonObject&);
};

#endif  // BOX2DCIRCLE_HPP
