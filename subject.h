#ifndef __SUBJECT__
#define __SUBJECT__
#include "vector"

class Observer; // forward declaration

class Subject {
  std::vector<Observer*> observers;

 public:
  Subject();
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  virtual char getState( int row, int col ) const = 0;
  virtual ~Subject()=0;
};

#endif
