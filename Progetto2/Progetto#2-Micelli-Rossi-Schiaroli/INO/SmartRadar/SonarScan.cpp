#include "SonarScan.h"
#include <Arduino.h>
#include "ServoMove.h"

extern ServoMove *servoTask;

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

    /* Notify Console */
    if(lastDetected < 1.50){
      /*
      Serial.print("Object detected at ");
      Serial.print(servoTask->getPos());
      Serial.print(" ");
      Serial.print(lastDetected);
      Serial.println("m far"); 
      */
    }
}

float SonarScan::getLastDetected(){
  return lastDetected;
}