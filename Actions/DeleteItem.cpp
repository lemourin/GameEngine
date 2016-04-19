#include "DeleteItem.hpp"
#include "MapEditor.hpp"
#include "QBox2D/QBody.hpp"
#include "QBox2D/QWorld.hpp"

DeleteItem::DeleteItem(MapEditor* p) : SubAction(p), m_object(this) {}

void DeleteItem::mouseReleaseEvent(QMouseEvent* event) {
  QBody* body = world()->bodyUnderPoint(mapFromScreen(event->pos()));
  if (body) world()->destroyBody(body);

  event->ignore();
}
