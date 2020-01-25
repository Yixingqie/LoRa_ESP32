//By Yixing Qie
#include <Wire.h> 
#include "SSD1306.h" //screen library
#include <SPI.h>
#include <LoRa.h>

SSD1306 display(0x3c, 4, 15);

#define SS 18
#define RST 14
#define DI0 26

#define BAND 434500000.00
#define spreadingFactor 9 //bandwith spread
#define SignalBandwidth 31.25E3


void setup() {
  pinMode(16,OUTPUT);
  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH);

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  Serial.begin(115200);
  delay(1000);
  display.setFont(ArialMT_Plain_16);
  Serial.println("LoRa Receiver");
  display.drawString(5,5,"LoRa Receiver");
  display.display();
  SPI.begin(5,19,27,18); //configure oled
  LoRa.setPins(SS,RST,DI0); //configure esp32 lora
}

void loop() {
  int packetSize = LoRa.parsePacket();
    
    // read packets from other transmitter
    while (LoRa.available()) {
      char data = (char)LoRa.read();
    //  Serial.print(data); //print to serial monitor
      display.print(data);
      display.display(); //pushes to the screen
    }
  }
