#include "AddChain.hpp"
#include <memory>
#include "Graphics/TexturedPolygon.hpp"
#include "MapEditor.hpp"
#include "QBox2D/QChain.hpp"
#include "QBox2D/QWorld.hpp"
#include "Utility/Utility.hpp"

AddChain::AddChain(MapEditor* p) : SubAction(p), m_state(), m_object(this) {}

void AddChain::reset() {
  m_state = 0;
  m_pts.clear();
  update();
}

void AddChain::finished() {
  SubAction::finished();
  auto chain = std::make_unique<QChain>(world());
  chain->setVertices(m_pts);
  chain->texture().setSource(":/resources/rock.png");
  chain->texture().setTextureScale(QVector2D(0.05, 0.05));
  chain->initialize(world());

  m_state |= DirtyState::Finished;
  update();

  world()->itemSet()->addBody(std::move(chain));
}

void AddChain::mousePressEvent(QMouseEvent*) {}

void AddChain::mouseReleaseEvent(QMouseEvent* event) {
  m_pts.push_back(mapFromScreen(event->pos()));
  m_state |= DirtyState::Points;
  update();
}

void AddChain::mouseMoveEvent(QMouseEvent* event) {
  if (m_pts.size() == 0)
    event->ignore();
  m_mousePos = mapFromScreen(event->pos());

  m_state |= DirtyState::MousePos;
  update();
}

void AddChain::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Return) {
    finished();
  }
}

std::unique_ptr<SceneGraph::Node> AddChain::synchronize(
    std::unique_ptr<SceneGraph::Node> n) {
  if (pts().size() == 0) {
    return nullptr;
  }

  if (m_state & DirtyState::Points) {
    n = std::make_unique<Node>(pts());
    m_state ^= DirtyState::Points;
  }

  Node* node = static_cast<Node*>(n.get());
  if (m_state & DirtyState::MousePos) {
    node->setLastPoint(m_mousePos);
    m_state ^= DirtyState::MousePos;
  }

  if (m_state & DirtyState::Finished) {
    n = nullptr;

    m_pts.clear();
    m_state ^= DirtyState::Finished;
  }

  return n;
}

AddChain::Node::Node(std::vector<QPointF> pts)
    : m_geometry({{2, GL_FLOAT}}, pts.size() + 1, sizeof(QVector2D)) {
  setMaterial(&m_material);
  setGeometry(&m_geometry);

  m_geometry.setDrawingMode(GL_LINE_STRIP);
  QVector2D* array = m_geometry.vertexData<QVector2D>();
  for (size_t i = 0; i < pts.size(); i++)
    array[i] = QVector2D(pts[i].x(), pts[i].y());
  array[pts.size()] = array[pts.size() - 1];
  m_geometry.updateVertexData();
}

void AddChain::Node::setLastPoint(QPointF p) {
  QVector2D* array = m_geometry.vertexData<QVector2D>();
  array[m_geometry.vertexCount() - 1] = QVector2D(p.x(), p.y());
  m_geometry.updateVertexData();
}
