////// This is a demo of the RBBB running as webserver with the EtherCard
////// 2010-05-28 <jc@wippler.nl>
//////
////// License: GPLv2
////
////#include <EtherCard.h>
////
////// ethernet interface mac address, must be unique on the LAN
////static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
////static byte myip[] = { 192,168,0,110 };
////
////byte Ethernet::buffer[500];
////BufferFiller bfill;
////
////static word homePage() {
////    long t = millis() / 1000;
////    word h = t / 3600;
////    byte m = (t / 60) % 60;
////    byte s = t % 60;
////    bfill = ether.tcpOffset();
////    bfill.emit_p(PSTR(
////                         "HTTP/1.0 200 OK\r\n"
////                         "Content-Type: text/html\r\n"
////                         "Pragma: no-cache\r\n"
////                         "\r\n"
////                         "<meta http-equiv='refresh' content='1'/>"
////                         "<title>RBBB server</title>"
////                         "<h1>$D$D:$D$D:$D$D</h1>"),
////                 h/10, h%10, m/10, m%10, s/10, s%10);
////    return bfill.position();
////}
////
////void setup () {
////    Serial.begin(9600);
////    Serial.println(F("\n[RBBB Server]"));
////    // Change 'SS' to your Slave Select pin, if you arn't using the default pin
////    if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
////        Serial.println(F("Failed to access Ethernet controller"));
////    ether.staticSetup(myip);
////}
////
////void loop () {
////    word len = ether.packetReceive();
////    word pos = ether.packetLoop(len);
////
////    if (pos)  // check if valid tcp data is received
//////        Serial.println(pos);
//////        Serial.println(len);
////        ether.httpServerReply(homePage()); // send web page data
////}
//
////#include <UIPEthernet.h> // Used for Ethernet
////
////// **** ETHERNET SETTING ****
////byte mac[] = { 0x54, 0x34, 0x41, 0x30, 0x30, 0x31 };
////IPAddress ip(192, 168, 0, 110);
////EthernetServer server(2000);
////
////void setup() {
////    Serial.begin(9600);
////
////    // start the Ethernet connection and the server:
////    Ethernet.begin(mac, ip);
////    server.begin();
////
////    Serial.print("IP Address: ");
////    Serial.println(Ethernet.localIP());
////}
////
////void loop() {
////    // listen for incoming clients
////    EthernetClient client = server.available();
////
////    if (client)
////    {
////        Serial.println("-> New Connection");
////
////        // an http request ends with a blank line
////        boolean currentLineIsBlank = true;
////
////        while (client.connected())
////        {
////            if (client.available())
////            {
////                char c = client.read();
////                Serial.print(c);
////                // if you've gotten to the end of the line (received a newline
////                // character) and the line is blank, the http request has ended,
////                // so you can send a reply
////                if (c == '\n' && currentLineIsBlank)
////                {
////                    Serial.print("respond");
////                    client.println("<html><title>Hello World!</title><body><h3>Hello World!</h3></body>");
////                    break;
////                }
////
////                if (c == '\n') {
////                    // you're starting a new line
////                    currentLineIsBlank = true;
////                }
////                else if (c != '\r')
////                {
////                    // you've gotten a character on the current line
////                    currentLineIsBlank = false;
////                }
////            }
////            Serial.print("respond after avalible");
////            client.println("<html><title>Hello World!</title><body><h3>Hello World!</h3></body>");
//////            Serial.println("wait");
////        }
////
////        // give the web browser time to receive the data
////        delay(10);
////
////        // close the connection:
////        client.stop();
////        Serial.println("   Disconnected\n");
////    }
////}
//
///****************************************************************************************************************************
//   HelloServer.ino - Dead simple web-server for Ethernet shields
//   EthernetWebServer is a library for the Ethernet shields to run WebServer
//   Forked and modified from ESP8266 https://github.com/esp8266/Arduino/releases
//   Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer
//   Licensed under MIT license
//   Version: 1.0.9
//   Original author:
//   @file       Esp8266WebServer.h
//   @author     Ivan Grokhotkov
//   Version Modified By   Date      Comments
//   ------- -----------  ---------- -----------
//    1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc to support Ethernetx libraries
//    1.0.1   K Hoang      20/02/2020 Add support to lambda functions
//    1.0.2   K Hoang      20/02/2020 Add support to UIPEthernet library for ENC28J60
//    1.0.3   K Hoang      23/02/2020 Add support to SAM DUE / SAMD21 boards
//    1.0.4   K Hoang      16/04/2020 Add support to SAMD51 boards
//    1.0.5   K Hoang      24/04/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense,
//                                    Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B30_ublox, etc.
//                                    More Custom Ethernet libraries supported such as Ethernet2, Ethernet3, EthernetLarge
//    1.0.6   K Hoang      27/04/2020 Add W5x00 support to ESP32/ESP8266 boards
//    1.0.7   K Hoang      30/04/2020 Add ENC28J60 support to ESP32/ESP8266 boards
//    1.0.8   K Hoang      12/05/2020 Fix W5x00 support for ESP8266 boards.
//    1.0.9   K Hoang      15/05/2020 Add EthernetWrapper.h for easier W5x00 support as well as more Ethernet libs in the future.
// *****************************************************************************************************************************/
///*
//    The Arduino board communicates with the shield using the SPI bus. This is on digital pins 11, 12, and 13 on the Uno
//    and pins 50, 51, and 52 on the Mega. On both boards, pin 10 is used as SS. On the Mega, the hardware SS pin, 53,
//    is not used to select the Ethernet controller chip, but it must be kept as an output or the SPI interface won't work.
//*/
//
//#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
//      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
//      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
//      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
//      || defined(__SAMD51G19A__) || defined(__SAMD21G18A__) )
//#if defined(ETHERNET_USE_SAMD)
//#undef ETHERNET_USE_SAMD
//#endif
//#define ETHERNET_USE_SAMD      true
//#endif
//
//#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
//        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
//        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) )
//#if defined(ETHERNET_USE_NRF528XX)
//#undef ETHERNET_USE_NRF528XX
//#endif
//#define ETHERNET_USE_NRF528XX      true
//
////This is workaround for NINA_B302_ublox
//// Change the pin
//#define ENC28J60_CONTROL_CS         10
//#define ENC28J60_USE_SPILIB         true
//#warning Use nRF52 with SPI pins defined
//
//#endif
//
//#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
//#if defined(ETHERNET_USE_SAM_DUE)
//#undef ETHERNET_USE_SAM_DUE
//#endif
//#define ETHERNET_USE_SAM_DUE      true
//#endif
//
//#if defined(ETHERNET_USE_SAMD)
//// For SAMD
//
//#if defined(ARDUINO_SAMD_ZERO)
//#define BOARD_TYPE      "SAMD Zero"
//#elif defined(ARDUINO_SAMD_MKR1000)
//#define BOARD_TYPE      "SAMD MKR1000"
//#elif defined(ARDUINO_SAMD_MKRWIFI1010)
//#define BOARD_TYPE      "SAMD MKRWIFI1010"
//#elif defined(ARDUINO_SAMD_NANO_33_IOT)
//#define BOARD_TYPE      "SAMD NANO_33_IOT"
//#elif defined(ARDUINO_SAMD_MKRFox1200)
//#define BOARD_TYPE      "SAMD MKRFox1200"
//#elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
//#define BOARD_TYPE      "SAMD MKRWAN13X0"
//#elif defined(ARDUINO_SAMD_MKRGSM1400)
//#define BOARD_TYPE      "SAMD MKRGSM1400"
//#elif defined(ARDUINO_SAMD_MKRNB1500)
//#define BOARD_TYPE      "SAMD MKRNB1500"
//#elif defined(ARDUINO_SAMD_MKRVIDOR4000)
//#define BOARD_TYPE      "SAMD MKRVIDOR4000"
//#elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
//#define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
//#elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
//#define BOARD_TYPE      "SAMD ADAFRUIT_ITSYBITSY_M4_EXPRESS"
//#elif defined(__SAMD21E18A__)
//#define BOARD_TYPE      "SAMD21E18A"
//#elif defined(__SAMD21G18A__)
//#define BOARD_TYPE      "SAMD21G18A"
//#elif defined(__SAMD51G19A__)
//#define BOARD_TYPE      "SAMD51G19A"
//#elif defined(__SAMD51J19A__)
//#define BOARD_TYPE      "SAMD51J19A"
//#elif defined(__SAMD51J20A__)
//#define BOARD_TYPE      "SAMD51J20A"
//#elif defined(__SAMD51__)
//#define BOARD_TYPE      "SAMD51"
//#else
//#define BOARD_TYPE      "SAMD Unknown"
//#endif
//
//#elif (ETHERNET_USE_SAM_DUE)
//#define BOARD_TYPE      "SAM DUE"
//
//#elif (ETHERNET_USE_NRF528XX)
//
//#if defined(NRF52840_FEATHER)
//#define BOARD_TYPE      "NRF52840_FEATHER"
//#elif defined(NRF52832_FEATHER)
//#define BOARD_TYPE      "NRF52832_FEATHER"
//#elif defined(NRF52840_FEATHER_SENSE)
//#define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
//#elif defined(NRF52840_ITSYBITSY)
//#define BOARD_TYPE      "NRF52840_ITSYBITSY"
//#elif defined(NRF52840_CIRCUITPLAY)
//#define BOARD_TYPE      "NRF52840_CIRCUITPLAY"
//#elif defined(NRF52840_CLUE)
//#define BOARD_TYPE      "NRF52840_CLUE"
//#elif defined(NRF52840_METRO)
//#define BOARD_TYPE      "NRF52840_METRO"
//#elif defined(NRF52840_PCA10056)
//#define BOARD_TYPE      "NRF52840_PCA10056"
//#elif defined(NINA_B302_ublox)
//#define BOARD_TYPE      "NINA_B302_ublox"
//#elif defined(PARTICLE_XENON)
//#define BOARD_TYPE      "PARTICLE_XENON"
//#elif defined(ARDUINO_NRF52_ADAFRUIT)
//#define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
//#else
//#define BOARD_TYPE      "nRF52 Unknown"
//#endif
//
//#elif ( defined(CORE_TEENSY) )
//// For Teensy 4.0
//#if defined(__IMXRT1062__)
//#define BOARD_TYPE      "TEENSY 4.0"
//#elif ( defined(__MKL26Z64__) || defined(ARDUINO_ARCH_AVR) )
//#define BOARD_TYPE      "TEENSY LC or 2.0"
//#else
//#define BOARD_TYPE      "TEENSY 3.X"
//#endif
//
//#elif ( defined(ESP8266) )
//// For ESP8266
//#warning Use ESP8266 architecture
//#define ETHERNET_USE_ESP8266
//#define BOARD_TYPE      "ESP8266"
//
//#elif ( defined(ESP32) )
//// For ESP32
//#warning Use ESP32 architecture
//#define ETHERNET_USE_ESP32
//#define BOARD_TYPE      "ESP32"
//
//#define W5500_RST_PORT   21
//
//#else
//// For Mega
//#define BOARD_TYPE      "AVR Mega"
//#endif
//
//#include <SPI.h>
//
//#define USE_ETHERNET_WRAPPER    true
////#define USE_ETHERNET_WRAPPER    false
//
//// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
//// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)
//
//#define USE_UIP_ETHERNET   true
////#define USE_UIP_ETHERNET   false
//
////#define USE_CUSTOM_ETHERNET     true
//
//// Note: To rename ESP628266 Ethernet lib files to Ethernet_ESP8266.h and Ethernet_ESP8266.cpp
//// In order to USE_ETHERNET_ESP8266
//#if ( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )
//
//// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
////#define USE_THIS_SS_PIN   22  //21  //5 //4 //2 //15
//
//// Only one if the following to be true
//#define USE_ETHERNET2         false //true
//#define USE_ETHERNET3         false //true
//#define USE_ETHERNET_LARGE    false //true
//#define USE_ETHERNET_ESP8266  false //true
//
//#if !USE_ETHERNET_WRAPPER
//
//#if ( USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE || USE_ETHERNET_ESP8266 )
//  #ifdef USE_CUSTOM_ETHERNET
//    #undef USE_CUSTOM_ETHERNET
//    #define USE_CUSTOM_ETHERNET   true
//  #endif
//#endif
//
//#if USE_ETHERNET3
//#include "Ethernet3.h"
//#warning Use Ethernet3 lib
//#elif USE_ETHERNET2
//#include "Ethernet2.h"
//#warning Use Ethernet2 lib
//#elif USE_ETHERNET_LARGE
//#include "EthernetLarge.h"
//#warning Use EthernetLarge lib
//#elif USE_ETHERNET_ESP8266
//#include "Ethernet_ESP8266.h"
//#warning Use Ethernet_ESP8266 lib
//#elif USE_CUSTOM_ETHERNET
//#include "Ethernet_XYZ.h"
//#warning Use Custom Ethernet library from EthernetWrapper. You must include a library here or error.
//#else
//#define USE_ETHERNET          true
//#include "Ethernet.h"
//#warning Use Ethernet lib
//#endif
//
//// Ethernet_Shield_W5200, EtherCard, EtherSia not supported
//// Select just 1 of the following #include if uncomment #define USE_CUSTOM_ETHERNET
//// Otherwise, standard Ethernet library will be used for W5x00
//
//#endif    //#if !USE_UIP_ETHERNET
//#endif    //USE_ETHERNET_WRAPPER
//
//#include <EthernetWebServer.h>
//
//// Enter a MAC address and IP address for your controller below.
//
//// Enter a MAC address and IP address for your controller below.
//#define NUMBER_OF_MAC      20
//
//byte mac[][NUMBER_OF_MAC] =
//        {
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
//
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
//                { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
//        };
//
//// Select the IP address according to your local network
//IPAddress ip(192, 168, 0, 110);
//
//EthernetWebServer server(2000);
//
//const int led = 13;
//
//void handleRoot()
//{
//    String html = "Hello from HelloServer running on " + String(BOARD_TYPE);
//
//    server.send(200, "text/plain", html);
//}
//
//void handleNotFound()
//{
//    String message = "File Not Found\n\n";
//    message += "URI: ";
//    message += server.uri();
//    message += "\nMethod: ";
//    message += (server.method() == HTTP_GET) ? "GET" : "POST";
//    message += "\nArguments: ";
//    message += server.args();
//    message += "\n";
//    for (uint8_t i = 0; i < server.args(); i++)
//    {
//        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
//    }
//    server.send(404, "text/plain", message);
//    digitalWrite(led, 0);
//}
//
//void setup(void)
//{
//    // Open serial communications and wait for port to open:
//    Serial.begin(9600);
//    while (!Serial);
//
//    //delay(1000);
//    Serial.println("\nStarting HelloServer on " + String(BOARD_TYPE));
//
//#if USE_ETHERNET_WRAPPER
//
//    EthernetInit();
//
//#else
//
//    #if USE_ETHERNET
//      LOGWARN(F("=========== USE_ETHERNET ==========="));
//    #elif USE_ETHERNET2
//      LOGWARN(F("=========== USE_ETHERNET2 ==========="));
//    #elif USE_ETHERNET3
//      LOGWARN(F("=========== USE_ETHERNET3 ==========="));
//    #elif USE_ETHERNET_LARGE
//      LOGWARN(F("=========== USE_ETHERNET_LARGE ==========="));
//    #elif USE_ETHERNET_ESP8266
//      LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
//    #else
//      LOGWARN(F("========================="));
//    #endif
//
//      LOGWARN(F("Default SPI pinout:"));
//      LOGWARN1(F("MOSI:"), MOSI);
//      LOGWARN1(F("MISO:"), MISO);
//      LOGWARN1(F("SCK:"),  SCK);
//      LOGWARN1(F("SS:"),   SS);
//      LOGWARN(F("========================="));
//
//    #if defined(ESP8266)
//      // For ESP8266, change for other boards if necessary
//      #ifndef USE_THIS_SS_PIN
//        #define USE_THIS_SS_PIN   D2    // For ESP8266
//      #endif
//
//      LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);
//
//      #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 )
//        // For ESP8266
//        // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
//        // Ethernet           0                 X            X            X            X        0
//        // Ethernet2          X                 X            X            X            X        0
//        // Ethernet3          X                 X            X            X            X        0
//        // EthernetLarge      X                 X            X            X            X        0
//        // Ethernet_ESP8266   0                 0            0            0            0        0
//        // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
//        // Must use library patch for Ethernet, EthernetLarge libraries
//        //Ethernet.setCsPin (USE_THIS_SS_PIN);
//        Ethernet.init (USE_THIS_SS_PIN);
//
//      #elif USE_ETHERNET3
//        // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
//        #ifndef ETHERNET3_MAX_SOCK_NUM
//          #define ETHERNET3_MAX_SOCK_NUM      4
//        #endif
//
//        Ethernet.setCsPin (USE_THIS_SS_PIN);
//        Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
//
//      #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
//
//    #elif defined(ESP32)
//
//      // You can use Ethernet.init(pin) to configure the CS pin
//      //Ethernet.init(10);  // Most Arduino shields
//      //Ethernet.init(5);   // MKR ETH shield
//      //Ethernet.init(0);   // Teensy 2.0
//      //Ethernet.init(20);  // Teensy++ 2.0
//      //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
//      //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet
//
//      #ifndef USE_THIS_SS_PIN
//        #define USE_THIS_SS_PIN   22    // For ESP32
//      #endif
//
//      LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);
//
//      // For other boards, to change if necessary
//      #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 )
//        // Must use library patch for Ethernet, EthernetLarge libraries
//        // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
//        // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3
//
//        //Ethernet.setCsPin (USE_THIS_SS_PIN);
//        Ethernet.init (USE_THIS_SS_PIN);
//
//      #elif USE_ETHERNET3
//        // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
//        #ifndef ETHERNET3_MAX_SOCK_NUM
//          #define ETHERNET3_MAX_SOCK_NUM      4
//        #endif
//
//        Ethernet.setCsPin (USE_THIS_SS_PIN);
//        Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
//
//      #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
//
//    #else   //defined(ESP8266)
//      // unknown board, do nothing, use default SS = 10
//      #ifndef USE_THIS_SS_PIN
//        #define USE_THIS_SS_PIN   10    // For other boards
//      #endif
//
//      LOGWARN1(F("Unknown board setCsPin:"), USE_THIS_SS_PIN);
//
//      // For other boards, to change if necessary
//      #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 )
//        // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
//
//        Ethernet.init (USE_THIS_SS_PIN);
//
//      #elif USE_ETHERNET3
//        // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
//        #ifndef ETHERNET3_MAX_SOCK_NUM
//          #define ETHERNET3_MAX_SOCK_NUM      4
//        #endif
//
//        Ethernet.setCsPin (USE_THIS_SS_PIN);
//        Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
//
//      #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
//
//    #endif    //defined(ESP8266)
//
//#endif  //USE_ETHERNET_WRAPPER
//
//    // start the ethernet connection and the server:
//    // Use Static IP
//    //Ethernet.begin(mac, ip);
//    // Use DHCP dynamic IP and random mac
//    srand(1);
//    uint16_t index = rand() % NUMBER_OF_MAC;
//    //uint16_t index = random(NUMBER_OF_MAC);
//
//    Ethernet.begin(mac[index]);
//
//    server.on("/", handleRoot);
//
//    server.on("/inline", []() {
//        server.send(200, "text/plain", "This works as well");
//    });
//
//    server.onNotFound(handleNotFound);
//
//    server.begin();
//
//    Serial.print(F("HTTP EthernetWebServer is @ IP : "));
//    Serial.println(Ethernet.localIP());
//}
//
//void loop(void)
//{
//    server.handleClient();
//}

