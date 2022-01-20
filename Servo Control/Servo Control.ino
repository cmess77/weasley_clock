#define BLYNK_PRINT Serial
//#define BLYNK_TEMPLATE_ID
//#define BLYNK_DEVICE_NAME "Arduino MKR1000"
//#define BLYNK_AUTH_TOKEN

#include <SPI.h>
#include <WiFi101.h>
#include <BlynkSimpleMKR1000.h>
#include <ArduinoMotorCarrier.h>

//testing testing 123

//char ssid[] = ssid here
//char pass[] = password here


void moveServo(int state) {
  if (state == 1) {
    servo1.setAngle(0);
  }
  else {
    servo1.setAngle(180);
  }
}


BLYNK_WRITE(V1) {
  moveServo(param.asInt());
}


void setup() {
  Serial.begin(9600);
  if (controller.begin()) {
    Serial.print("MKR Motor Carrier connected, firmware version ");
    Serial.println(controller.getFWVersion());
  }
  else {
    Serial.println("Couldn't connect to Motor Carrier.");
    while(1);
  }
  
  Serial.println("rebooting...");
  controller.reboot();
  delay(500);
  servo1.setAngle(0);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  controller.ping();
}


void loop() {
  Blynk.run();
  
  controller.ping();
}
