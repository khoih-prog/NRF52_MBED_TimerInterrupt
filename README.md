# NRF52_MBED_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/NRF52_MBED_TimerInterrupt.svg?)](https://www.ardu-badge.com/NRF52_MBED_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/NRF52_MBED_TimerInterrupt.svg)](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/NRF52_MBED_TimerInterrupt.svg)](http://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/issues)

---
---

## Features

This library enables you to use Interrupt from Hardware Timers on an NRF52-based board using mbed-RTOS such as Nano-33-BLE.

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **16 ISR-based Timers, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

### Why do we need this Hardware Timer Interrupt?

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed on-time or not at all, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware timers, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

#### Important Notes:

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

---
---

### Releases v1.0.1

1. Initial coding for Nano-33-BLE and sync with [**NRF52_TimerInterrupt Library**](https://github.com/khoih-prog/NRF52_TimerInterrupt)


#### Supported Boards

  - **Arduino Nano-33-BLE**

---
---

## Prerequisite

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino mbed v1.3.0+`](https://www.adafruit.com/) for NRF52-based board using mbed-RTOS such as Nano-33-BLE.
 3. To use with certain example
   - [`SimpleTimer library`](https://github.com/schinken/SimpleTimer) for [ISR_16_Timers_Array example](examples/ISR_16_Timers_Array).
   
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
3. Install [**NRF52_MBED_TimerInterrupt** library](https://platformio.org/lib/show/xxxxx/NRF52_MBED_TimerInterrupt) by using [Library Manager](https://platformio.org/lib/show/xxxxx/NRF52_MBED_TimerInterrupt/installation). Search for **NRF52_MBED_TimerInterrupt** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Libraries' Patches

1. If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

2. To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

3. To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)

4. To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for this [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

6. **To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library**, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

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

7. Check if you need to install the UIPthernet patch [new NRF52 core F3/F4 compatibility](https://github.com/UIPEthernet/UIPEthernet/commit/c6d6519a260166b722b9cee5dd1f0fb2682e6782) to avoid errors `#include HardwareSPI.h` on some NRF52 boards (Nucleo-32 F303K8, etc.)

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using **xyz-Impl.h instead of standard xyz.cpp**, possibly creates certain `Multiple Definitions` Linker error in certain use cases. Although it's simple to just modify several lines of code, either in the library or in the application, the library is adding 2 more source directories

1. **scr_h** for new h-only files
2. **src_cpp** for standard h/cpp files

besides the standard **src** directory.

To use the **old standard cpp** way, locate this library' directory, then just 

1. **Delete the all the files in src directory.**
2. **Copy all the files in src_cpp directory into src.**
3. Close then reopen the application code in Arduino IDE, etc. to recompile from scratch.

To re-use the **new h-only** way, just 

1. **Delete the all the files in src directory.**
2. **Copy the files in src_h directory into src.**
3. Close then reopen the application code in Arduino IDE, etc. to recompile from scratch.

---
---


## New from v1.0.1

Now with these new `16 ISR-based timers` (while consuming only **1 hardware timer**), the maximum interval is practically unlimited (limited only by unsigned long miliseconds). The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers Therefore, their executions are not blocked by bad-behaving functions / tasks.
This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_16_Timers_Array**](examples/ISR_16_Timers_Array) example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.
Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.
This non-being-blocked important feature is absolutely necessary for mission-critical tasks. 
You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

---

## Supported Boards

- **NRF52840-based board using mbed-RTOS such as Nano-33-BLE.**

---

## Usage

Before using any Timer, you have to make sure the Timer has not been used by any other purpose.

### 1. Using only Hardware Timer directly

#### 1.1 Init Hardware Timer

```
// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1,NRF_TIMER_3,NRF_TIMER_4 (1,3 and 4)
// If you select the already-used NRF_TIMER_0 or NRF_TIMER_2, it'll be auto modified to use NRF_TIMER_1

// Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);
```

#### 1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function

```
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
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_US, TimerHandler))
  {
    startMillis = millis();
    Serial.printf("Starting  ITimer OK, millis() = %ld\n", startMillis);
  }
  else
    Serial.println("Can't set ITimer correctly. Select another freq. or interval");
}  
```

### 2. Using 16 ISR_based Timers from 1 Hardware Timers


#### 2.1 Init Hardware Timer and ISR-based Timer

```
// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1,NRF_TIMER_3,NRF_TIMER_4 (1,3 and 4)
// If you select the already-used NRF_TIMER_0 or NRF_TIMER_2, it'll be auto modified to use NRF_TIMER_1

// Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);

// Init NRF52_MBED_ISRTimer
// Each NRF52_MBED_ISRTimer can service 16 different ISR-based timers
NRF52_MBED_ISRTimer ISR_Timer;
```

