#include "SingleMode.h"
#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"
#include "EventCheck.h"
#include "SleepMode.h"


//extern Scheduler *scheduler;
extern ServoMove *servoTask;
extern SonarScan *sonarTask;
extern EventCheck *eventTask;
extern SleepMode *sleepTask;

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
        int speedCons = eventTask->getValue();
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
        Serial.println("s dtct");
        sleepTask->setSleeping(false);
        
        servoTask->setNewPosition(180);
        servoTask->setActive(true);
    } else if((detected == LOW)&&(servoTask->getPos()==0)){
        sleepTask->setSleeping(true);
        sleepTask->setActive(true);
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