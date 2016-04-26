#include "FixtureEdit.hpp"

#include "Graphics/TexturedPolygon.hpp"
#include "MapEditor.hpp"
#include "QBox2D/Fixture/Fixture.hpp"
#include "QBox2D/QChain.hpp"
#include "QBox2D/QWorld.hpp"

void FixtureEdit::mousePressEvent(QMouseEvent* e) { e->ignore(); }

void FixtureEdit::mouseReleaseEvent(QMouseEvent* e) {
  QPointF p = world()->mapFromScreen(e->pos());
  Fixture* fixture = dynamic_cast<Fixture*>(world()->fixtureUnderPoint(
      p, [](QFixture* f) { return !f->isSensor(); }));

  if (!fixture) {
    QChain* chain = static_cast<QChain*>(world()->visibleBodyUnderPoint(
        p, [](QBody* body) { return dynamic_cast<QChain*>(body) != nullptr; }));

    m_chain = chain;
    m_fixture = nullptr;

    if (chain) {
      m_textureSource = chain->texture().source();
      emit m_actionObject.update();
    }
  } else {
    m_textureSource = fixture->textureSource();
    emit m_actionObject.update();

    m_fixture = fixture;
    m_chain = nullptr;
  }

  emit m_actionObject.fixtureChanged();
}

FixtureEdit::FixtureEdit(MapEditor* parent)
  : SubAction(parent), m_actionObject(this), m_fixture(), m_chain() {}

void FixtureEdit::reset() {
  Action::reset();
  m_chain = nullptr;
  m_fixture = nullptr;
  emit m_actionObject.fixtureChanged();
}

void FixtureEdit::apply() {
  if (m_fixture) {
    m_fixture->setTextureSource(m_textureSource);
  } else if (m_chain) {
    m_chain->texture().setSource(m_textureSource);
  }
}

FixtureEditObject::FixtureEditObject(FixtureEdit* action)
    : ActionObject(action) {}

FixtureEdit* FixtureEditObject::action() const {
  return static_cast<FixtureEdit*>(ActionObject::action());
}

bool FixtureEditObject::fixture() const {
  return action()->m_fixture != nullptr || action()->m_chain != nullptr;
}

QString FixtureEditObject::textureSource() const {
  return action()->m_textureSource;
}

void FixtureEditObject::setTextureSource(QString str) {
  action()->m_textureSource = str;
  emit update();
}

void FixtureEditObject::apply() { action()->apply(); }
