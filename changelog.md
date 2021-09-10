# NRF52_MBED_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/NRF52_MBED_TimerInterrupt.svg?)](https://www.ardu-badge.com/NRF52_MBED_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/NRF52_MBED_TimerInterrupt.svg)](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/NRF52_MBED_TimerInterrupt.svg)](http://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.1](#releases-v121)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.0.2](#releases-v102)
  * [Releases v1.0.1](#releases-v101)

---
---

## Changelog

### Releases v1.3.0

1. Don't use NRF_TIMER_1 because of [ArduinoCore-mbed mbed_nano core v2.0.0+](https://github.com/arduino/ArduinoCore-mbed)
2. Force to use NRF_TIMER_3 if select NRF_TIMER_0, NRF_TIMER_1 or NRF_TIMER_2
3. Check [Nano 33 BLE will not run library examples using NRF_TIMER_1 #6](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/issues/6)


### Releases v1.2.1

1. Add **mbed_nano** to list of compatible architectures. For more info, Check [Add mbed_nano to list of compatible architectures #3](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/pull/3).


### Releases v1.2.0

1. Add better debug feature.
2. Optimize code and examples to reduce RAM usage
3. Add Table of Contents

### Releases v1.1.1

1. Add example [**Change_Interval**](examples/Change_Interval)
2. Bump up version to sync with other TimerInterrupt Libraries. Modify Version String.

### Releases v1.0.2

1. Add example [**ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex) and optimize example [**ISR_16_Timers_Array**](examples/ISR_16_Timers_Array)

### Releases v1.0.1

1. Initial coding for Nano-33-BLE and sync with [**NRF52_TimerInterrupt Library**](https://github.com/khoih-prog/NRF52_TimerInterrupt)



