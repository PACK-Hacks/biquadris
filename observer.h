#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
#include "subject.h"
#include "observer.h"
#include <utility>
using namespace std;

class Observer {
 public:
 // blind_status: 0 = no blind, 1 = blind on p1, 2 = blind on p2
 // message: message to output 
 // activePlayer: 0 = both players (begging of the game), 1 = p1, 2 = p2 

  virtual void notify(int blind_status = 0, std::string message  = " ", 
    int activePlayer = 0) = 0; 
  
  virtual ~Observer() = default;
};

#endif
