#include "AddRectangle.hpp"
#include "AddBody.hpp"
#include "Graphics/Primitives.hpp"
#include "QBox2D/Fixture/Box2DBox.hpp"

AddRectangle::AddRectangle(AddBody *p)
    : AddFixture(p), m_state(), m_object(this) {}

void AddRectangle::reset() {
  m_state = Reset;

  update();
}

std::unique_ptr<QFixture> AddRectangle::fixture() const {
  auto box = std::make_unique<Box2DBox>();
  box->setPosition(
      QPointF(std::min(m_p1.x(), m_p2.x()), std::min(m_p1.y(), m_p2.y())));

  box->setSize(
      QSizeF(std::abs(m_p1.x() - m_p2.x()), std::abs(m_p1.y() - m_p2.y())));

  box->setTextureSource(":/resources/crate.jpg");

  return box;
}

void AddRectangle::mousePressEvent(QMouseEvent *) {}

void AddRectangle::mouseReleaseEvent(QMouseEvent *event) {
  if (!(m_state & SetFirst)) {
    m_p1 = mapFromScreen(event->pos());
    m_state |= SetFirst;
  } else if (!(m_state & SetSecond)) {
    m_p2 = mapFromScreen(event->pos());
    m_state |= SetSecond;
    finished();
  }
}

void AddRectangle::mouseMoveEvent(QMouseEvent *event) {
  if ((m_state & SetFirst) && !(m_state & SetSecond)) {
    m_cursor = mapFromScreen(event->pos());
    m_state |= MovedCursor;

    update();
  }
}

std::unique_ptr<SceneGraph::Node> AddRectangle::synchronize(
    std::unique_ptr<SceneGraph::Node> node) {
  if (m_state & Reset) {
    m_state ^= Reset;
    node = nullptr;
  }

  if (m_state & MovedCursor) {
    m_state ^= MovedCursor;
    QMatrix4x4 matrix;
    matrix.translate(m_p1.x(), m_p1.y());
    matrix.scale(m_cursor.x() - m_p1.x(), m_cursor.y() - m_p1.y());

    if (!node) node = std::make_unique<Rectangle>();
    static_cast<Rectangle *>(node.get())->setMatrix(matrix);
  }

  return node;
}

AddRectangle::Rectangle::Rectangle()
    : m_geometryNode(
          {QPointF(0, 0), QPointF(0, 1), QPointF(1, 1), QPointF(1, 0)}) {
  appendChild(&m_geometryNode);
  m_geometryNode.setColor(Qt::red);
}

AddRectangle::Rectangle::~Rectangle() {}
