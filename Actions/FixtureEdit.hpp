#ifndef FIXTUREEDIT_HPP
#define FIXTUREEDIT_HPP

#include "SubAction.hpp"

class FixtureEdit;
class Fixture;
class QChain;

class FixtureEditObject : public ActionObject {
 private:
  Q_OBJECT
  Q_PROPERTY(bool fixture READ fixture NOTIFY fixtureChanged)
  Q_PROPERTY(QString textureSource READ textureSource WRITE setTextureSource
                 NOTIFY update)
 public:
  FixtureEditObject(FixtureEdit *);

  FixtureEdit *action() const;

  bool fixture() const;

  QString textureSource() const;
  void setTextureSource(QString);

  Q_INVOKABLE void apply();

 signals:
  void fixtureChanged();
  void update();
};

// TODO: Add onFixtureDestroyed so that action knows when edited fixture is
// destroyed.
class FixtureEdit : public SubAction {
 private:
  friend class FixtureEditObject;

  FixtureEditObject m_actionObject;
  QString m_textureSource;
  Fixture *m_fixture;
  QChain *m_chain;

 protected:
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);

 public:
  FixtureEdit(MapEditor *);
  void reset();

  inline QString name() const { return "FixtureEdit"; }

  void apply();
};

#endif  // FIXTUREEDIT_HPP