#### 2.2 Set Hardware Timer Interval and attach Timer Interrupt Handler functions

```
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
 3. [SwitchDebounce](examples/SwitchDebounce)
 4. [TimerInterruptTest](examples/TimerInterruptTest)
 5. [TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)


---
---

### Example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array)

```
#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
  #error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "NRF52_MBED_TimerInterrupt.h"
// For Nano33-BLE, don't use Serial.print() in ISR as system will definitely hang.
#define NRF52_MBED_TIMER_INTERRUPT_DEBUG      1

#include "NRF52_MBED_TimerInterrupt.h"

#include "NRF52_MBED_ISR_Timer.h"

#include <SimpleTimer.h>              // https://github.com/schinken/SimpleTimer

#ifndef LED_BUILTIN
#define LED_BUILTIN       D13
#endif

#ifndef LED_BLUE
#define LED_BLUE          D7
#endif

#ifndef LED_RED
#define LED_RED           D8
#endif

#define HW_TIMER_INTERVAL_US      10000L

volatile uint32_t startMillis = 0;

// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1,NRF_TIMER_3,NRF_TIMER_4 (1,3 and 4)
// If you select the already-used NRF_TIMER_0 or NRF_TIMER_2, it'll be auto modified to use NRF_TIMER_1

// Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);

// Init NRF52_MBED_ISRTimer
// Each NRF52_MBED_ISRTimer can service 16 different ISR-based timers
NRF52_MBED_ISRTimer ISR_Timer;

#define LED_TOGGLE_INTERVAL_MS        2000L

void TimerHandler(void)
{
  static bool toggle  = false;
  static int timeRun  = 0;

  ISR_Timer.run();

  // Toggle LED every LED_TOGGLE_INTERVAL_MS = 2000ms = 2s
  if (++timeRun == ((LED_TOGGLE_INTERVAL_MS * 1000) / HW_TIMER_INTERVAL_US) )
  {
    timeRun = 0;

    //timer interrupt toggles pin LED_BUILTIN
    digitalWrite(LED_BUILTIN, toggle);
    toggle = !toggle;
  }
}

#define NUMBER_ISR_TIMERS         16

// You can assign any interval for any timer here, in milliseconds
uint32_t TimerInterval[NUMBER_ISR_TIMERS] =
{
  5000L,  10000L,  15000L,  20000L,  25000L,  30000L,  35000L,  40000L,
  45000L, 50000L,  55000L,  60000L,  65000L,  70000L,  75000L,  80000L
};

volatile unsigned long deltaMillis    [NUMBER_ISR_TIMERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
volatile unsigned long previousMillis [NUMBER_ISR_TIMERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

typedef void (*irqCallback)  (void);

// In NRF52, avoid doing something fancy in ISR, for example Serial.print()
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething0()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[0]    = currentMillis - previousMillis[0];
  previousMillis[0] = currentMillis;
}

void doingSomething1()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[1]    = currentMillis - previousMillis[1];
  previousMillis[1] = currentMillis;
}

void doingSomething2()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[2]    = currentMillis - previousMillis[2];
  previousMillis[2] = currentMillis;
}

void doingSomething3()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[3]    = currentMillis - previousMillis[3];
  previousMillis[3] = currentMillis;
}

void doingSomething4()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[4]    = currentMillis - previousMillis[4];
  previousMillis[4] = currentMillis;
}

void doingSomething5()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[5]    = currentMillis - previousMillis[5];
  previousMillis[5] = currentMillis;
}

void doingSomething6()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[6]    = currentMillis - previousMillis[6];
  previousMillis[6] = currentMillis;
}

void doingSomething7()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[7]    = currentMillis - previousMillis[7];
  previousMillis[7] = currentMillis;
}

void doingSomething8()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[8]    = currentMillis - previousMillis[8];
  previousMillis[8] = currentMillis;
}

void doingSomething9()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[9]    = currentMillis - previousMillis[9];
  previousMillis[9] = currentMillis;
}

void doingSomething10()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[10]    = currentMillis - previousMillis[10];
  previousMillis[10] = currentMillis;
}

void doingSomething11()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[11]    = currentMillis - previousMillis[11];
  previousMillis[11] = currentMillis;
}

void doingSomething12()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[12]    = currentMillis - previousMillis[12];
  previousMillis[12] = currentMillis;
}

void doingSomething13()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[13]    = currentMillis - previousMillis[13];
  previousMillis[13] = currentMillis;
}

void doingSomething14()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[14]    = currentMillis - previousMillis[14];
  previousMillis[14] = currentMillis;
}

void doingSomething15()
{
  unsigned long currentMillis  = millis();
  
  deltaMillis[15]    = currentMillis - previousMillis[15];
  previousMillis[15] = currentMillis;
}

