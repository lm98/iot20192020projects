#ifndef _SONAR_SCAN_
#define _SONAR_SCAN_

#include "Task.h"

  class SonarScan : public Task {
    int triggerPin;
    int echoPin;
    float lastDetected;

    public:

      SonarScan(int triggerPin, int echoPin);
      void init(int period);
      void tick();
      float getLastDetected();
  };

#endif
