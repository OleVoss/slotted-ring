int ledPin = 14;
int inPin = 15;
int val = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inPin, INPUT);
}

void loop() {
  val = digitalRead(inPin);
  digitalWrite(ledPin, val);
}
