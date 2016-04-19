#ifndef ADDBODY_HPP
#define ADDBODY_HPP
#include "AddCircle.hpp"
#include "AddPolygon.hpp"
#include "AddRectangle.hpp"
#include "QBox2D/QBody.hpp"
#include "SubAction.hpp"

class AddBody : public SubAction {
 private:
  friend class AddFixture;

  AddPolygon m_addPolygon;
  AddCircle m_addCircle;
  AddRectangle m_addRectangle;
  AddFixture* m_currentAction;
  std::vector<std::unique_ptr<QFixture>> m_fixtures;
  std::vector<Action*> m_action;

  ActionObject m_object;

  void subActionFinished(SubAction*);

 public:
  explicit AddBody(MapEditor*);

  void reset();
  void finished();

  inline AddPolygon* addPolygon() { return &m_addPolygon; }
  inline AddCircle* addCircle() { return &m_addCircle; }
  inline AddRectangle* addRectangle() { return &m_addRectangle; }
  inline AddFixture* currentAction() const { return m_currentAction; }

  inline QString name() const { return "AddBody"; }
};

#endif  // ADDBODY_HPP
