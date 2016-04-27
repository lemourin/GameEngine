#ifndef MAINACTION_HPP
#define MAINACTION_HPP
#include "Action.hpp"
#include "FileAction.hpp"
#include "MapEditor.hpp"

class QWorld;

class MainActionObject : public ActionObject {
 private:
  Q_OBJECT

 public:
  MainActionObject(MainAction*);

  Q_INVOKABLE void quit();
};

class MainAction : public Action {
 private:
  MapEditor m_mapEditor;
  FileAction m_fileAction;

  MainActionObject m_actionObject;

 protected:
  void subActionEnabledChanged(SubAction *);

 public:
  MainAction(QWorld *, std::unique_ptr<FileActionResolver>,
             std::unique_ptr<MapEditorCallback> mapEditorCallback);
  ~MainAction();

  inline MapEditor *mapEditor() { return &m_mapEditor; }
  inline FileAction *fileAction() { return &m_fileAction; }

  void registerUserInterface(QQmlContext *);
};

#endif  // MAINACTION_HPP
