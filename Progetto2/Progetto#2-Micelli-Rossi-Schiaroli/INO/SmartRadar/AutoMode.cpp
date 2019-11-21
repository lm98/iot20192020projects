#include "AutoMode.h"
#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"

extern ServoMove *servoTask;
extern SonarScan *sonarTask;

void AutoMode::init(int period){
    Task::init(period);
    servoTask->setNewPosition(0);
}

void AutoMode::tick(){
    servoTask -> setActive(true);
    if(servoTask->pos>170){
        servoTask->setNewPosition(0);
    }else if(servoTask->pos<10){
        servoTask->setNewPosition(180);
    }
    sonarTask -> setActive(true);
}

void AutoMode::shutDown(){
    servoTask->setActive(false);
    sonarTask->setActive(false);
    this->setActive(false);
}