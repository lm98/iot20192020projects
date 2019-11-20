#include "ManualMode.h"
#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"

extern Scheduler *scheduler;
extern ServoMove *servoTask;
extern SonarScan *sonarTask;

void ManualMode::init(int period){
    Task::init(period);
}

void ManualMode::tick(){
    scheduler->shutDownAllTasks();
    servoTask->setActive(true);
    sonarTask->setActive(true);
}
