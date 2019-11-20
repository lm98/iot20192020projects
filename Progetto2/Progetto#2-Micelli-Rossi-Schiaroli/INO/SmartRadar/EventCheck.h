#ifndef __EVENTCHECK__
#define __EVENTCHECK__

#include "Task.h"

#define BUTTON_SINGLE 3
#define BUTTON_MANUAL 4
#define BUTTON_AUTO 5

class EventCheck : public Task{

//Define different state enumeration
enum modality {
  SINGLE,
  MANUAL,
  AUTO
} state;

int value;

public:

  void tick();
  void init(int period);  
  int getValue();
  
};

#endif
