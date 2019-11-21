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
    int detected = digitalRead(pirPin);
    if (detected == HIGH){
        servoTask->setNewPosition(180);
        servoTask->setActive(true);
       // sonarTask->setActive(true);
    } 

  //  sonarTask->setActive(false);

    if(servoTask->pos>170){
        servoTask->setNewPosition(0);
        servoTask->setActive(true);
        sonarTask->setActive(false);
    } 

    if((((servoTask->pos)%(servoTask->delta))==0) && (servoTask->newPos != 0)){
        sonarTask->setActive(true);
    } else {
        sonarTask->setActive(false);
    }
}

void SingleMode::shutDown(){
    servoTask->setActive(false);
    sonarTask->setActive(false);
    this->setActive(false);
}