#include "FixtureEdit.hpp"

#include "MapEditor.hpp"
#include "QBox2D/QWorld.hpp"
#include "QBox2D/Fixture/Fixture.hpp"

void FixtureEdit::mousePressEvent(QMouseEvent* e) {
  e->ignore();
}

void FixtureEdit::mouseReleaseEvent(QMouseEvent* e) {
  auto fixtureSet = world()->fixturesUnderPoint(world()->mapFromScreen(e->pos()));
  if (fixtureSet.empty()) {
    e->ignore();
    return;
  }
  Fixture* fixture = static_cast<Fixture*>(fixtureSet.front());
  qDebug() << fixture->textureSource();
}

FixtureEdit::FixtureEdit(MapEditor* parent)
    : SubAction(parent), m_actionObject(this) {}

FixtureEditObject::FixtureEditObject(FixtureEdit* action)
    : ActionObject(action) {}
