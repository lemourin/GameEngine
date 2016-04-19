#include "TexturedPolygon.hpp"
#include "Geometry/Triangle.hpp"
#include "Graphics/Primitives.hpp"

TexturedPolygon::TexturedPolygon(SceneGraph::Item* parent)
    : TexturedItem(parent), m_textureScale(1, 1) {}

std::unique_ptr<SceneGraph::Node> TexturedPolygon::synchronize(
    std::unique_ptr<SceneGraph::Node> root) {
  if (!root) root = std::make_unique<Node>(vertices(), textureScale());

  static_cast<Node*>(root.get())->setTexture(texture());

  return root;
}

TexturedPolygon::Node::Node(const std::vector<QPointF>& pts, QVector2D scale)
    : m_geometry({{2, GL_FLOAT}, {2, GL_FLOAT}}, 3 * (pts.size() - 2),
                 sizeof(QVector4D)) {
  m_geometryNode.setGeometry(&m_geometry);
  m_geometryNode.setMaterial(&m_material);
  appendChild(&m_geometryNode);

  m_geometry.setDrawingMode(GL_TRIANGLES);

  QVector4D* array = m_geometry.vertexData<QVector4D>();
  std::vector<QPointF> p;
  Geometry::toTriangles(pts, p);
  for (size_t i = 0; i < p.size(); i++)
    array[i] = QVector4D(p[i].x(), p[i].y(), p[i].x() * scale.x(),
                         p[i].y() * scale.y());
  m_geometry.updateVertexData();
}

void TexturedPolygon::Node::setTexture(QOpenGLTexture* texture) {
  m_material.setTexture(texture);
}
