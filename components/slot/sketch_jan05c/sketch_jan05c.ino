#include <Wire.h>

int ledRed = 2;
int ledBlue = 3;
int ledGreen = 4;

int ledArray[3] {ledGreen, ledBlue, ledRed};

#define adress 0x05
unsigned ledConfig[3];

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  Serial.begin(9600);
  Wire.begin(adress);

  Wire.onReceive(receiveData);

  Serial.println("Ready");
}

void loop() {
  if (Wire.available()) {
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed, HIGH);
  } else {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledBlue, HIGH);
  }
}

void receiveData(int byteCount) {
  while (Wire.available()) {
    
    Serial.println(byteCount);
    for (int i = 0; i<byteCount; i++) {
      ledConfig[i] = Wire.read();
    }
    
    Serial.print("received: ");
    Serial.print(ledConfig[0]);
    Serial.print(ledConfig[1]);
    Serial.println(ledConfig[2]);

    applyConfig(ledConfig);
  }
}

void applyConfig(int ledConfig[]) {
  for (int i=0; i<sizeof(ledArray); i++) {
    digitalWrite(ledArray[i], ledConfig[i]);
  }
}
