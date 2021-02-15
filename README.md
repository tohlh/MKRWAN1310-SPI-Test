# MKRWAN1310 SPI Test
This is a project that tests SPI transmission between SAM D21 (master) and STM32 (slave) of the Murata module on the Arduino MKRWAN 1310.

This repo contains three STM32 firmwares that run in different SPI modes: polling, IT and DMA. It also contains a master sketch that runs on SAM D21 that transfers data to STM32.

The purpose of this project is to eventually build a Murata LoRaWAN module firmware that is able to communicate with SAM D21 via SPI, which enables SAM D21 to communicate with the LoRaWAN module and SPI flash RAM in a multi-slave mode. It is currently an issue as these two devices cause contention on SERCOM4 as they share the same pins.

## Compiling and flashing STM32 firmware

Eclipse with System Workbench for STM32 is required to compile the firmware, follow [this guide](http://www.openstm32.org/Installing%2BSystem%2BWorkbench%2Bfor%2BSTM32%2Bfrom%2BEclipse#Important_note_about_your_MAC_OSX_host_version) to install System Workbench on your IDE.

Once installed, you can then build the project that will generate a fw.h file, which can be flashed onto the STM32 on MKRWAN 1310 with MKRWANFWUpdate_standalone example in https://github.com/arduino-libraries/MKRWAN.

The repo already includes the latest fw.h file for each version of the firmware.

## The Master sketch
Once the firmware is installed on STM32, you can then test SPI transfer from SAM D21 with this sketch.

The test is done by entering a number between 1 - 9 in the serial monitor. STM32 will receive this number and trigger `LORA_IRQ` pin on SAM D21 in that number of times.

With the current firmware and master sketch, it is expected to see the following message in serial monitor if the user entered 1, 4, 6:
```
20:03:19.641 -> MKRWAN1310 SPI Test
20:03:19.641 -> Please enter a number from 1 to 9
20:03:23.933 -> TRANSFER: txData: 0x1, rxData: 0xFF
20:03:23.933 -> LORA_IRQ RISING was triggered 1 times
20:03:23.933 -> Please enter a number from 1 to 9
20:03:25.517 -> TRANSFER: txData: 0x4, rxData: 0xFF
20:03:25.517 -> LORA_IRQ RISING was triggered 4 times
20:03:25.517 -> Please enter a number from 1 to 9
20:03:27.045 -> TRANSFER: txData: 0x6, rxData: 0xFF
20:03:27.045 -> LORA_IRQ RISING was triggered 6 times
20:03:27.045 -> Please enter a number from 1 to 9
```
