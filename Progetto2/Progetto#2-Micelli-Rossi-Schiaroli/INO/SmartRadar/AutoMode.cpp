#include "AutoMode.h"
#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"
#include "SlowBlink.h"

extern ServoMove *servoTask;
extern SonarScan *sonarTask;
extern SlowBlink *ledTask;

AutoMode::AutoMode(float dNear, float dFar){
    this->dNear = dNear;
    this->dFar = dFar;
}

void AutoMode::init(int period){
    Task::init(period);
    servoTask->setNewPosition(0);
}

void AutoMode::tick(){

    servoTask->setActive(true);

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
            ledTask->setActive(true);
        } else {
            ledTask->setActive(false);
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
        ledTask->setActive(false);
        this->setActive(false);
    }   
}