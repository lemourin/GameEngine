#ifndef GRABITEM_HPP
#define GRABITEM_HPP
#include "QBox2D/QJoint.hpp"
#include "SceneGraph/Geometry.hpp"
#include "SceneGraph/Material.hpp"
#include "SceneGraph/Node.hpp"
#include "SubAction.hpp"

class QWorld;
class QBody;
class b2MouseJoint;

class ArrowNode : public SceneGraph::GeometryNode {
 private:
  friend class GrabItem;

  SceneGraph::Geometry m_geometry;
  SceneGraph::ColorMaterial m_material;

  QPointF m_p1, m_p2;

 public:
  ArrowNode();

  inline void setP1(const QPointF& p) { m_p1 = p; }
  inline void setP2(const QPointF& p) { m_p2 = p; }

  void updateGeometry();
};

class GrabItem : public SubAction {
 private:
  friend class World;

  std::unique_ptr<QMouseJoint> m_mouseJoint;
  QBody* m_grabbedBody;
  bool m_pressed;

  ActionObject m_object;

  void destroyJoint();

 protected:
  std::unique_ptr<SceneGraph::Node> synchronize(std::unique_ptr<SceneGraph::Node> old);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

 public:
  GrabItem(MapEditor*);
  ~GrabItem();

  bool pickItem(QPointF point);
  void releaseItem();
  void setDirection(QPointF);

  void reset();

  inline QString name() const { return "GrabItem"; }
};

#endif  // GRABITEM_HPP
