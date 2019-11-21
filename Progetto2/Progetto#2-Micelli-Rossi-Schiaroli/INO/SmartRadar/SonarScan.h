#ifndef _SONAR_SCAN_
#define _SONAR_SCAN_

#include "Task.h"

  class SonarScan : public Task {
    int triggerPin;
    int echoPin;
    
    public:
      float lastDetected;
      SonarScan(int triggerPin, int echoPin);
      void init(int period);
      void tick();
      float getDistance();
  };

#endif
