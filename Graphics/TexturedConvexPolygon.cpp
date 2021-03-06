#include "TexturedConvexPolygon.hpp"

TexturedConvexPolygon::TexturedConvexPolygon(SceneGraph::Item* parent)
    : TexturedPolygon(parent) {}

std::unique_ptr<SceneGraph::Node> TexturedConvexPolygon::synchronize(
    std::unique_ptr<SceneGraph::Node> root) {
  if (!root) root = std::make_unique<Node>(vertices(), textureScale());

  static_cast<Node*>(root.get())->setTexture(texture());

  return root;
}

TexturedConvexPolygon::Node::Node(const std::vector<QPointF>& pts,
                                  QVector2D scale)
    : m_geometry({{2, GL_FLOAT}, {2, GL_FLOAT}}, pts.size(),
                 sizeof(QVector4D)) {
  m_geometryNode.setGeometry(&m_geometry);
  m_geometryNode.setMaterial(&m_material);
  appendChild(&m_geometryNode);

  m_geometry.setDrawingMode(GL_TRIANGLE_FAN);

  QVector4D* array = m_geometry.vertexData<QVector4D>();
  for (size_t i = 0; i < pts.size(); i++)
    array[i] = QVector4D(pts[i].x(), pts[i].y(), pts[i].x() * scale.x(),
                         pts[i].y() * scale.y());
  m_geometry.updateVertexData();
}

void TexturedConvexPolygon::Node::setTexture(QOpenGLTexture* t) {
  m_material.setTexture(t);
}
