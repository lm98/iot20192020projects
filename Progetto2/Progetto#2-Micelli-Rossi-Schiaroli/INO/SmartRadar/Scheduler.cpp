#include "Scheduler.h"

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
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
