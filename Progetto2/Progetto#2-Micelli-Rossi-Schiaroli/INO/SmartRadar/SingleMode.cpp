#include "SingleMode.h"
#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"

extern Scheduler *scheduler;
extern ServoMove *servoTask;
extern SonarScan *sonarTask;

void SingleMode::init(int period){
    Task::init(period);
}

void SingleMode::tick(){
    scheduler->shutDownAllTasks();
}
