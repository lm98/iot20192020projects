#include "SingleMode.h"
#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"
#include "EventCheck.h"

//extern Scheduler *scheduler;
extern ServoMove *servoTask;
extern SonarScan *sonarTask;
extern EventCheck *eventTask;

SingleMode::SingleMode(int pirPin, int potPin){
    this->pirPin = pirPin;
    this->potPin = potPin;
}

void SingleMode::init(int period){
    Task::init(period);
    pinMode(pirPin,INPUT);
    pinMode(potPin,INPUT);
    servoTask->setNewPosition(0);
}

void SingleMode::tick(){


/* Read servo speed from console  */
    if(eventTask->isValueAvailable()){
        servoTask->setActive(true);
        int speedCons = eventTask->getValue(); //map(eventTask->getValue(),0,180,0,16));
        if(servoTask->getServoSpeed() != speedCons){
            servoTask->setServoSpeed(speedCons);
        }
    } else {
    
/* Read servo speed from potentiometer */
        int speedPot = map(analogRead(potPin),0,1023,0,500);
        if(servoTask->getServoSpeed() != speedPot){
            servoTask->setServoSpeed(speedPot);
        }

    }

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