irqCallback irqCallbackFunc[NUMBER_ISR_TIMERS] =
{
  doingSomething0,  doingSomething1,  doingSomething2,  doingSomething3,
  doingSomething4,  doingSomething5,  doingSomething6,  doingSomething7,
  doingSomething8,  doingSomething9,  doingSomething10, doingSomething11,
  doingSomething12, doingSomething13, doingSomething14, doingSomething15
};

////////////////////////////////////////////////


#define SIMPLE_TIMER_MS        2000L

// Init SimpleTimer
SimpleTimer simpleTimer;

// Here is software Timer, you can do somewhat fancy stuffs without many issues.
// But always avoid
// 1. Long delay() it just doing nothing and pain-without-gain wasting CPU power.Plan and design your code / strategy ahead
// 2. Very long "do", "while", "for" loops without predetermined exit time.
void simpleTimerDoingSomething2s()
{
  static unsigned long previousMillis = startMillis;

  unsigned long currMillis = millis();

  Serial.printf("SimpleTimer : %ds, ms = %lu, Dms : %lu\n", SIMPLE_TIMER_MS / 1000, currMillis, currMillis - previousMillis);

  for (int i = 0; i < NUMBER_ISR_TIMERS; i++)
  {
    Serial.printf("Timer : %d, programmed : %lu, actual : %lu\n", i, TimerInterval[i], deltaMillis[i]);
  }

  previousMillis = currMillis;
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  Serial.printf("\nStarting ISR_16_Timers_Array on %s\n", BOARD_NAME);
  Serial.printf("Version : v%s\n", NRF52_MBED_TIMER_INTERRUPT_VERSION);

  // Interval in microsecs
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_US, TimerHandler))
  {
    startMillis = millis();
    Serial.printf("Starting  ITimer OK, millis() = %ld\n", startMillis);
  }
  else
    Serial.println("Can't set ITimer correctly. Select another freq. or interval");

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  for (int i = 0; i < NUMBER_ISR_TIMERS; i++)
  {
    previousMillis[i] = startMillis;
    ISR_Timer.setInterval(TimerInterval[i], irqCallbackFunc[i]);
  }

  // You need this timer for non-critical tasks. Avoid abusing ISR if not absolutely necessary.
  simpleTimer.setInterval(SIMPLE_TIMER_MS, simpleTimerDoingSomething2s);
}

#define BLOCKING_TIME_MS      3000L

void loop()
{
  // This unadvised blocking task is used to demonstrate the blocking effects onto the execution and accuracy to Software timer
  // You see the time elapse of ISR_Timer still accurate, whereas very unaccurate for Software Timer
  // The time elapse for 2000ms software timer now becomes 3000ms (BLOCKING_TIME_MS)
  // While that of ISR_Timer is still prefect.
  delay(BLOCKING_TIME_MS);

  // You need this Software timer for non-critical tasks. Avoid abusing ISR if not absolutely necessary
  // You don't need to and never call ISR_Timer.run() here in the loop(). It's already handled by ISR timer.
  simpleTimer.run();
}
```
---
---

### Debug Terminal Output Samples

1. The following is the sample terminal output when running example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) on **Nano 33 BLE** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy**.  The ISR timer is **programmed for 2s, is activated exactly after 2.000s !!!**

While software timer, **programmed for 2s, is activated after more than 3.000s in loop().

```
Starting ISR_16_Timers_Array on Nano 33 BLE
Version : 1.0.1
NRF52_MBED_TimerInterrupt: Timer = NRF_TIMER3
NRF52_MBED_TimerInterrupt: _fre = 1000000.00, _count = 10000
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

2. The following is the sample terminal output when running example [**TimerInterruptTest**](examples/TimerInterruptTest) on **Arduino Nano-33-BLE** to demonstrate the accuracy and how to start/stop Hardware Timers.

```
Starting TimerInterruptTest on Nano 33 BLE
Version : v1.0.1
NRF52_MBED_TimerInterrupt: Timer = NRF_TIMER3
NRF52_MBED_TimerInterrupt: _fre = 1000000.00, _count = 1000000
Starting  ITimer0 OK, millis() = 5660
NRF52_MBED_TimerInterrupt: Timer = NRF_TIMER4
NRF52_MBED_TimerInterrupt: _fre = 1000000.00, _count = 3000000
Starting  ITimer1 OK, millis() = 5665
Stop ITimer0, millis() = 5669
Start ITimer0, millis() = 10670
Stop ITimer1, millis() = 15001
Stop ITimer0, millis() = 15671
Start ITimer0, millis() = 20672
Stop ITimer0, millis() = 25673
Start ITimer1, millis() = 30002
Start ITimer0, millis() = 30674
Stop ITimer0, millis() = 35675
Start ITimer0, millis() = 40676
Stop ITimer1, millis() = 45003
Stop ITimer0, millis() = 45677
Start ITimer0, millis() = 50678
Stop ITimer0, millis() = 55679
Start ITimer1, millis() = 60004
Start ITimer0, millis() = 60680
```

