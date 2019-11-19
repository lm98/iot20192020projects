#ifndef _SONAR_SCAN_
#define _SONAR_SCAN_

#include "Task.h"
#include "Sonar.h"

  class SonarScan : public Task {
    int triggerPin;
    int echoPin;
    Sonar* sonar;
    
    public:
      float lastDetected;
      SonarScan(int triggerPin, int echoPin);
      void init(int period);
      void tick();
  };

#endif
