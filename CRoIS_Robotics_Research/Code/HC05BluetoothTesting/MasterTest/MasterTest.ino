#define ledPin 9
int state = 0;
int potValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial1.begin(230400); // Default communication rate of the Bluetooth module
  Serial.begin(230400);
}
void loop() {
 if(Serial1.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial1.read(); // Reads the data from the serial port
    Serial.println(state);
 }
 // Controlling the LED
 if (state == '1') {
  digitalWrite(ledPin, HIGH); // LED ON
  state = 0;
 }
 else if (state == '0') {
  digitalWrite(ledPin, LOW); // LED ON
  state = 0;
 }

 potValue = analogRead(A0);
 int potValueMapped = map(potValue, 0, 1023, 0, 179);
 Serial1.write(potValueMapped); // Sends potValue to servo motor
 delay(10);
}
