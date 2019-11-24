#include "SleepMode.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <Arduino.h>

void SleepMode::init(int period){
    Task::init(period);
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    power_adc_disable();
    power_spi_disable();
    power_timer0_disable();
    power_timer2_disable();
    power_twi_disable(); 
    
}

void SleepMode::tick(){
    if(sleeping){
        //Serial.println("sleeping");
        sleep_mode();  
    } else {
        //Serial.println("woke up");
        sleep_disable();
        power_all_enable();
        this->setActive(false);
    }
}

bool SleepMode::isSleeping(){
    return this->sleeping;
}

void SleepMode::setSleeping(bool sleep){
    this->sleeping = sleep;
}