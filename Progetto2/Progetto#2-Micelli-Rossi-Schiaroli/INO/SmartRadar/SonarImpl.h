#ifndef _SONAR_IMPL_
#define _SONAR_IMPL_

#include "Sonar.h"

class SonarImpl : public Sonar {

  const float vs = 331.45 + 0.62*20;
  int triggerPin;
  int echoPin;

  public:
    SonarImpl(int triggerPin, int echoPin);
    void init();
    float scan(); //ping and return the distance from the object
};

#endif
