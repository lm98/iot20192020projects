#include "AutoMode.h"
#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"
#include "SlowBlink.h"
#include "EventCheck.h"
#include <Arduino.h>

extern ServoMove *servoTask;
extern SonarScan *sonarTask;
extern SlowBlink *ledATask;
extern EventCheck *eventTask;

AutoMode::AutoMode(float dNear, float dFar, int potPin){
    this->dNear = dNear;
    this->dFar = dFar;
    this->potPin = potPin;
}

void AutoMode::init(int period){
    Task::init(period);
    servoTask->setNewPosition(0);
}

void AutoMode::tick(){

    servoTask->setActive(true);
    ledATask->setActive(false);

    /* Read servo speed from console if servo isn't moving */
    if(eventTask->isValueAvailable()&&servoTask->getPos()==0){
        int speedCons = eventTask->getValue();
        if(servoTask->getServoSpeed() != speedCons){
            servoTask->setServoSpeed(speedCons);
        }
    } else if(servoTask->getPos()==0){
    
/* Read servo speed from potentiometer if servo isn't moving */
        int speedPot = map(analogRead(potPin),0,1023,0,500);
        if(servoTask->getServoSpeed() != speedPot){
            servoTask->setServoSpeed(speedPot);
        }

    }

/* Tell the servo to make a double sweep: from 0 to 180 and reverse */
    if(servoTask->getPos()==180){
        servoTask->setNewPosition(0);
    }else if(servoTask->getPos()==0){
        servoTask->setNewPosition(180);
    }

/* Activate sonar every delta movement, otherwise we don't scan. */
    if((((servoTask->getPos())%(servoTask->getDelta()))==0)){
        sonarTask->setActive(true);

        if(sonarTask->getLastDetected() < dFar){
            ledATask->setActive(true);
            Serial.println("a alrm");
            /* TRACKING MODE */
            
            if(sonarTask->getLastDetected() < dNear){
                servoTask->setActive(false);
                Serial.println("a alrm trck");
            }
        } else {
            ledATask->setActive(false);
        }
    } else {
        sonarTask->setActive(false);
    }
}

void AutoMode::shutDown(){
    if(this->isActive()){
        servoTask->restart();
        servoTask->setActive(false);
        sonarTask->setActive(false);
        ledATask->setActive(false);
        this->setActive(false);
    }   
}