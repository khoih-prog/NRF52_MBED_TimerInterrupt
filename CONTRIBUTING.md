## Contributing to NRF52_MBED_TimerInterrupt

### Reporting Bugs

Please report bugs in NRF52_MBED_TimerInterrupt if you find them.

However, before reporting a bug please check through the following:

* [Existing Open Issues](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/issues) - someone might have already encountered this.

If you don't find anything, please [open a new issue](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/issues/new).

### How to submit a bug report

Please ensure to specify the following:

* Arduino IDE version (e.g. 1.8.19) or Platform.io version
* `nRF52840 mbed` Core Version (e.g. Arduino mbed_nano core v3.4.1, Seeeduino mbed core v2.7.2)
* `nRF52840-based Nano_33_BLE` Board type (e.g. Nano_33_BLE, Nano_33_BLE_Sense, SEEED_XIAO_NRF52840 and SEEED_XIAO_NRF52840_SENSE, etc.)
* Contextual information (e.g. what you were trying to achieve)
* Simplest possible steps to reproduce
* Anything that might be relevant in your opinion, such as:
  * Operating system (Windows, Ubuntu, etc.) and the output of `uname -a`
  * Network configuration


### Example

```
Arduino IDE version: 1.8.19
Arduino mbed_nano core v3.4.1
Nano_33_BLE board
OS: Ubuntu 20.04 LTS
Linux xy-Inspiron-3593 5.15.0-52-generic #58~20.04.1-Ubuntu SMP Thu Oct 13 13:09:46 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux

Context:
I encountered a crash while using this library

Steps to reproduce:
1. ...
2. ...
3. ...
4. ...
```

---

### Sending Feature Requests

Feel free to post feature requests. It's helpful if you can explain exactly why the feature would be useful.

There are usually some outstanding feature requests in the [existing issues list](https://github.com/khoih-prog/NRF52_MBED_TimerInterrupt/issues?q=is%3Aopen+is%3Aissue+label%3Aenhancement), feel free to add comments to them.

---

### Sending Pull Requests

Pull Requests with changes and fixes are also welcome!

Please use the `astyle` to reformat the updated library code as follows (demo for Ubuntu Linux)

1. Change directory to the library GitHub

```
xy@xy-Inspiron-3593:~$ cd Arduino/xy/NRF52_MBED_TimerInterrupt_GitHub/
xy@xy-Inspiron-3593:~/Arduino/xy/NRF52_MBED_TimerInterrupt_GitHub$
```

2. Issue astyle command

```
xy@xy-Inspiron-3593:~/Arduino/xy/NRF52_MBED_TimerInterrupt_GitHub$ bash utils/restyle.sh
```

