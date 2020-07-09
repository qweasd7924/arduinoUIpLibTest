#include <UIPEthernet.h>
#include <stdio.h>

#define bufferMax 128
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
        0xDE, 0xAD, 0xBE, 0xEF, 0x11, 0xED
};
IPAddress ip(192, 168, 0, 110);
char post;
char buf[30];
// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(2000);

void setup() {
    pinMode(8, OUTPUT);
    digitalWrite(8,LOW);
    delay(100);
    digitalWrite(8,HIGH);
    delay(100);

    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    // start the Ethernet connection and the server:
    Ethernet.begin(mac, ip);
    server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
}
void loop() {
    // listen for incoming clients
    EthernetClient client = server.available();
    if (client) {
        Serial.println("new client");
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        String buffer = String("");
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                // if you've gotten to the end of the line (received a newline
                // character) and the line is blank, the http request has ended,
                // so you can send a reply
                if (c == '\n' && currentLineIsBlank) {
                    Serial.println("1111111111111111111111111111111111111111111");
//                    client.println('eee\n');
                    while(client.available()) {      //Обработка запроса POST(находится после пустой строки заголовка)
                        post = client.read();
                        if (buffer.length() <= bufferMax) {
                            buffer += post;
                        }
                    }

//                    if(buffer.indexOf("ron=11361") >= 0) {digitalWrite(3, HIGH);}
//                    if(buffer.indexOf("roff=11360") >= 0) {digitalWrite(3, LOW);}
//
//                    if(buffer.indexOf("gon=11381") >= 0) {digitalWrite(5, HIGH);}
//                    if(buffer.indexOf("goff=11380") >= 0) {digitalWrite(5, LOW);}
//
//                    if(buffer.indexOf("bon=11401") >= 0) {digitalWrite(7, HIGH);}
//                    if(buffer.indexOf("boff=11400") >= 0) {digitalWrite(7, LOW);}
                    Serial.println("send header");

                    client.flush();
                    client.write('1afdsssssssssssssssssss');
                    client.write('1afdsssssssssssssssssss\r\n\r\n');
                    client.println("abc123cba\r\n\r\n");


                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.print("Connection: close\r\n\r\n");  // the connection will be closed after completion of the response
                    client.println("<!DOCTYPE HTML>");
                    client.println("<html lang=\"ru\">");
                    client.println("<head>");
                    client.println("<meta charset='Windows-1251'>");
                    client.println("<title>Arduino mega</title>");
                    client.println("</head>");
                    client.println("<body>");
                    client.println("</body>");
//                    client.println("<font size=5 color=blue> Web-server на Arduino MEGA 1280 <br>и контроллере enc28j60 <br>с аутентификацией без защиты</font>");
//                    client.println("<br>");
//                    client.println("<hr>");
//
//                    client.println("<FORM action=\"\" method=\"POST\">");
//                    client.println("<label for='pro'><b>Включить красный светодиод:</b></label><br>");
//                    client.println("<input type='password' name='ron'  id='pro'><br>");
//                    client.println("<label for='prf'><b>Выключить красный светодиод:</b></label><br>");
//                    client.println("<input type='password' name='roff'  id='prf'><br><br>");
//
//                    client.println("<label for='pgo'><b>Включить зеленый светодиод:</b></label><br>");
//                    client.println("<input type='password' name='gon'  id='pgo'><br>");
//                    client.println("<label for='pgf'><b>Выключить зеленый светодиод:</b></label><br>");
//                    client.println("<input type='password' name='goff'  id='pgf'><br><br>");
//
//                    client.println("<label for='pbo'><b>Включить синий светодиод:</b></label><br>");
//                    client.println("<input type='password' name='bon'  id='pbo'><br>");
//                    client.println("<label for='pbf'><b>Выключить синий светодиод:</b></label><br>");
//                    client.println("<input type='password' name='boff'  id='pbf'><br><br>");
//
//                    client.println("<INPUT type=\"submit\" value=\"Ввести\">");
//                    client.println("</FORM>");
//
//                    client.println("<br>");
//
////                    sensors.requestTemperatures();
////                    dtostrf(sensors.getTempCByIndex(0),7,2,buf);
////                    client.print("<font size=4 color=broun>Температура ");
////                    client.print(buf);
////                    client.println(" градусов C</font><br><br>");
////                    if (digitalRead(3)){ client.println("<font size=4 color=red>Красный светодиод ВКЛЮЧЕН</font><br>"); }
////                    else{ client.println("<font size=4 color=red>Красный светодиод ВЫКЛЮЧЕН</font><br>"); }
////                    if (digitalRead(5)){ client.println("<font size=4 color=green>Зеленый светодиод ВКЛЮЧЕН</font><br>");}
////                    else{ client.println("<font size=4 color=green>Зеленый светодиод ВЫКЛЮЧЕН</font><br>"); }
////                    if (digitalRead(7)){client.println("<font size=4 color=blue>Синий светодиод  ВКЛЮЧЕН</font><br>"); }
////                    else{ client.println("<font size=4 color=blue>Синий светодиод  ВЫКЛЮЧЕН</font><br>"); }
//                    client.println("<hr>");
//
//                    client.print("Свободно памяти: ");
////                    client.println(freeRam());
//
//                    Serial.println(buffer);  // Распечатка POST запроса
//
//                    client.println("</body>");
                    client.println("</html>");
                    Serial.println("-------------------");

                    break;
                }
                if (c == '\n') {
                    // you're starting a new line
                    currentLineIsBlank = true;


//                    digitalWrite(8,LOW);
//                    delay(100);
//                    digitalWrite(8,HIGH);
//                    delay(3000);

//                    Serial.print(client.availableForWrite());
//                    Serial.println(" client avelible for write ");
//                    client.write('1afdsssssssssssssssssss');
//                    Serial.println("mes res");
//                    Serial.println("-------");
                } else if (c != '\r') {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        client.stop();
        Serial.println();
        Serial.println("client disconnected");
    }
}