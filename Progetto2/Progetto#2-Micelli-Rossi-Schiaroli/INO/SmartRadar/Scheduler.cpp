#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  long period = 1000l*basePeriod;
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
  nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){ 
  Serial.println("prima del while");  
  while (!timerFlag){}
  Serial.println("dopo il while");  
  timerFlag = false;

  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->isActive() && taskList[i]->updateAndCheckTime(basePeriod)){
      taskList[i]->tick();
    }
  }
}

void Scheduler::activateTask(Task* task){
  for(int i = 0; i < nTasks; i++){
    if((taskList[i]==task)&&(!taskList[i]->isActive())){
      task->setActive(true);
      return;
    }
  }
}

void Scheduler::shutDownAllTasks(){
  for(int i = 0; i < nTasks; i++){
    if(taskList[i]->isActive()){
      taskList[i]->setActive(false);
    }
  }
}
