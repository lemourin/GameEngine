#include "StaticLight.hpp"
#include <QJsonObject>
#include "LightSystem.hpp"
#include "QBox2D/Fixture/Box2DBox.hpp"
#include "QBox2D/QWorld.hpp"
#include "Utility/DisplayItem.hpp"
#include "Utility/Utility.hpp"

StaticLight::StaticLight(Item *parent)
    : Light(parent), m_dynamicShadows(), m_dynamicLight() {
}

StaticLight::~StaticLight() { destroyBody(); }

void StaticLight::initialize(QWorld *w) {
  auto fixture = std::make_unique<Box2DBox>();
  fixture->setPosition(QPointF(-radius(), -radius()));
  fixture->setSize(QSizeF(2 * radius(), 2 * radius()));
  fixture->setSensor(true);
  fixture->setVisible(false);
  fixture->setShadowCaster(false);
  addFixture(std::move(fixture));

  assert(lightSystem());
  lightSystem()->addLight(this);

  QBody::initialize(w);
}

void StaticLight::destroyBody() {
  if (lightSystem()) lightSystem()->removeLight(this);

  Light::destroyBody();
}

bool StaticLight::read(const QJsonObject &obj) {
  Light::read(obj);
  setDynamicShadows(obj["dynamicShadows"].toBool());

  return true;
}

bool StaticLight::write(QJsonObject &obj) const {
  Light::write(obj);
  obj["dynamicShadows"] = dynamicShadows();

  return true;
}

void StaticLight::synchronize() {
  setTransform(position(), rotation());
  if (dynamicLight()) {
    dynamicLight()->setPosition(position());
  }
}

void StaticLight::visibleChanged() {
  if (lightSystem()) {
    lightSystem()->lightVisibilityChanged(this);
  }
}
