#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
#include "subject.h"
#include "observer.h"

class Observer {
 public:
  virtual void notify(int id=0, std::string message="") = 0;
  virtual ~Observer() = default;
};

#endif
