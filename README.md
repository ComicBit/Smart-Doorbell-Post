Smart Doorbell Wiki
===================

Introduction
------------

This project revolves around enhancing a traditional doorbell system with smart capabilities. The aim is to connect the doorbell to a local network and send a POST request to a specific URL whenever the doorbell is pressed. This will allow integration of the doorbell system with other smart devices and services. For instance you can use this in combination with Homebridge to hear the doorbell in HomeKit.

Hardware Components
-------------------

*   Seed Studio ESP32-C3 board
*   PC817C Optoisolator
*   Pull-up resistor (1k ohm)
*   Current-limiting resistor (390 ohms)
*   Doorbell buzzer operating at 5V

PCB Design
----------

A custom PCB design for this project is available in the `design/gerber` folder in the repository. The design includes all the necessary connections for the ESP32-C3, the optoisolator, and the resistors. You can use this design to create a compact and reliable hardware setup for this project.

Software Components
-------------------

The project uses the Arduino platform for programming the ESP32-C3. The code connects the ESP32-C3 to a Wi-Fi network, sets up an interrupt to detect when the doorbell is pressed, sends a POST request when the doorbell is pressed, and optimizes power consumption by using deep sleep mode when idle.

Additionally, a cooldown mechanism is implemented using a timer to avoid spamming the network with multiple POST requests if the doorbell plays multiple sounds in quick succession. The cooldown timer can be set to a specific duration, allowing a period of time to pass before sending another POST request.

You will need to install the Arduino IDE and the ESP32 board definitions to compile and upload the code. You also need the Arduino `WiFi` and `HTTPClient` libraries for network connectivity and HTTP requests.

Setup Instructions
------------------

1.  Install the Arduino IDE and the ESP32 board definitions.
2.  Open the Arduino sketch provided in the repository.
3.  Replace `<Your Network SSID>`, `<Your Network Password>`, and `http://192.168.50.150:9595/door` in the code with your actual Wi-Fi SSID, password, and the URL you want to send the POST request to.
4.  Adjust the cooldown timer duration according to your requirements. This can be done by modifying the timer settings in the code.
5.  Connect the ESP32-C3 to your computer.
6.  Select the correct board and port in the Arduino IDE.
7.  Compile and upload the sketch to the ESP32-C3.
8.  Assemble the hardware components as described in the PCB design.
9.  Connect the ESP32-C3 setup to the doorbell system.

State of the project
-------
As today the design is still UNTESTED and it will be updated once I will be able to build the boards and test everything properly.

Safety Precautions
------------------

Remember to always take necessary safety precautions when working with electricity. If you're unsure, consider seeking help from someone with experience in electronics. This project involves interfacing with a doorbell system, which typically operates at low voltages but can still present risks if not handled correctly.

Support
-------

If you have any questions or run into any issues, feel free to open an issue on the repository. We'll be happy to assist you.

Future Enhancements
-------------------

While this project provides a basic integration of a doorbell system with a smart home setup, there's a lot more that could be done. As of today, the way the battery will get charged is using the type c connector because I couldn't find a clear answer on how to power the board from the pins without breaking the charging functionality. I found only a reference in the [Seed Studio documentation](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/) in the chapter titled 'Power Pins', which I didn't quite understand. Future enhancements would aim to implement the possibility of opening the door from the smart home system. I would love to be able to hear and speak from HomeKit but we will see how much time this would take me. Contributions are more than welcome.

License
-------

This project is open source and available under the [Apache 2 License](https://www.apache.org/licenses/LICENSE-2.0).