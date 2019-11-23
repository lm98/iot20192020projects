#include "ManualMode.h"
#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"
#include "EventCheck.h"
#include <Arduino.h>

extern ServoMove *servoTask;
extern SonarScan *sonarTask;
extern EventCheck *eventTask;

void ManualMode::init(int period){
    Task::init(period);
}

void ManualMode::tick(){
    
/* Check if there's a value from Serial, if so, move */
    if(eventTask->isValueAvailable()){
        servoTask->setActive(true);
        int val = eventTask->getValue(); //map(eventTask->getValue(),0,180,0,16));
        servoTask->setNewPosition(val);
    } 
   
/* When servo reaches it's destination, sonar starts scanning */
    if(servoTask->getPos() == servoTask->getNewPos()) {
        Serial.println("m");
        sonarTask-> setActive(true);
    } else {
        sonarTask->setActive(false);
    }

}

void ManualMode::shutDown(){
    if(this->isActive()){
        servoTask->restart();
        servoTask->setActive(false);
        sonarTask->setActive(false);
        this->setActive(false);
    }

}