void setup() {
 Serial.begin(9600);
 pinMode(22, OUTPUT);
 pinMode(24, OUTPUT);
 pinMode(2, OUTPUT);

}

void loop() {
  stop();
  motorFwd();
  delay(3000);

  motorBack();
  delay(3000);

  motorRight();
  delay(3000);

  motorLeft();
  delay(3000);
  stop();

}

//Right turn
void motorRight() {
  digitalWrite(2, 255);
  digitalWrite(22, HIGH);
  digitalWrite(24, LOW);
}

//Left turn
void motorLeft() {
  digitalWrite(2, 255);
  digitalWrite(22, LOW);
  digitalWrite(24, HIGH);
}
//FWD
void motorFwd() {
  digitalWrite(2, 255);
  digitalWrite(22, HIGH);
  digitalWrite(24, HIGH);
}

//Back 
void motorBack() {
  digitalWrite(2, 255);
  digitalWrite(22, LOW);
  digitalWrite(24, LOW);
}
void stop() {
  digitalWrite(2, 0);
}





