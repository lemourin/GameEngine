#include "AddPolygon.hpp"
#include "AddBody.hpp"
#include "Geometry/Functions.hpp"
#include "Graphics/Primitives.hpp"
#include "QBox2D/Fixture/Box2DPolygon.hpp"
#include "QBox2D/QWorld.hpp"

AddPolygon::AddPolygon(AddBody* parent) : AddFixture(parent), m_object(this) {}

void AddPolygon::reset() {
  m_pts.clear();
  update();
}

std::unique_ptr<QFixture> AddPolygon::fixture() const {
  if (m_pts.size() < 3) return nullptr;
  auto polygon = std::make_unique<Box2DPolygon>();
  polygon->setVertices(m_pts);

  return polygon;
}

void AddPolygon::mousePressEvent(QMouseEvent*) {}

void AddPolygon::mouseReleaseEvent(QMouseEvent* event) {
  m_pts.push_back(mapFromScreen(event->pos()));

  if (m_pts.size() >= 3) {
    std::vector<Vector2d> vec;
    for (QPointF p : m_pts) vec.push_back(Vector2d(p));

    Geometry::convexHull(vec);

    m_pts.clear();
    for (Vector2d p : vec) m_pts.push_back(QPointF(p));
  }

  update();
}

std::unique_ptr<SceneGraph::Node> AddPolygon::synchronize(
    std::unique_ptr<SceneGraph::Node>) {
  if (m_pts.size() < 3) {
    return std::make_unique<Node>(m_pts, QSizeF(1, 1));
  }

  auto node = std::make_unique<ConvexPolygonNode>(m_pts);
  node->setColor(Qt::yellow);

  return node;
}

AddPolygon::Node::Node(std::vector<QPointF> pts, QSizeF size) {
  qreal w = size.width(), h = size.height();
  for (QPointF p : pts) {
    std::vector<QPointF> vertex = {QPointF(-0.5 * w + p.x(), -0.5 * h + p.y()),
                                   QPointF(0.5 * w + p.x(), -0.5 * h + p.y()),
                                   QPointF(0.5 * w + p.x(), 0.5 * h + p.y()),
                                   QPointF(-0.5 * w + p.x(), 0.5 * h + p.y())};

    auto node = std::make_unique<ConvexPolygonNode>(vertex);
    appendChild(node.get());

    m_node.push_back(std::move(node));
  }
}

AddPolygon::Node::~Node() {}
