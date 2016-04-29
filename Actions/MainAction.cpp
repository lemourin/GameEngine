#include "MainAction.hpp"
#include <QQmlContext>
#include <memory>
#include "QBox2D/QWorld.hpp"

MainAction::MainAction(QWorld *w, std::unique_ptr<FileActionResolver> resolver,
                       std::unique_ptr<MapEditorCallback> mapEditorCallback)
    : Action(w, w),
      m_mapEditor(this, std::move(mapEditorCallback)),
      m_fileAction(this, std::move(resolver)),
      m_actionObject(this) {}

MainAction::~MainAction() {}

void MainAction::registerUserInterface(QQmlContext *context) {
  SaveMapAction *saveMapAction = fileAction()->saveMapAction();
  LoadMapAction *loadMapAction = fileAction()->loadMapAction();

  AddBody *addBody = mapEditor()->addBody();

  context->setContextProperty("mainAction", object());

  context->setContextProperty("mapEditor", mapEditor()->object());
  context->setContextProperty("fileAction", fileAction()->object());

  context->setContextProperty("saveMap", saveMapAction->object());
  context->setContextProperty("loadMap", loadMapAction->object());

  context->setContextProperty("addBody", addBody->object());
  context->setContextProperty("addPolygon", addBody->addPolygon()->object());
  context->setContextProperty("addRectangle",
                              addBody->addRectangle()->object());
  context->setContextProperty("addCircle", addBody->addCircle()->object());

  context->setContextProperty("grabItem", mapEditor()->grabItem()->object());
  context->setContextProperty("deleteItem",
                              mapEditor()->deleteItem()->object());
  context->setContextProperty("bodyEdit", mapEditor()->bodyEdit()->object());
  context->setContextProperty("addChain", mapEditor()->addChain()->object());
  context->setContextProperty("fixtureEdit",
                              mapEditor()->fixtureEdit()->object());
}

void MainAction::step() {
  mapEditor()->grabItem()->update();
}

void MainAction::subActionEnabledChanged(SubAction *action) {
  Action::subActionEnabledChanged(action);

  if (!action->enabled()) {
    world()->setFocus(true);
  }
}

MainActionObject::MainActionObject(MainAction *action) : ActionObject(action) {}

void MainActionObject::quit() {
  if (action()->currentSubAction())
    action()->currentSubAction()->setEnabled(false);
}
