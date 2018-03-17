#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define IN1 8
#define IN2 10

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
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
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
                    digitalWrite(IN1, HIGH);
                    digitalWrite(IN2, LOW);
                    msg[0] = 0x1;
                    msg[1] = 0x1;
                    acc.write(msg, 2);
                } else {
                    digitalWrite(IN1, LOW);
                    digitalWrite(IN2, HIGH);
                    msg[0] = 0x1;
                    msg[1] = 0x2;
                    acc.write(msg, 2);
                }
            }
        }
    } else {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
  }
  
    delay(10);
}


