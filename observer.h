#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "subject.h"
#include "observer.h"

class Observer {
 public:
  virtual void notify(int id = 0) = 0;
  virtual ~Observer() = default;
};

#endif
