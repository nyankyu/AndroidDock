#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define LED 13

AndroidAccessory acc (
  "kobitokaba",
  "Holder",
  "Arduino MEGA ADK R3",
  "1.0",
  "http://www.android.com",
  "0000000012345678"
);

void setup();
void loop();

void init_led() {
  pinMode(LED, OUTPUT);
}

void setup() {
  Serial.begin(115200);
  Serial.print("\r\nStart");

  init_led();

  acc.powerOn();
}

void loop() {
    byte msg[2];
    byte led;
  
    if (acc.isConnected()) {
        int len = acc.read(msg, sizeof(msg), 1);
  
        if (len > 0) {
            if (msg[0] == 0x1) {
                if(msg[1] == 0x1) {
                    digitalWrite(LED, HIGH);
                    msg[0] = 0x1;
                    msg[1] = 0x1;
                    acc.write(msg, 2);
                } else {
                    digitalWrite(LED, LOW);
                    msg[0] = 0x1;
                    msg[1] = 0x2;
                    acc.write(msg, 2);
                }
            }
        }
    } else {
        digitalWrite(LED, LOW);
  }
  
    delay(10);
}


