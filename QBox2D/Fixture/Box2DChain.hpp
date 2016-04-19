#ifndef BOX2DCHAIN_HPP
#define BOX2DCHAIN_HPP
#include "Box2DPolygon.hpp"

class Box2DChain : public Box2DPolygon {
 private:
 protected:
  std::unique_ptr<b2Shape> createShape() const;
  std::unique_ptr<SceneGraph::Node> synchronize(
      std::unique_ptr<SceneGraph::Node>);

 public:
  explicit Box2DChain(Item* = nullptr);

  bool write(QJsonObject&) const;
};

#endif  // BOX2DCHAIN_HPP
