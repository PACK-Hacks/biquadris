#ifndef __SUBJECT__
#define __SUBJECT__
#include "vector"
#include "observer.h"


class Subject {
  std::vector<Observer*> observers;

 public:
  Subject();
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  virtual ~Subject()=0;
};

#endif
