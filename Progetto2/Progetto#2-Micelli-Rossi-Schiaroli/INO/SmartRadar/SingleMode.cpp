#include "SingleMode.h"
#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"

//extern Scheduler *scheduler;
extern ServoMove *servoTask;
extern SonarScan *sonarTask;


SingleMode::SingleMode(int pirPin){
    this->pirPin = pirPin;
}

void SingleMode::init(int period){
    Task::init(period);
    pinMode(pirPin,INPUT);
    servoTask->setNewPosition(0);
}

void SingleMode::tick(){

/* When pir detects a movement, servo makes a complete sweep */
    int detected = digitalRead(pirPin);
    if ((detected == HIGH)&&(servoTask->getPos()==0)){
        servoTask->setNewPosition(180);
        servoTask->setActive(true);
    } 

/* When servo makes a full sweep, return immediately in position 0 */
    if(servoTask->getPos()==180){
        servoTask->restart();
        servoTask->setActive(true);
        sonarTask->setActive(false);
    } 

/* Activate sonar every delta movement, otherwise we don't scan. */
    if((((servoTask->getPos())%(servoTask->getDelta()))==0) && (servoTask->getNewPos() != 0)){
        sonarTask->setActive(true);
    } else {
        sonarTask->setActive(false);
    }
}

void SingleMode::shutDown(){
    if(this->isActive()){
        servoTask->restart();
        servoTask->setActive(false);
        sonarTask->setActive(false);
        this->setActive(false);
    }
}