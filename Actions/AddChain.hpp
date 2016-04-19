#ifndef ADDCHAIN_HPP
#define ADDCHAIN_HPP
#include "SceneGraph/Geometry.hpp"
#include "SceneGraph/Material.hpp"
#include "SceneGraph/Node.hpp"
#include "SubAction.hpp"

class AddChain : public SubAction {
 private:
  class Node : public SceneGraph::GeometryNode {
   private:
    SceneGraph::ColorMaterial m_material;
    SceneGraph::Geometry m_geometry;

   public:
    Node(std::vector<QPointF> pts);

    void setLastPoint(QPointF);
  };

  enum DirtyState { MousePos = 1 << 0, Points = 1 << 1, Finished = 1 << 2 };

  typedef int State;

  std::vector<QPointF> m_pts;
  QPointF m_mousePos;
  State m_state;
  ActionObject m_object;

 protected:
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent*);
  void keyPressEvent(QKeyEvent* event);
  std::unique_ptr<SceneGraph::Node> synchronize(
      std::unique_ptr<SceneGraph::Node>);

 public:
  AddChain(MapEditor* = nullptr);

  inline const std::vector<QPointF>& pts() const { return m_pts; }

  void reset();

  inline QString name() const { return "AddChain"; }
};

#endif  // ADDCHAIN_HPP
