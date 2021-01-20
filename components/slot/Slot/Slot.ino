#include <Wire.h>
#include <LiquidCrystal.h>

// led pin config
const int belegtPin = 2, monitorPin = 3;
const int antwortPins[2] {4, 5};

// lcd config
const int rs = 13, en = 12;
const int d4 = 14, d5 = 15, d6 = 16, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// i2c config
#define adress 0x05
unsigned configArray[6];


// config struct
struct CONFIG {
  int belegt;
  int monitor;
  int quelle;
  int ziel;
  int block;
  int antwort;
};

// antwort config arrays
const int antwortLed1[4] {0, 1, 0, 1};
const int antwortLed2[4] {0, 0, 1, 1};

// initialize config
CONFIG config;

void setup() {
  Serial.begin(9600); // debug display
  Serial.println("Starting setup...");
  
  // LED setup
  pinMode(belegtPin, OUTPUT);
  pinMode(monitorPin, OUTPUT);
  pinMode(antwortPins[0], OUTPUT);
  pinMode(antwortPins[1], OUTPUT);

  // LCD setup
  lcd.begin(16, 2);
  lcdPrintConfig(0, 0, 0);
  
  // I2C
  Wire.begin(adress);
  Wire.onReceive(receiveConfig);

  Serial.println("...done");
}

void loop() {
  // update frequency
  delay(500);
}

void receiveConfig(int byteCount) {
  // read array from i2c-bus
  while (Wire.available()) {
    Serial.println("Receiving config...");
    for (int i = 0; i<byteCount; i++) {
      configArray[i] = Wire.read();
    }
    Serial.println("...done");
  }
  
  // change config struct
  config.belegt = configArray[0];
  config.monitor = configArray[1];
  config.quelle = configArray[2];
  config.ziel = configArray[3];
  config.block = configArray[4];
  config.antwort = configArray[5];
    
  // apply config
  applyLEDConfig();
  applyLCDConfig();
}

void applyLEDConfig() {
  // belegt led
  digitalWrite(belegtPin, constrain(config.belegt, 0, 1));

  // monitor led
  digitalWrite(monitorPin, constrain(config.monitor, 0, 1));

  // antwort led
  digitalWrite(antwortPins[1], antwortLed1[config.antwort]);
  digitalWrite(antwortPins[0], antwortLed2[config.antwort]);
  
}

void applyLCDConfig() {
  lcdPrintConfig(config.quelle, config.ziel, config.block);
}

void lcdPrintConfig(int sender, int receiver, int blockSize) {
  lcd.setCursor(2, 0);
  lcd.print("sender:");
  lcd.print(sender);
  lcd.setCursor(0, 1);
  lcd.print("receiver:");
  lcd.print(receiver);

  lcdPrintBlock(blockSize);
  
}

void lcdPrintBlock(int blockSize) {
  // clear block section
  for (int r = 0; r<2; r++) {
    lcd.setCursor(11, r);
    for (int b = 0; b<5; b++) {
      lcd.write(254);
    }
  }

  // write block
  for (int r = 0; r<2; r++) {
    lcd.setCursor(11, r);
    for (int b = 0; b<blockSize; b++) {
      lcd.write(255);
    }
  }
}
