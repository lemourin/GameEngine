#ifndef FIXTUREEDIT_HPP
#define FIXTUREEDIT_HPP

#include "SubAction.hpp"

class FixtureEdit;

class FixtureEditObject : public ActionObject {
 private:
 public:
  FixtureEditObject(FixtureEdit *);
};

class FixtureEdit : public SubAction {
 private:
  FixtureEditObject m_actionObject;

 protected:
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);

 public:
  FixtureEdit(MapEditor *);

  inline QString name() const { return "FixtureEdit"; }
};

#endif  // FIXTUREEDIT_HPP
