#ifndef QCHAIN_HPP
#define QCHAIN_HPP
#include "Geometry/Circle.hpp"
#include "QBox2D/QBody.hpp"
#include "Graphics/TexturedPolygon.hpp"

class QChain : public QBody {
 private:
  std::vector<QPointF> m_vertices;
  TexturedPolygon m_texture;

  void createChain();

 public:
  QChain(SceneGraph::Item * = nullptr);
  ~QChain();

  const std::vector<QPointF> &vertices() const { return m_vertices; }
  void setVertices(const std::vector<QPointF> &v);

  void cutCircle(Circle);

  bool testPoint(const QPointF &point) const;

  bool read(const QJsonObject &);
  bool write(QJsonObject &) const;

  const TexturedPolygon& texture() const { return m_texture; }
  TexturedPolygon& texture() { return m_texture; }
};

#endif  // QCHAIN_HPP
