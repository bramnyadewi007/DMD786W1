
#include <Arduino.h>
//#include <ESP8266WiFi.h>

#include <DMD786W1.h>
#include <fonts/ElektronMart6x8.h>

extern "C" {
#include <user_interface.h>
}

//#ifdef ESP32
//#include <WiFi.h>
//#include <AsyncTCP.h>
//#elif defined(ESP8266)
//#include <ESP8266WiFi.h>
//#include <ESPAsyncTCP.h>
//#endif
//#include <ESPAsyncWebServer.h>
//
//AsyncWebServer server(80);


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

// Set these to your desired credentials.
const char *APssid = "243AP_P10test";
const char *APpassword = "orange243";

const char* PARAM_MESSAGE = "message";

IPAddress staticIP(19, 19, 19, 19); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 4, 4);  //DNS

//void notFound(AsyncWebServerRequest *request) {
//  request->send(404, "text/plain", "Not found");
//}

//SETUP DMD
#define DISPLAYS_WIDE 32 // Kolom Panel  // versi ini max 32
#define DISPLAYS_HIGH 1 // Baris Panel

DMD786W1 Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);	// Jumlah Panel P10 yang digunakan (KOLOM,BARIS)

void ICACHE_RAM_ATTR refresh() {
  timer0_write(ESP.getCycleCount() + 2800);  //buat diatas 4 panel mending pakai ini
  Disp.refresh();
  //timer0_write(ESP.getCycleCount() + 8000); //buat dibawah 4 panel pakai ini juga bisa
}

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266! Test DMD P10 WiFi");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

//----------------------------------------------------------------------
// SETUP

void setup() {
  delay(800);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Mulai......");
  Serial.println();

  WiFi.disconnect();
  //WiFi.config(staticIP, subnet, gateway, dns);
  //WiFi.config(staticIP, subnet, gateway);
  //WiFi.begin(ssid, password);
  //WiFi.mode(WIFI_STA);

  WiFi.softAP(APssid, APpassword);

  WiFi.softAPConfig(staticIP, staticIP, IPAddress(255, 255, 255, 0));

  IPAddress myIP = staticIP; //WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  //  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
  //    request->send(200, "text/plain", "Hello, world");
  //  });
  //
  //  // Send a GET request to <IP>/get?message=<message>
  //  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest * request) {
  //    String message;
  //    if (request->hasParam(PARAM_MESSAGE)) {
  //      message = request->getParam(PARAM_MESSAGE)->value();
  //    } else {
  //      message = "No message sent";
  //    }
  //    request->send(200, "text/plain", "Hello, GET: " + message);
  //  });
  //
  //  // Send a POST request to <IP>/post with a form field message set to <message>
  //  server.on("/post", HTTP_POST, [](AsyncWebServerRequest * request) {
  //    String message;
  //    if (request->hasParam(PARAM_MESSAGE, true)) {
  //      message = request->getParam(PARAM_MESSAGE, true)->value();
  //    } else {
  //      message = "No message sent";
  //    }
  //    request->send(200, "text/plain", "Hello, POST: " + message);
  //  });
  //
  //  server.onNotFound(notFound);
  //
  //  server.begin();


  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  delay(500);

  // DMDESP Setup
  Disp.setDoubleBuffer(true);
  //Disp.start(""); // Jalankan library DMDESP
  Disp.start(); // Jalankan library DMDESP
  noInterrupts();
  timer0_isr_init();
  timer0_attachInterrupt(refresh);
  timer0_write(ESP.getCycleCount() + 8000);
  interrupts();

  //Disp.setBrightness(100); // Tingkat kecerahan
  Disp.setBrightness(150); // Tingkat kecerahan
  Disp.setFont(ElektronMart6x8); // Tentukan huruf

}



//----------------------------------------------------------------------
// LOOP

void loop() {

  server.handleClient();
  MDNS.update();

  for(int i=0;i<Disp.width()/32;i++){
    Disp.drawText(i*32, 0, +"P-"+String(DISPLAYS_WIDE));// "DMDESP");
  }
  //Disp.drawText(Disp.width() - 32, 0, +"P-"+String(DISPLAYS_WIDE));// "DMDESP");
  
  TeksJalan(8, 50); // Tampilkan teks berjalan TeksJalan(posisi y, kecepatan);

}


//--------------------------
// TAMPILKAN SCROLLING TEKS

static char *teks[] = {"Teks berjalan dengan DMDESP ESPDMD DMDESP  A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 a b c d e f  h i j k l m n o p q r s t u v w x y z 100 90 80 70 60 50 40 30 20 10 0 -- ++ ++ 00 01 02  03 04 05 06 07 08 09 10 >>__<< zA zB zC zD zE zF zG zH zI zJ zK zL zM zN zO zP zQ zR zS zT zU zV zW zX zY zZ z0 z1 z2 z3 z4 z5 z6 z7 z8 z9 z10 z11 z12 z13 z14 z15 z16 z17 z18 z19 z20 z21 z22 z23 z24 z25 z26 z27 z28 z29 z30 z31 z32 z33 z34 z35 z36 z37 z38 z39 z40 z41 z42 z43 z44 z45 z46 z47 z48 z49 z50 z51 z52 z53 z54 z55 z56 z57 z58 z59 z60 z61 z62 z63 z64 z65 z66 z67 z68 z69 z70 z71 z72 z73 z74 z75 z76 z77 z78 z79 z80 z81 z82 z83 z84 z85 z86 z87 z88 z89 z90 z91 z92 z93 z94 z95 z96 z97 z98 z99 z100 Za Zb Zc Zd Ze Zf Zh Zi Zj Zk Zl Zm Zn Zo Zp Zq Zr Zs Zt Zu Zv Zw Zx Zy Zz z100 z90 z80 z70 z60 z50 z40 z30 z20 z10 z0 z-- z++ z++ z00 z01 z02 z03 z04 z05 z06 z07 z08 z09 z10 Z>>__<<Z zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz "};

void TeksJalan(int y, uint32_t kecepatan) {
/*
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(ElektronMart6x8);
  int fullScroll = Disp.textWidth(teks[0]) + width;
  if ((micros() - pM) > kecepatan) {
    pM = micros();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, y, teks[0]);
    Disp.swapBuffersAndCopy();
  }
*/

  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(ElektronMart6x8);
  int fullScroll = Disp.textWidth(teks[0]) + width;
  if ((millis() - pM) > kecepatan) {
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, y, teks[0]);
    Disp.swapBuffersAndCopy();
  }
}
