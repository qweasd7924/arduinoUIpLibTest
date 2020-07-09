// TCP сервер, возвращает полученные данные
#include <SPI.h>
#include <UIPEthernet.h>

// определяем конфигурацию сети
byte mac[] = {0xAE, 0xB2, 0x26, 0xE4, 0x4A, 0x5C}; // MAC-адрес
byte ip[] = {192, 168, 0, 110}; // IP-адрес
byte myDns[] = {192, 168,0, 1}; // адрес DNS-сервера
byte gateway[] = {192, 168, 0, 1}; // адрес сетевого шлюза
byte subnet[] = {255, 255, 255, 0}; // маска подсети

EthernetServer server(2000); // создаем сервер, порт 2000
EthernetClient client; // объект клиент
boolean clientAlreadyConnected= false; // признак клиент уже подключен

void setup() {
    Ethernet.begin(mac, ip, myDns, gateway, subnet); // инициализация контроллера
    server.begin(); // включаем ожидание входящих соединений
    Serial.begin(9600);
    Serial.print("Server address:");
    Serial.println(Ethernet.localIP()); // выводим IP-адрес контроллера
}

String reqStr;
size_t reqSize;
uint8_t* reqBuf;

String respStr;
size_t respSize;
//char* respBuf;
uint8_t* respBuf;


void loop() {


    client = server.available(); // ожидаем объект клиент
    if (client) {
        // есть данные от клиента
        if (clientAlreadyConnected == false) {
            // сообщение о подключении
            Serial.println("Client connected");
            client.println("Server ready"); // ответ клиенту
            clientAlreadyConnected= true;
        }

        while((reqSize = client.available()) > 0)
        {
            reqBuf = (uint8_t*)malloc(reqSize);
            reqSize = client.read(reqBuf, reqSize);
//            client.write(reqBuf,reqSize);
            reqStr = (char*)reqBuf;
            reqStr = reqStr.substring(0, reqSize);
            free(reqBuf);
        }
        Serial.println(reqStr);


        respStr = "a1b2c3d";

//        uint8_t dataArray[dataString.length()];
//        dataString.toCharArray(dataArray, dataString.length())

        uint8_t dataArray[respStr.length()];
        respStr.getBytes(dataArray, respStr.length());

//        respStr.getBytes(respBuf, respStr.length());
        client.write(dataArray, respStr.length());
        free(respBuf);

//        while(client.available() > 0) {
//            char chr = client.read(); // чтение символа
//            server.write(chr); // передача клиенту
//            Serial.write(chr);
//        }
    }
}