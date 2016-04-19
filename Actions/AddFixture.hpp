#ifndef ADDFIXTURE_HPP
#define ADDFIXTURE_HPP
#include <memory>
#include "QBox2D/QFixture.hpp"
#include "SubAction.hpp"

class AddFixture : public SubAction {
 public:
  AddFixture(Action*);
  virtual std::unique_ptr<QFixture> fixture() const = 0;
};

#endif  // ADDFIXTURE_HPP
