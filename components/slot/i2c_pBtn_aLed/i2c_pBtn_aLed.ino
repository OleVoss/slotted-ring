#include <Wire.h>

int ledPin = 14;

#define adress 0x05
int number = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Wire.begin(adress);

  Wire.onReceive(receiveData);

  Serial.println("Ready");
}

void loop() {
  delay(100);
}

void receiveData() {
  while (Wire.available()) {
    number = Wire.read();
    Serial.print("received: ");
    Serial.println(number);

    if (number == 1) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }
}
