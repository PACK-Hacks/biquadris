#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
#include "subject.h"
#include "observer.h"

class Observer {
 public:
  virtual void notify(std::string message="", int id=0) = 0;
  virtual ~Observer() = default;
};

#endif
