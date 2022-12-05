# NRF52_MBED_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/NRF52_MBED_TimerInterrupt.svg?)](https://www.ardu-badge.com/NRF52_MBED_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/NRF52_MBED_TimerInterrupt.svg)](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/NRF52_MBED_TimerInterrupt.svg)](http://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Important Change from v1.4.0](#Important-Change-from-v140)
* [Why do we need this NRF52_MBED_TimerInterrupt library](#why-do-we-need-this-nrf52_mbed_timerinterrupt-library)
  * [Features](#features)
  * [Why using ISR-based Hardware Timer Interrupt is better](#why-using-isr-based-hardware-timer-interrupt-is-better)
  * [Important notes about NRF_TIMER_1](#important-notes-about-nrf_timer_1)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Changelog](changelog.md) 
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [New from v1.0.1](#new-from-v101)
* [Usage](#usage)
  * [1. Using only Hardware Timer directly](#1-using-only-hardware-timer-directly)
    * [1.1 Init Hardware Timer](#11-init-hardware-timer)
    * [1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function](#12-set-hardware-timer-interval-and-attach-timer-interrupt-handler-function)
    * [1.3 Set Hardware Timer Frequency and attach Timer Interrupt Handler function](#13-set-hardware-timer-frequency-and-attach-timer-interrupt-handler-function)
  * [2. Using 16 ISR_based Timers from 1 Hardware Timer](#2-using-16-isr_based-timers-from-1-hardware-timer)
    * [2.1 Important Note](#21-important-note)
    * [2.2 Init Hardware Timer and ISR-based Timer](#22-init-hardware-timer-and-isr-based-timer)
    * [2.3 Set Hardware Timer Interval and attach Timer Interrupt Handler functions](#23-set-hardware-timer-interval-and-attach-timer-interrupt-handler-functions)
* [Examples](#examples)
  * [  1. Argument_None](examples/Argument_None)
  * [  2. ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
  * [  3. ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)
  * [  4. SwitchDebounce](examples/SwitchDebounce)
  * [  5. TimerInterruptTest](examples/TimerInterruptTest)
  * [  6. TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)
  * [  7. **FakeAnalogWrite**](examples/FakeAnalogWrite)
  * [  8. **Change_Interval**](examples/Change_Interval)
  * [  9. **multiFileProject**](examples/multiFileProject) **New**
* [Example ISR_16_Timers_Array_Complex](#example-isr_16_timers_array_complex)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ISR_16_Timers_Array_Complex on Arduino Nano_33_BLE](#1-isr_16_timers_array_complex-on-arduino-nano_33_ble)
  * [2. TimerInterruptTest on Arduino Nano_33_BLE](#2-timerinterrupttest-on-arduino-nano_33_ble)
  * [3. Argument_None on Arduino Nano_33_BLE](#3-argument_none-on-arduino-nano_33_ble)
  * [4. FakeAnalogWrite on Arduino Nano_33_BLE](#4-fakeanalogwrite-on-arduino-nano_33_ble)
  * [5. Change_Interval on Arduino Nano_33_BLE](#5-change_interval-on-arduino-nano_33_ble)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Change from v1.4.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

### Why do we need this [NRF52_MBED_TimerInterrupt library](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt)

### Features

This library enables you to use Interrupt from Hardware Timers on an NRF52-based board using mbed-RTOS such as Nano-33-BLE.

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **16 ISR-based Timers, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

Now with these new **16 ISR-based timers**, the maximum interval is **practically unlimited** (limited only by unsigned long milliseconds) while **the accuracy is nearly perfect** compared to software timers. 

The most important feature is they're ISR-based timers. Therefore, their executions are **not blocked by bad-behaving functions / tasks**. This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_Timer_Complex**](examples/ISR_Timer_Complex) example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.

Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

### Why using ISR-based Hardware Timer Interrupt is better

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware timers, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)


### Important notes about NRF_TIMER_1

- Starting from core `mbed_nano` core v2.0.0+, `NRF_TIMER_1` stops working. 

```cpp
// For core mbed core 1.3.2-
// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1,NRF_TIMER_3,NRF_TIMER_4 (1,3 and 4)
// If you select the already-used NRF_TIMER_0 or NRF_TIMER_2, it'll be auto modified to use NRF_TIMER_1

// For core mbed core 2.0.0-
// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_3,NRF_TIMER_4 (3 and 4)
// If you select the already-used NRF_TIMER_0, NRF_TIMER_1 or NRF_TIMER_2, it'll be auto modified to use NRF_TIMER_3
```

---

### Currently supported Boards

1. **MBED nRF52840-based boards such as Nano_33_BLE, Nano_33_BLE_Sense**, etc. using [**Arduino-mbed mbed_nano** core](https://github.com/arduino/ArduinoCore-mbed)
2. **Seeeduino nRF52840-based boards such as SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE**, etc. using Seeeduino `mbed` core

---

### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

---

### Notes for recent 2.0.0 release of Arduino Mbed OS Boards platform

From [Add mbed_nano to list of compatible architectures #3](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/pull/3)

```cpp
In the recent 2.0.0 release of the Arduino Mbed OS Boards platform, the mbed architecture split into four architectures:

mbed_edge: Arduino Edge Control
mbed_nano: Nano 33 BLE and Nano RP2040 Connect
mbed_rp2040: Raspberry Pi Pico
mbed_portenta: Portenta H7

The mbed architecture should be retained for backwards support, but the new mbed_nano should also be added to avoid spurious incompatibility warnings and the library's examples being shown under the File > Examples > INCOMPATIBLE menu of the Arduino IDE when the Nano 33 BLE board is selected.
```

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino mbed_nano core 3.4.1+`](https://github.com/arduino/ArduinoCore-mbed) for NRF52-based board using mbed-RTOS such as Nano-33-BLE if you don't use `NRF_TIMER_1`. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
 3. [`Arduino mbed core v1.3.2-`](https://github.com/arduino/ArduinoCore-mbed/releases/tag/1.3.2) for NRF52-based board using mbed-RTOS such as Nano-33-BLE if you'd like to use `NRF_TIMER_1`. Latest is [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
 4. `Seeeduino mbed core 2.7.2+` for Seeeduino nRF52840-based boards such as **SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE**
 
 5. To use with certain example
   - [`SimpleTimer library`](https://github.com/jfturcot/SimpleTimer) for [ISR_16_PWMs_Array_Complex example](examples/ISR_16_PWMs_Array_Complex)
   
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**NRF52_MBED_TimerInterrupt**](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/NRF52_MBED_TimerInterrupt.svg?)](https://www.ardu-badge.com/NRF52_MBED_TimerInterrupt) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**NRF52_MBED_TimerInterrupt**](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt) page.
2. Download the latest release `NRF52_MBED_TimerInterrupt-main.zip`.
3. Extract the zip file to `NRF52_MBED_TimerInterrupt-main` directory 
4. Copy whole `NRF52_MBED_TimerInterrupt-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**NRF52_MBED_TimerInterrupt** library](https://registry.platformio.org/libraries/khoih-prog/NRF52_MBED_TimerInterrupt) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/NRF52_MBED_TimerInterrupt/installation). Search for **NRF52_MBED_TimerInterrupt** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Libraries' Patches

#### Notes: These patches are totally optional and necessary only when you use the related Ethernet library and get certain error or issues.

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- For [UIPEthernet v2.0.8](https://github.com/UIPEthernet/UIPEthernet)

  - [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
  - [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
  - [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
  - [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

- For [UIPEthernet v2.0.9](https://github.com/UIPEthernet/UIPEthernet)

  - [UIPEthernet.h](LibraryPatches/UIPEthernet-2.0.9/UIPEthernet.h)
  - [UIPEthernet.cpp](LibraryPatches/UIPEthernet-2.0.9/UIPEthernet.cpp)
  - [Enc28J60Network.h](LibraryPatches/UIPEthernet-2.0.9/utility/Enc28J60Network.h)
  - [Enc28J60Network.cpp](LibraryPatches/UIPEthernet-2.0.9/utility/Enc28J60Network.cpp)


---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include these `.hpp` files

```cpp
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "NRF52_MBED_TimerInterrupt.hpp"   //https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "NRF52_MBED_ISR_Timer.hpp"        //https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt
```

in many files. But be sure to use the following `.h` files **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "NRF52_MBED_TimerInterrupt.h"     //https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "NRF52_MBED_ISR_Timer.h"          //https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

---
---


## New from v1.0.1

Now with these new `16 ISR-based timers` (while consuming only **1 hardware timer**), the maximum interval is practically unlimited (limited only by unsigned long milliseconds). The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers Therefore, their executions are not blocked by bad-behaving functions / tasks.
This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_16_Timers_Array**](examples/ISR_16_Timers_Array) example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.
Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.
This non-being-blocked important feature is absolutely necessary for mission-critical tasks. 
You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in `loop()`, using `delay()` function as an example. The elapsed time then is very unaccurate

---
---

## Usage

Before using any Timer, you have to make sure the Timer has not been used by any other purpose.

### 1. Using only Hardware Timer directly

#### 1.1 Init Hardware Timer

```cpp
// For core mbed core 1.3.2-
// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1,NRF_TIMER_3,NRF_TIMER_4 (1,3 and 4)
// If you select the already-used NRF_TIMER_0 or NRF_TIMER_2, it'll be auto modified to use NRF_TIMER_1

// For core mbed core 2.0.0-
// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_3,NRF_TIMER_4 (3 and 4)
// If you select the already-used NRF_TIMER_0, NRF_TIMER_1 or NRF_TIMER_2, it'll be auto modified to use NRF_TIMER_3

// Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);
```

#### 1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function

Use one of these functions with **interval in unsigned long milliseconds**

```cpp
// interval (in microseconds).
// No params and duration now. To be added in the future by adding similar functions here or to NRF52-hal-timer.c
bool setInterval(unsigned long interval, timerCallback callback);

// interval (in microseconds).
// No params and duration now. To be added in the future by adding similar functions here or to NRF52-hal-timer.c
bool attachInterruptInterval(unsigned long interval, timerCallback callback);
```

as follows

```cpp
void TimerHandler(void)
{
  // Doing something here inside ISR
  // No Serial.print() can be used
}

#define TIMER_INTERVAL_MS        1000      // 1s = 1000ms
void setup()
{
  ....
  
  // Interval in microsecs
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler0))
  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer0. Select another freq. or timer));
}  
```

### 1.3 Set Hardware Timer Frequency and attach Timer Interrupt Handler function

Use one of these functions with **frequency in float Hz**

```cpp
// frequency (in hertz).
// No params and duration now. To be added in the future by adding similar functions here or to NRF52-hal-timer.c
bool setFrequency(float frequency, timerCallback callback);

// frequency (in hertz).
bool attachInterrupt(float frequency, timerCallback callback);
```

as follows

```cpp
void TimerHandler0()
{
  // Doing something here inside ISR
  // No Serial.print() can be used
}

#define TIMER0_FREQ_HZ        5555.555

void setup()
{
  ....
  
  // Frequency in float Hz
  if (ITimer0.attachInterrupt(TIMER0_FREQ_HZ, TimerHandler0))
  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer0. Select another freq. or timer));
}  
```

### 2. Using 16 ISR_based Timers from 1 Hardware Timer

### 2.1 Important Note

The 16 ISR_based Timers, designed for long timer intervals, only support using **unsigned long millisec intervals**. If you have to use much higher frequency or sub-millisecond interval, you have to use the Hardware Timers directly as in [1.3 Set Hardware Timer Frequency and attach Timer Interrupt Handler function](#13-set-hardware-timer-frequency-and-attach-timer-interrupt-handler-function)

### 2.2 Init Hardware Timer and ISR-based Timer

```cpp
// For core mbed core 1.3.2-
// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1,NRF_TIMER_3,NRF_TIMER_4 (1,3 and 4)
// If you select the already-used NRF_TIMER_0 or NRF_TIMER_2, it'll be auto modified to use NRF_TIMER_1

// For core mbed core 2.0.0-
// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_3,NRF_TIMER_4 (3 and 4)
// If you select the already-used NRF_TIMER_0, NRF_TIMER_1 or NRF_TIMER_2, it'll be auto modified to use NRF_TIMER_3

// Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);

// Init NRF52_MBED_ISRTimer
// Each NRF52_MBED_ISRTimer can service 16 different ISR-based timers
NRF52_MBED_ISRTimer ISR_Timer;
```

### 2.3 Set Hardware Timer Interval and attach Timer Interrupt Handler functions

```cpp
void TimerHandler(void)
{
  ISR_Timer.run();
}

#define HW_TIMER_INTERVAL_MS          50L

#define TIMER_INTERVAL_2S             2000L
#define TIMER_INTERVAL_5S             5000L
#define TIMER_INTERVAL_11S            11000L
#define TIMER_INTERVAL_101S           101000L

// In NRF52, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething2s()
{
  // Doing something here inside ISR
}
  
void doingSomething5s()
{
  // Doing something here inside ISR
}

void doingSomething11s()
{
  // Doing something here inside ISR
}

void doingSomething101s()
{
  // Doing something here inside ISR
}

void setup()
{
  ....
  
  // Interval in microsecs
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    lastMillis = millis();
    Serial.printf("Starting  ITimer OK, millis() = %ld\n", lastMillis);
  }
  else
    Serial.println("Can't set ITimer correctly. Select another freq. or interval");

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  ISR_Timer.setInterval(TIMER_INTERVAL_2S, doingSomething2s);
  ISR_Timer.setInterval(TIMER_INTERVAL_5S, doingSomething5s);
  ISR_Timer.setInterval(TIMER_INTERVAL_11S, doingSomething11s);
  ISR_Timer.setInterval(TIMER_INTERVAL_101S, doingSomething101s);
}  
```

---
---

### Examples: 

 1. [Argument_None](examples/Argument_None)
 2. [ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
 3. [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)
 4. [SwitchDebounce](examples/SwitchDebounce)
 5. [TimerInterruptTest](examples/TimerInterruptTest)
 6. [TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)
 7. [FakeAnalogWrite](examples/FakeAnalogWrite)
 8. [**Change_Interval**](examples/Change_Interval)
 9. [**multiFileProject**](examples/multiFileProject) **New**
 
---
---

### Example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)

https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/blob/c302b0dc80d6e827ee7cd0513aa56df2d0adfa4f/examples/ISR_16_Timers_Array_Complex/ISR_16_Timers_Array_Complex.ino#L35-L387

---
---

### Debug Terminal Output Samples

### 1. ISR_16_Timers_Array_Complex on Arduino Nano_33_BLE

The following is the sample terminal output when running example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex) on **Arduino Nano_33_BLE** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy**.  The ISR timer is **programmed for 2s, is activated exactly after 2.000s !!!**

While software timer, **programmed for 2s, is activated after more than 3.000s in loop().

```
Starting ISR_16_Timers_Array_Complex on Nano 33 BLE
NRF52_MBED_TimerInterrupt v1.4.1
[TISR] Timer = NRF_TIMER3, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 100.00, _count = 10000
Starting  ITimer OK, millis() = 714
simpleTimer2s, ms=3714, Dms=3000
Timer : 0, programmed : 5000, actual : 0
Timer : 1, programmed : 10000, actual : 0
Timer : 2, programmed : 15000, actual : 0
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=6730, Dms=3016
Timer : 0, programmed : 5000, actual : 5004
Timer : 1, programmed : 10000, actual : 0
Timer : 2, programmed : 15000, actual : 0
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=9746, Dms=3016
Timer : 0, programmed : 5000, actual : 5004
Timer : 1, programmed : 10000, actual : 0
Timer : 2, programmed : 15000, actual : 0
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=12762, Dms=3016
Timer : 0, programmed : 5000, actual : 5004
Timer : 1, programmed : 10000, actual : 10008
Timer : 2, programmed : 15000, actual : 0
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=15778, Dms=3016
Timer : 0, programmed : 5000, actual : 4994
Timer : 1, programmed : 10000, actual : 10008
Timer : 2, programmed : 15000, actual : 15002
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=18794, Dms=3016
Timer : 0, programmed : 5000, actual : 4994
Timer : 1, programmed : 10000, actual : 10008
Timer : 2, programmed : 15000, actual : 15002
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=21810, Dms=3016
Timer : 0, programmed : 5000, actual : 5002
Timer : 1, programmed : 10000, actual : 9996
Timer : 2, programmed : 15000, actual : 15002
Timer : 3, programmed : 20000, actual : 20004
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=24826, Dms=3016
Timer : 0, programmed : 5000, actual : 5002
Timer : 1, programmed : 10000, actual : 9996
Timer : 2, programmed : 15000, actual : 15002
Timer : 3, programmed : 20000, actual : 20004
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=27842, Dms=3016
Timer : 0, programmed : 5000, actual : 5002
Timer : 1, programmed : 10000, actual : 9996
Timer : 2, programmed : 15000, actual : 15002
Timer : 3, programmed : 20000, actual : 20004
Timer : 4, programmed : 25000, actual : 25006
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=30858, Dms=3016
Timer : 0, programmed : 5000, actual : 5002
Timer : 1, programmed : 10000, actual : 10004
Timer : 2, programmed : 15000, actual : 15006
Timer : 3, programmed : 20000, actual : 20004
Timer : 4, programmed : 25000, actual : 25006
Timer : 5, programmed : 30000, actual : 30008
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=33874, Dms=3016
Timer : 0, programmed : 5000, actual : 5002
Timer : 1, programmed : 10000, actual : 10004
Timer : 2, programmed : 15000, actual : 15006
Timer : 3, programmed : 20000, actual : 20004
Timer : 4, programmed : 25000, actual : 25006
Timer : 5, programmed : 30000, actual : 30008
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=36890, Dms=3016
Timer : 0, programmed : 5000, actual : 4992
Timer : 1, programmed : 10000, actual : 10004
Timer : 2, programmed : 15000, actual : 15006
Timer : 3, programmed : 20000, actual : 20004
Timer : 4, programmed : 25000, actual : 25006
Timer : 5, programmed : 30000, actual : 30008
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=39906, Dms=3016
Timer : 0, programmed : 5000, actual : 4992
Timer : 1, programmed : 10000, actual : 10004
Timer : 2, programmed : 15000, actual : 15006
Timer : 3, programmed : 20000, actual : 20004
Timer : 4, programmed : 25000, actual : 25006
Timer : 5, programmed : 30000, actual : 30008
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=42922, Dms=3016
Timer : 0, programmed : 5000, actual : 5001
Timer : 1, programmed : 10000, actual : 9993
Timer : 2, programmed : 15000, actual : 15006
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 25006
Timer : 5, programmed : 30000, actual : 30008
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=45938, Dms=3016
Timer : 0, programmed : 5000, actual : 5001
Timer : 1, programmed : 10000, actual : 9993
Timer : 2, programmed : 15000, actual : 14994
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 25006
Timer : 5, programmed : 30000, actual : 30008
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=48954, Dms=3016
Timer : 0, programmed : 5000, actual : 5001
Timer : 1, programmed : 10000, actual : 9993
Timer : 2, programmed : 15000, actual : 14994
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 25006
Timer : 5, programmed : 30000, actual : 30008
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=51970, Dms=3016
Timer : 0, programmed : 5000, actual : 5001
Timer : 1, programmed : 10000, actual : 10002
Timer : 2, programmed : 15000, actual : 14994
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 24997
Timer : 5, programmed : 30000, actual : 30008
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=54986, Dms=3016
Timer : 0, programmed : 5000, actual : 5001
Timer : 1, programmed : 10000, actual : 10002
Timer : 2, programmed : 15000, actual : 14994
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 24997
Timer : 5, programmed : 30000, actual : 30008
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=58002, Dms=3016
Timer : 0, programmed : 5000, actual : 5003
Timer : 1, programmed : 10000, actual : 10002
Timer : 2, programmed : 15000, actual : 14994
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 24997
Timer : 5, programmed : 30000, actual : 30008
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=61018, Dms=3016
Timer : 0, programmed : 5000, actual : 5003
Timer : 1, programmed : 10000, actual : 10006
Timer : 2, programmed : 15000, actual : 15007
Timer : 3, programmed : 20000, actual : 20008
Timer : 4, programmed : 25000, actual : 24997
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60009
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=64034, Dms=3016
Timer : 0, programmed : 5000, actual : 5003
Timer : 1, programmed : 10000, actual : 10006
Timer : 2, programmed : 15000, actual : 15007
Timer : 3, programmed : 20000, actual : 20008
Timer : 4, programmed : 25000, actual : 24997
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60009
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=67050, Dms=3016
Timer : 0, programmed : 5000, actual : 4992
Timer : 1, programmed : 10000, actual : 10006
Timer : 2, programmed : 15000, actual : 15007
Timer : 3, programmed : 20000, actual : 20008
Timer : 4, programmed : 25000, actual : 24997
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60009
Timer : 12, programmed : 65000, actual : 65001
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=70066, Dms=3016
Timer : 0, programmed : 5000, actual : 4992
Timer : 1, programmed : 10000, actual : 10006
Timer : 2, programmed : 15000, actual : 15007
Timer : 3, programmed : 20000, actual : 20008
Timer : 4, programmed : 25000, actual : 24997
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60009
Timer : 12, programmed : 65000, actual : 65001
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=73082, Dms=3016
Timer : 0, programmed : 5000, actual : 5003
Timer : 1, programmed : 10000, actual : 9995
Timer : 2, programmed : 15000, actual : 15007
Timer : 3, programmed : 20000, actual : 20008
Timer : 4, programmed : 25000, actual : 24997
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 35004
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60009
Timer : 12, programmed : 65000, actual : 65001
Timer : 13, programmed : 70000, actual : 70004
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=76098, Dms=3016
Timer : 0, programmed : 5000, actual : 5003
Timer : 1, programmed : 10000, actual : 9995
Timer : 2, programmed : 15000, actual : 14998
Timer : 3, programmed : 20000, actual : 20008
Timer : 4, programmed : 25000, actual : 25004
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 35004
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60009
Timer : 12, programmed : 65000, actual : 65001
Timer : 13, programmed : 70000, actual : 70004
Timer : 14, programmed : 75000, actual : 75007
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=79114, Dms=3016
Timer : 0, programmed : 5000, actual : 5003
Timer : 1, programmed : 10000, actual : 9995
Timer : 2, programmed : 15000, actual : 14998
Timer : 3, programmed : 20000, actual : 20008
Timer : 4, programmed : 25000, actual : 25004
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 35004
Timer : 7, programmed : 40000, actual : 40001
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60009
Timer : 12, programmed : 65000, actual : 65001
Timer : 13, programmed : 70000, actual : 70004
Timer : 14, programmed : 75000, actual : 75007
Timer : 15, programmed : 80000, actual : 0
simpleTimer2s, ms=82130, Dms=3016
Timer : 0, programmed : 5000, actual : 5002
Timer : 1, programmed : 10000, actual : 10005
Timer : 2, programmed : 15000, actual : 14998
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25004
Timer : 5, programmed : 30000, actual : 30001
Timer : 6, programmed : 35000, actual : 35004
Timer : 7, programmed : 40000, actual : 40008
Timer : 8, programmed : 45000, actual : 45002
Timer : 9, programmed : 50000, actual : 50003
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60009
Timer : 12, programmed : 65000, actual : 65001
Timer : 13, programmed : 70000, actual : 70004
Timer : 14, programmed : 75000, actual : 75007
Timer : 15, programmed : 80000, actual : 80009

```

---

### 2. TimerInterruptTest on Arduino Nano_33_BLE

The following is the sample terminal output when running example [**TimerInterruptTest**](examples/TimerInterruptTest) on **Arduino Nano_33_BLE** to demonstrate the accuracy and how to start/stop Hardware Timers.

```
Starting TimerInterruptTest on Nano 33 BLE
NRF52_MBED_TimerInterrupt v1.4.1
[TISR] Timer = NRF_TIMER3, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 1.00, _count = 1000000
Starting ITimer0 OK, millis() = 1219
[TISR] Timer = NRF_TIMER4, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 0.33, _count = 3000000
Starting ITimer1 OK, millis() = 1221
Stop ITimer0, millis() = 5001
Start ITimer0, millis() = 10002
Stop ITimer1, millis() = 15001
Stop ITimer0, millis() = 15003
Start ITimer0, millis() = 20004
Stop ITimer0, millis() = 25005
Start ITimer1, millis() = 30002
Start ITimer0, millis() = 30006
Stop ITimer0, millis() = 35007
Start ITimer0, millis() = 40008
Stop ITimer1, millis() = 45003
Stop ITimer0, millis() = 45009

```

---

### 3. Argument_None on Arduino Nano_33_BLE

The following is the sample terminal output when running example [**Argument_None**](examples/Argument_None) on **Arduino Nano_33_BLE** to demonstrate the accuracy of Hardware Timers.

```
Starting Argument_None on Nano 33 BLE
NRF52_MBED_TimerInterrupt v1.4.1
[TISR] Timer = NRF_TIMER4, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 2.00, _count = 500000
Starting ITimer0 OK, millis() = 814
[TISR] Timer = NRF_TIMER3, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 0.50, _count = 2000000
Starting  ITimer1 OK, millis() = 816
Time = 10001, Timer0Count = 18, Timer1Count = 4
Time = 20002, Timer0Count = 38, Timer1Count = 9
Time = 30003, Timer0Count = 58, Timer1Count = 14
Time = 40004, Timer0Count = 78, Timer1Count = 19
Time = 50005, Timer0Count = 98, Timer1Count = 24
Time = 60006, Timer0Count = 118, Timer1Count = 29
```

---

### 4. FakeAnalogWrite on Arduino Nano_33_BLE

The following is the sample terminal output when running example [FakeAnalogWrite](examples/FakeAnalogWrite) on **Arduino Nano_33_BLE** to demonstrate the usage of PWWM fakeAnalogWrite to simulate PWM analogWrite, but being able to write to many more pins.

```
Starting FakeAnalogWrite on Nano 33 BLE
NRF52_MBED_TimerInterrupt v1.4.1
[TISR] Timer = NRF_TIMER3, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 10000.00, _count = 100
Starting ITimer OK, millis() = 909
Add index 0, pin = 2, input PWM_Value=0, mapped PWM_Value= 0
Add index 1, pin = 3, input PWM_Value=0, mapped PWM_Value= 0
Add index 2, pin = 4, input PWM_Value=0, mapped PWM_Value= 0
Add index 3, pin = 5, input PWM_Value=0, mapped PWM_Value= 0
Add index 4, pin = 6, input PWM_Value=0, mapped PWM_Value= 0
Add index 5, pin = 7, input PWM_Value=0, mapped PWM_Value= 0
Add index 6, pin = 8, input PWM_Value=0, mapped PWM_Value= 0
Add index 7, pin = 9, input PWM_Value=0, mapped PWM_Value= 0
Test PWM_Value = 0, max = 255
Update index 0, pin = 2, input PWM_Value=5, mapped PWM_Value= 14
Update index 1, pin = 3, input PWM_Value=5, mapped PWM_Value= 14
Update index 2, pin = 4, input PWM_Value=5, mapped PWM_Value= 14
Update index 3, pin = 5, input PWM_Value=5, mapped PWM_Value= 14
Update index 4, pin = 6, input PWM_Value=5, mapped PWM_Value= 14
Update index 5, pin = 7, input PWM_Value=5, mapped PWM_Value= 14
Update index 6, pin = 8, input PWM_Value=5, mapped PWM_Value= 14
Update index 7, pin = 9, input PWM_Value=5, mapped PWM_Value= 14
Test PWM_Value = 5, max = 255
Update index 0, pin = 2, input PWM_Value=10, mapped PWM_Value= 27
Update index 1, pin = 3, input PWM_Value=10, mapped PWM_Value= 27
Update index 2, pin = 4, input PWM_Value=10, mapped PWM_Value= 27
Update index 3, pin = 5, input PWM_Value=10, mapped PWM_Value= 27
Update index 4, pin = 6, input PWM_Value=10, mapped PWM_Value= 27
Update index 5, pin = 7, input PWM_Value=10, mapped PWM_Value= 27
Update index 6, pin = 8, input PWM_Value=10, mapped PWM_Value= 27
Update index 7, pin = 9, input PWM_Value=10, mapped PWM_Value= 27
Test PWM_Value = 10, max = 255
Update index 0, pin = 2, input PWM_Value=15, mapped PWM_Value= 39
Update index 1, pin = 3, input PWM_Value=15, mapped PWM_Value= 39
Update index 2, pin = 4, input PWM_Value=15, mapped PWM_Value= 39
Update index 3, pin = 5, input PWM_Value=15, mapped PWM_Value= 39
Update index 4, pin = 6, input PWM_Value=15, mapped PWM_Value= 39
Update index 5, pin = 7, input PWM_Value=15, mapped PWM_Value= 39
Update index 6, pin = 8, input PWM_Value=15, mapped PWM_Value= 39
Update index 7, pin = 9, input PWM_Value=15, mapped PWM_Value= 39
Test PWM_Value = 15, max = 255
Update index 0, pin = 2, input PWM_Value=20, mapped PWM_Value= 49
Update index 1, pin = 3, input PWM_Value=20, mapped PWM_Value= 49
Update index 2, pin = 4, input PWM_Value=20, mapped PWM_Value= 49
Update index 3, pin = 5, input PWM_Value=20, mapped PWM_Value= 49
Update index 4, pin = 6, input PWM_Value=20, mapped PWM_Value= 49
Update index 5, pin = 7, input PWM_Value=20, mapped PWM_Value= 49
Update index 6, pin = 8, input PWM_Value=20, mapped PWM_Value= 49
Update index 7, pin = 9, input PWM_Value=20, mapped PWM_Value= 49
Test PWM_Value = 20, max = 255
...
Update index 0, pin = 2, input PWM_Value=100, mapped PWM_Value= 118
Update index 1, pin = 3, input PWM_Value=100, mapped PWM_Value= 118
Update index 2, pin = 4, input PWM_Value=100, mapped PWM_Value= 118
Update index 3, pin = 5, input PWM_Value=100, mapped PWM_Value= 118
Update index 4, pin = 6, input PWM_Value=100, mapped PWM_Value= 118
Update index 5, pin = 7, input PWM_Value=100, mapped PWM_Value= 118
Update index 6, pin = 8, input PWM_Value=100, mapped PWM_Value= 118
Update index 7, pin = 9, input PWM_Value=100, mapped PWM_Value= 118
Test PWM_Value = 100, max = 255
Update index 0, pin = 2, input PWM_Value=105, mapped PWM_Value= 120
Update index 1, pin = 3, input PWM_Value=105, mapped PWM_Value= 120
Update index 2, pin = 4, input PWM_Value=105, mapped PWM_Value= 120
Update index 3, pin = 5, input PWM_Value=105, mapped PWM_Value= 120
Update index 4, pin = 6, input PWM_Value=105, mapped PWM_Value= 120
Update index 5, pin = 7, input PWM_Value=105, mapped PWM_Value= 120
Update index 6, pin = 8, input PWM_Value=105, mapped PWM_Value= 120
Update index 7, pin = 9, input PWM_Value=105, mapped PWM_Value= 120
Test PWM_Value = 105, max = 255
Update index 0, pin = 2, input PWM_Value=110, mapped PWM_Value= 121
Update index 1, pin = 3, input PWM_Value=110, mapped PWM_Value= 121
Update index 2, pin = 4, input PWM_Value=110, mapped PWM_Value= 121
Update index 3, pin = 5, input PWM_Value=110, mapped PWM_Value= 121
Update index 4, pin = 6, input PWM_Value=110, mapped PWM_Value= 121
Update index 5, pin = 7, input PWM_Value=110, mapped PWM_Value= 121
Update index 6, pin = 8, input PWM_Value=110, mapped PWM_Value= 121
Update index 7, pin = 9, input PWM_Value=110, mapped PWM_Value= 121
Test PWM_Value = 110, max = 255
Update index 0, pin = 2, input PWM_Value=115, mapped PWM_Value= 123
Update index 1, pin = 3, input PWM_Value=115, mapped PWM_Value= 123
Update index 2, pin = 4, input PWM_Value=115, mapped PWM_Value= 123
Update index 3, pin = 5, input PWM_Value=115, mapped PWM_Value= 123
Update index 4, pin = 6, input PWM_Value=115, mapped PWM_Value= 123
Update index 5, pin = 7, input PWM_Value=115, mapped PWM_Value= 123
Update index 6, pin = 8, input PWM_Value=115, mapped PWM_Value= 123
Update index 7, pin = 9, input PWM_Value=115, mapped PWM_Value= 123
Test PWM_Value = 115, max = 255
Update index 0, pin = 2, input PWM_Value=120, mapped PWM_Value= 124
Update index 1, pin = 3, input PWM_Value=120, mapped PWM_Value= 124
Update index 2, pin = 4, input PWM_Value=120, mapped PWM_Value= 124
Update index 3, pin = 5, input PWM_Value=120, mapped PWM_Value= 124
Update index 4, pin = 6, input PWM_Value=120, mapped PWM_Value= 124
Update index 5, pin = 7, input PWM_Value=120, mapped PWM_Value= 124
Update index 6, pin = 8, input PWM_Value=120, mapped PWM_Value= 124
Update index 7, pin = 9, input PWM_Value=120, mapped PWM_Value= 124
Test PWM_Value = 120, max = 255
```

---

### 5. Change_Interval on Arduino Nano_33_BLE

The following is the sample terminal output when running example [Change_Interval](examples/Change_Interval) on **Arduino Nano_33_BLE** to demonstrate how to change Timer Interval on-the-fly

```
Starting Change_Interval on Nano 33 BLE
NRF52_MBED_TimerInterrupt v1.4.1
[TISR] Timer = NRF_TIMER4, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 2.00, _count = 500000
Starting ITimer0 OK, millis() = 810
[TISR] Timer = NRF_TIMER3, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 0.50, _count = 2000000
Starting ITimer1 OK, millis() = 812
Time = 10001, Timer0Count = 18, Timer1Count = 4
Time = 20002, Timer0Count = 38, Timer1Count = 9
[TISR] Timer = NRF_TIMER4, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 1.00, _count = 1000000
[TISR] Timer = NRF_TIMER3, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 0.25, _count = 4000000
Changing Interval, Timer0 = 1000,  Timer1 = 4000
Time = 30003, Timer0Count = 48, Timer1Count = 11
Time = 40004, Timer0Count = 58, Timer1Count = 14
[TISR] Timer = NRF_TIMER4, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 2.00, _count = 500000
[TISR] Timer = NRF_TIMER3, Timer Clock (Hz) = 1000000.00
[TISR] Frequency = 0.50, _count = 2000000
Changing Interval, Timer0 = 500,  Timer1 = 2000
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level (_TIMERINTERRUPT_LOGLEVEL_) from 0 to 4

```cpp
// These define's must be placed at the beginning before #include "NRF52_MBED_TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.

---
---


### Issues

Submit issues to: [NRF52_MBED_TimerInterrupt issues](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/issues)

---

## TO DO

1. Search for bug and improvement.

---

## DONE

 1. Basic hardware timers for NRF52832 and NRF52840.
 2. More hardware-initiated software-enabled timers
 3. Longer time interval
 4. Similar features for remaining Arduino boards such as AVR, ESP32, ESP8266, STM32, SAM-DUE, SAMD21/SAMD51, nRF52, Teensy, etc.
 5. Add Table of Contents
 6. Add new **mbed_nano** to list of compatible architectures.
 7. Fix `multiple-definitions` linker error
 8. Optimize library code by using `reference-passing` instead of `value-passing`
 9. Add support to Seeeduino nRF52840-based boards such as **SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE**, etc. using Seeeduino `mbed` core
10. Add astyle using `allman` style. Restyle the library


---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Thanks to [per1234](https://github.com/per1234) to make PR in [Add mbed_nano to list of compatible architectures #3](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/pull/3) leading to the new version v1.2.1 to add new **mbed_nano** to list of compatible architectures.
2. Thanks to [cattledogGH](https://github.com/cattledogGH) to report issue in [Nano 33 BLE will not run library examples using NRF_TIMER_1 #6](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/issues/6) leading to the new version v1.3.0 to not use `NRF_TIMER_1` because of [ArduinoCore-mbed mbed_nano core v2.0.0+](https://github.com/arduino/ArduinoCore-mbed)


<table>
  <tr>
    <td align="center"><a href="https://github.com/per1234"><img src="https://github.com/per1234.png" width="100px;" alt="per1234"/><br /><sub><b>per1234</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/cattledogGH"><img src="https://github.com/cattledogGH.png" width="100px;" alt="cattledogGH"/><br /><sub><b>cattledogGH</b></sub></a><br /></td>
  </tr> 
</table>

---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/blob/main/LICENSE)

---

## Copyright

Copyright 2020- Khoi Hoang


