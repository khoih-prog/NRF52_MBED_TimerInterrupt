/****************************************************************************************************************************
  NRF52_MBED_ISR_Timer.hpp
  For NRF52 boards using mbed-RTOS such as Nano-33-BLE
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt
  Licensed under MIT license

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one NRF52 timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Based on SimpleTimer - A timer library for Arduino.
  Author: mromani@ottotecnica.com
  Copyright (c) 2010 OTTOTECNICA Italy

  Based on BlynkTimer.h
  Author: Volodymyr Shymanskyy

  Version: 1.4.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.1   K Hoang      22/11/2020 Initial coding and sync with NRF52_TimerInterrupt
  1.0.2   K Hoang      23/11/2020 Add and optimize examples
  1.1.1   K.Hoang      06/12/2020 Add Change_Interval example. Bump up version to sync with other TimerInterrupt Libraries
  1.2.0   K.Hoang      11/01/2021 Add better debug feature. Optimize code and examples to reduce RAM usage
  1.2.1   K.Hoang      04/05/2021 Add mbed_nano to list of compatible architectures
  1.3.0   K.Hoang      09/09/2021 Don't use NRF_TIMER_1 because of mbed_nano core v2.0.0+
  1.4.0   K.Hoang      22/01/2022 Fix `multiple-definitions` linker error
  1.4.0   K.Hoang      26/10/2022 Add support to SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE using mbed
*****************************************************************************************************************************/

#pragma once

#ifndef ISR_TIMER_GENERIC_HPP
#define ISR_TIMER_GENERIC_HPP

#include "NRF52_MBED_ISR_Timer.hpp"
#include "NRF52_MBED_ISR_Timer-Impl.h"

#endif    // ISR_TIMER_GENERIC_HPP

