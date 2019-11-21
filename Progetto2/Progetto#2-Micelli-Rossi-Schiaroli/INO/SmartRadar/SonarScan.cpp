#include "SonarScan.h"
#include <Arduino.h>

SonarScan::SonarScan(int triggerPin, int echoPin){
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
  lastDetected = 0;
}

void SonarScan::init(int period){
  Task::init(period);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void SonarScan::tick(){
    
    digitalWrite(triggerPin,LOW);
    delayMicroseconds(3);
    digitalWrite(triggerPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(triggerPin,LOW);
       
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    lastDetected = t* (331.45 + 0.62*20);
    if(lastDetected > 1.50){
      Serial.println("Out of range");
    } else {
      Serial.println(lastDetected);
    }
}

float SonarScan::getLastDetected(){
  return lastDetected;
}