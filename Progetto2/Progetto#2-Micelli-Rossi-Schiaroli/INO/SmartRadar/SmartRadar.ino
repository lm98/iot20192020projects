#include "Scheduler.h"
#include "SlowBlink.h"


#define RX 0
#define TX 1

Scheduler scheduler;

void setup() {
  Serial.begin(9600);
  scheduler.init(100);

  Task* t0 = new SlowBlink(13);
  t0->init(100);
  scheduler.addTask(t0);
}

void loop() {
  if (Serial.available() > 0){
    scheduler.schedule();  
  }
	
}