// WEB сервер, передает клиенту текстовую строку
#include <SPI.h>
#include <UIPEthernet.h>

// определяем конфигурацию сети
byte mac[] = {0xAE, 0xB2, 0x26, 0xE4, 0x4A, 0x5C}; // MAC-адрес
byte ip[] = {192, 168, 0, 110}; // IP-адрес

EthernetServer server(2000); // создаем сервер, порт 80
EthernetClient client; // объект клиент

boolean flagEmptyLine = true; // признак строка пустая
char tempChar;

void setup() {
    Ethernet.begin(mac, ip); // инициализация контроллера
    server.begin(); // включаем ожидание входящих соединений
    Serial.begin(9600);
    Serial.print("Server address:");
    Serial.println(Ethernet.localIP()); // выводим IP-адрес контроллера
    Serial.print("");
}

void loop() {
    client = server.available(); // ожидаем объект клиент
    if (client) {
        flagEmptyLine = true;
        Serial.println("New request from client:");

        while (client.connected()) {
            if (client.available()) {
                tempChar = client.read();
                Serial.write(tempChar);

                if (tempChar == '\n' && flagEmptyLine) {
                    // пустая строка, ответ клиенту
                    client.println("HTTP/1.1 200 OK"); // стартовая строка
                    client.println("Content-Type: text/html; charset=utf-8"); // тело передается в коде HTML, кодировка UTF-8
                    client.println("Connection: close"); // закрыть сессию после ответа
                    client.println(); // пустая строка отделяет тело сообщения
                    client.println("<!DOCTYPE HTML>"); // тело сообщения
                    client.println("<html>");
                    client.println("<H1> Первый WEB-сервер</H1>"); // выбираем крупный шрифт
                    client.println("</html>");
                    break;
                }
                if (tempChar == '\n') {
                    // новая строка
                    flagEmptyLine = true;
                }
                else if (tempChar != '\r') {
                    // в строке хотя бы один символ
                    flagEmptyLine = false;
                }
            }
        }
        delay(1);
        // разрываем соединение
        client.stop();
        Serial.println("Break");
    }
}