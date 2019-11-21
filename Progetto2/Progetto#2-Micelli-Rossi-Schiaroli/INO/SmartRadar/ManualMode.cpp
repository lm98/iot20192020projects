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
    /*
    if(eventTask->isValueAvailable()){
        servoTask->setActive(true);
        int val = eventTask->getValue(); //map(eventTask->getValue(),0,180,0,16));
        servoTask->setNewPosition(val);
    }
    */
   /*
        int val = eventTask->getValue(); //map(eventTask->getValue(),0,180,0,16));
        servoTask->setNewPosition(val);
        servoTask->setActive(true);
        //*/
        sonarTask->setActive(true);
}

void ManualMode::shutDown(){
    //servoTask->setActive(false);
    sonarTask->setActive(false);
    this->setActive(false);
}