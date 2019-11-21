#include "SonarImpl.h"
#include <Arduino.h>

SonarImpl::SonarImpl(int triggerPin, int echoPin){
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
}

void SonarImpl::init(){
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);  
}

float SonarImpl::scan(){
    /* invio impulso */
    digitalWrite(triggerPin,LOW);
    delayMicroseconds(3);
    digitalWrite(triggerPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(triggerPin,LOW);
    
    /* ricevi l’eco */
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    Serial.println(d);
}
