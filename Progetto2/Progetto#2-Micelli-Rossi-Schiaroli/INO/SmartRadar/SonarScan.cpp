#include "SonarScan.h"
#include "SonarImpl.h"

SonarScan::SonarScan(int triggerPin, int echoPin){
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
  this->lastDetected = 0;
}

void SonarScan::init(int period){
  Task::init(period);
  Sonar* sonar = new SonarImpl(triggerPin, echoPin);
}

void SonarScan::tick(){
  this->lastDetected = sonar->scan();
}

float SonarScan::getDistance(){
  return this->lastDetected;
}
