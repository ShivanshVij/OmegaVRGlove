String readSerial;

void setup() {
  // start serial for output at baud rate 9600
  Serial1.begin(9600);
}

void loop() {
  delay(100);
  // wait until there's serial data available
  if (Serial1.available() > 0) {
    readSerial = Serial1.readString();
    if(sizeof(readSerial) > 0){
      Serial.println(readSerial);
      Serial1.println(readSerial);
    }
  }
}
