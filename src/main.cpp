//http://mypractic.ru/urok-64-tcp-server-i-klient-na-arduino-biblioteka-uipethernet.html
//http://mypractic.ru/arduino-biblioteka-uipethernet-h-ethernet-h
#include "Arduino.h"
// TCP сервер, возвращает полученные данные
//#include <SPI.h>
#include <UIPEthernet.h>

// определяем конфигурацию сети
byte mac[] = {0xAE, 0xB2, 0x26, 0xE4, 0x4A, 0x5C}; // MAC-адрес
byte ip[] = {192, 168, 0, 110}; // IP-адрес
byte myDns[] = {192, 168, 0, 1}; // адрес DNS-сервера
byte gateway[] = {192, 168, 0, 1}; // адрес сетевого шлюза
byte subnet[] = {255, 255, 255, 0}; // маска подсети

EthernetServer server(2000); // создаем сервер, порт 2000
EthernetClient client; // объект клиент
boolean clientAlreadyConnected= false; // признак клиент уже подключен

#define resPin 8

void setup() {
//    Ethernet.begin(mac, ip); // инициализация контроллера
    Ethernet.begin(mac, ip, myDns, gateway, subnet); // инициализация контроллера
    server.begin(); // включаем ожидание входящих соединений

    Serial.begin(9600);
    while (!Serial);
    Serial.print("Server address:");
    Serial.println(Ethernet.localIP()); // выводим IP-адрес контроллера
}

void loop() {
    client = server.available(); // ожидаем объект клиент
    if (client) {
        // есть данные от клиента
//        if (clientAlreadyConnected == false) {
//            // сообщение о подключении
//            Serial.println("Client connected");
////            delay(100);
//            client.println("Server ready"); // ответ клиенту
//            clientAlreadyConnected= true;
//        }

        while(client.available() > 0) {
            char chr = client.read(); // чтение символа
            server.write(chr); // передача клиенту
            Serial.write(chr);
        }
        Serial.println("\nPack sended");
    }
}