#define LFS_R 5//4
#define LFS_M 6//6
#define LFS_L 4//5

void setup() {
  Serial.begin(9600);
  pinMode(LFS_L, INPUT);
  pinMode(LFS_M, INPUT);
  pinMode(LFS_R, INPUT);

}

void loop() {
  lineFollowerTest();

}

void lineFollowerTest() {
  bool left = digitalRead(LFS_L);
  bool middle = digitalRead(LFS_M);
  bool right = digitalRead(LFS_R);

  Serial.print("Left Sensor: ");
  Serial.println(left);

  Serial.print("Middle Sensor: ");
  Serial.println(middle);

  Serial.print("Right Sensor: ");
  Serial.println(right);

  delay(500);
}
