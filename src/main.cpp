// TCP сервер, возвращает полученные данные
//#include <SPI.h>
#include <UIPEthernet.h>

//--------------------------Ethernet----------------------

// определяем конфигурацию сети
byte mac[] = {0xAE, 0xB2, 0x26, 0xE4, 0x4A, 0x5D}; // MAC-адрес
byte ip[] = {192, 168, 0, 150}; // IP-адрес
byte myDns[] = {192, 168, 19, 1}; // адрес DNS-сервера
byte gateway[] = {192, 168, 19, 1}; // адрес сетевого шлюза
byte subnet[] = {255, 255, 255, 0}; // маска подсети

EthernetServer server(2000); // создаем сервер, порт 2000
EthernetClient client; // объект клиент
boolean clientAlreadyConnected = false; // признак клиент уже подключен
size_t size;

String req;
String resp = "-123-\n";
int respLen = 0;


void setup() {
    Ethernet.begin(mac, ip); // инициализация контроллера
//    Ethernet.begin(mac, ip, myDns, gateway, subnet); // инициализация контроллера
    server.begin(); // включаем ожидание входящих соединений
    Serial.begin(9600);
    Serial.print("Server address:");
    Serial.println(Ethernet.localIP()); // выводим IP-адрес контроллера
}

bool isConnectd = false;

void loop() {
    //  if (client.connected()) {
    //    Serial.println("!!!Connected!!!");
    //  }
    client = server.available(); // ожидаем объект клиент


    if (client) {
        Serial.println("---message received---");
        while ((size = client.available()) > 0) {
            //      Serial.println(size);
            uint8_t *msg = (uint8_t *) malloc(size);
            size = client.read(msg, size);
            req = (char *) msg;
            req = req.substring(0, size);
            Serial.println(req);
            Serial.println(size);
//      client.write(msg, size);
            //            client.println("123");
            //      server.println("321");
            client.println(req + " received");
            //      Serial.println("\n---Start message---");
            //      Serial.println(req + " is String");
            //      client.print(req + " recieved");
            //      resp = "-123-\n";
            //      respLen = resp.length();
            //
            //      if (req.substring(0, 9) == "get state") {
            //        Serial.println("Ethernet state here");
            //        client.print("Ethernet state work fine");
            //      } else if (req.substring(0, 4) == "move") {
            //        Serial.println("Try to move");
            //        client.print("Try to move");
            //      }
            free(msg);
        }
        Serial.println("---end message---");
//        client.stop();
    }
}