---

3. The following is the sample terminal output when running example [**Argument_None**](examples/Argument_None) on **Arduino Nano-33-BLE** to demonstrate the accuracy of Hardware Timers.

```
Starting Argument_None on Nano 33 BLE
Version : 1.0.1
NRF52_MBED_TimerInterrupt: Timer = NRF_TIMER1
NRF52_MBED_TimerInterrupt: _fre = 1000000.00, _count = 500000
Starting  ITimer0 OK, millis() = 1519
NRF52_MBED_TimerInterrupt: Timer = NRF_TIMER3
NRF52_MBED_TimerInterrupt: _fre = 1000000.00, _count = 2000000
Starting  ITimer1 OK, millis() = 1521
Time = 10001, Timer0Count = 16, Timer1Count = 4
Time = 20002, Timer0Count = 37, Timer1Count = 9
Time = 30003, Timer0Count = 57, Timer1Count = 14
Time = 40004, Timer0Count = 77, Timer1Count = 19
Time = 50005, Timer0Count = 97, Timer1Count = 24
Time = 60006, Timer0Count = 117, Timer1Count = 29
Time = 70007, Timer0Count = 137, Timer1Count = 34
Time = 80008, Timer0Count = 157, Timer1Count = 39
Time = 90009, Timer0Count = 177, Timer1Count = 44
Time = 100010, Timer0Count = 197, Timer1Count = 49

```

4. The following is the sample terminal output when running example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) on **Adafruit NRF52840_ITSYBITSY** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy or blocked**. The 16 independent ISR timers are **programmed to be activated repetitively after certain intervals, is activated exactly after that programmed interval !!!**

While software timer, **programmed for 2s, is activated after 10.000s in loop()!!!**.

In this example, 16 independent ISR Timers are used, yet utilized just one Hardware Timer. The Timer Intervals and Function Pointers are stored in arrays to facilitate the code modification.


```
Starting ISR_16_Timers_Array on NRF52840_ITSYBITSY
Version : 1.0.1
CPU Frequency = 64 MHz
NRF52TimerInterrupt: F_CPU (MHz) = 64, Timer = NRF_TIMER2
NRF52TimerInterrupt: _fre = 1000000.00, _count = 1000
Starting  ITimer OK, millis() = 915
5s: Delta ms = 5000, ms = 5915
simpleTimer2s:Dms=10001
5s: Delta ms = 5001, ms = 10916
5s: Delta ms = 4999, ms = 15915
5s: Delta ms = 5000, ms = 20915
simpleTimer2s:Dms=10003
5s: Delta ms = 5000, ms = 25915
5s: Delta ms = 5000, ms = 30915
simpleTimer2s:Dms=10000
5s: Delta ms = 5000, ms = 35915
5s: Delta ms = 5000, ms = 40915
simpleTimer2s:Dms=10000
5s: Delta ms = 5000, ms = 45915
5s: Delta ms = 5000, ms = 50915
simpleTimer2s:Dms=10004
5s: Delta ms = 5000, ms = 55915
5s: Delta ms = 5000, ms = 60915
simpleTimer2s:Dms=10001
5s: Delta ms = 5000, ms = 65915
5s: Delta ms = 5000, ms = 70915
simpleTimer2s:Dms=10005
5s: Delta ms = 5000, ms = 75915
5s: Delta ms = 5000, ms = 80915
simpleTimer2s:Dms=10004
5s: Delta ms = 5000, ms = 85915
5s: Delta ms = 5000, ms = 90915
simpleTimer2s:Dms=10000
5s: Delta ms = 5001, ms = 95916
5s: Delta ms = 4999, ms = 100915
simpleTimer2s:Dms=10004
5s: Delta ms = 5000, ms = 105915
5s: Delta ms = 5000, ms = 110915
simpleTimer2s:Dms=10004
```
---
---

### Releases v1.0.1

1. Initial coding for Nano-33-BLE and sync with [**NRF52_TimerInterrupt Library**](https://github.com/khoih-prog/NRF52_TimerInterrupt)

#### Supported Boards

  - **Arduino Nano-33-BLE**

---
---

### Issues ###

Submit issues to: [NRF52_MBED_TimerInterrupt issues](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/issues)

---

## TO DO

1. Search for bug and improvement.


## DONE

1. Basic hardware timers for NRF52832 and NRF52840.
2. More hardware-initiated software-enabled timers
3. Longer time interval

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.


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


