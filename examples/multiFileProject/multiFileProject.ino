/****************************************************************************************************************************
  multiFileProject.ino
  For NRF52 boards using mbed-RTOS such as Nano-33-BLE
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt
  Licensed under MIT license

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one NRF52 timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
  #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "NRF52_MBED_TimerInterrupt.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "NRF52_MBED_ISR_Timer.h"

void setup() 
{
  // put your setup code here, to run once:
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
