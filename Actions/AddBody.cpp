#include "AddBody.hpp"
#include "AddCircle.hpp"
#include "AddPolygon.hpp"
#include "Graphics/Primitives.hpp"
#include "MapEditor.hpp"
#include "QBox2D/QBody.hpp"
#include "QBox2D/QFixture.hpp"
#include "QBox2D/QWorld.hpp"
#include <memory>

AddBody::AddBody(MapEditor* p)
    : SubAction(p),
      m_addPolygon(this),
      m_addCircle(this),
      m_addRectangle(this),
      m_currentAction(),
      m_action({addPolygon(), addCircle(), addRectangle()}),
      m_object(this) {}

void AddBody::finished() {
  auto body = std::make_unique<QBody>(world());

  for (auto &f : m_fixtures) body->addFixture(std::move(f));
  body->initialize(world());

  world()->itemSet()->addBody(std::move(body));
  m_fixtures.clear();
}

void AddBody::subActionFinished(SubAction* action) {
  auto fixture = std::move(static_cast<AddFixture*>(action)->fixture());
  if (fixture) {
    fixture->setParent(this);
    m_fixtures.push_back(std::move(fixture));
  }

  action->reset();
}

void AddBody::reset() {
  Action::reset();
  m_fixtures.clear();
}
