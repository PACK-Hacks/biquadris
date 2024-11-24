#include "subject.h"
#include "observer.h"
#include <vector>

Subject::Subject() {}
Subject::~Subject() {}

// Add new observer
void Subject::attach( Observer* o ) {
    observers.emplace_back(o);
}

// Remove observer
void Subject::detach( Observer* o ) {
    for (auto p = observers.begin(); p != observers.end(); ++p) {
        if (*p == o) {
            observers.erase(p);
            break;
        }
    }
}

// Notify observers
void Subject::notifyObservers() {
    for (auto p: observers) p->notify();
}
