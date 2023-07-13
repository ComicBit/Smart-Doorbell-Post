Smart Doorbell Overview
===============================

Bringing the traditional doorbell into the era of smart homes, this project aims to establish a budget-friendly, universal doorbell system. This will enable your doorbell to join the local network, sending a POST request to a designated URL every time the doorbell is pressed. Such integration is ideal with platforms like Homebridge and Homebridge Http Doorbell V3, which provide audible notifications via HomeKit.

Core Functionality
------------------

This smart doorbell operates using an optoisolator, which safely detects every doorbell press. In my case, a 9V DC power supply powers the doorbell, and this voltage is used to charge the battery via a buck converter. I am aware that different setups can be very different, and this will require extensive testing.

![alt text](https://github.com/ComicBit/Smart-Doorbell-Post/blob/main/img/pcb.png?raw=true)

Hardware Breakdown
------------------

Your smart doorbell will consist of:

*   Seed Studio ESP32-S3 board (the C3 is not a viable option because it misses the possibility of being waken up from external inputs)
*   PC817C Optoisolator
*   Buck converter DD2712SA 5v
*   Pull-up resistor (1k ohm)
*   Current-limiting resistor (390 ohms)
*   DO-41 Diode
*   Doorbell buzzer (operating at 5V) - note: different buzzer voltages may require adjustment of the 390-ohm resistor.
*   3x - JST 2 Pins connectors

Custom PCB Design
-----------------

The project includes a custom PCB design found in the `design/gerber` repository folder. This layout offers all the essential connections for the ESP32-S3, optoisolator, and resistors, leading to a compact and trustworthy hardware configuration. Note: Power input for the ESP is drawn from a pinout connected to the ESP's type c port.

Software Components
-------------------

Built on the Arduino platform, the ESP32-S3 code connects to a Wi-Fi network, sets up an interrupt for doorbell press detection, and sends POST requests accordingly. It also features an energy-efficient deep sleep mode during idle times. To prevent network spamming due to rapid doorbell presses, a timer creates a cooldown period between POST requests.

To work with the software, install the Arduino IDE, ESP32 board definitions, and Arduino `WiFi` and `HTTPClient` libraries.

Setup Procedure
---------------

1.  Install the Arduino IDE and ESP32 board definitions.
2.  Open the Arduino sketch from the repository.
3.  Substitute `<Your Network SSID>`, `<Your Network Password>`, and `http://192.168.50.150:9595/door` with your Wi-Fi SSID, password, and desired POST request URL.
4.  Adjust the cooldown timer duration to fit your needs.
5.  Connect the ESP32-S3 to your computer.
6.  Select the appropriate board and port in the Arduino IDE.
7.  Compile and upload the sketch to the ESP32-S3.
8.  Assemble the hardware as directed by the PCB design.
9.  Connect the doorbell setup to your doorbell system.

Project Status
--------------

As of now, the design is UNTESTED. Updates will follow after the boards' assembly and thorough testing.

Safety Warning
--------------

Always exercise safety when working with electricity. If you're inexperienced with electronics, seek help from a professional. Despite doorbell systems generally operating at low voltages, mishandling can lead to hazards.

Future Enhancements
-------------------

This project merely initiates the integration of doorbells into smart homes. Unfortunately though, due to my limited knowledge of PCB designing as right now the battery connection is quite finnicky.

Future enhancements may include distinguishing between different sounds, enabling door operation from the smart home system, and integrating voice communication through HomeKit. Though the timeline is uncertain, contributions and testing are always appreciated.

Support
-------

For any questions or issues, open an issue on the repository.

License
-------

This open-source project is under the [Apache 2 License](https://www.apache.org/licenses/LICENSE-2.0).
