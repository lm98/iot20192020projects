#ifndef __EVENTCHECK__
#define __EVENTCHECK__

#include "Task.h"

#define BUTTON_SINGLE 9
#define BUTTON_MANUAL 10
#define BUTTON_AUTO 11

class EventCheck : public Task {

//Define different state enumeration
enum modality {
  SINGLE,
  MANUAL,
  AUTO
} state;

int value;
bool valueReceived;

public:

  void tick();
  void init(int period);  
  int getValue();
  bool isValueAvailable();
  
};

#endif
