#include <EZDist.h>

#define TrigPinLeft 22
#define EchoPinLeft 23
#define TrigPinRight 24
#define EchoPinRight 25

EZDist UltraLeft(TrigPinLeft, EchoPinLeft);
EZDist UltraRight(TrigPinRight, EchoPinRight);

void setup() {
  Serial.begin(9600);
}

void loop() {
  USonicTest();
}

void USonicTest()
{
  DistRight = UltraRight.cm();  
  DistLeft = UltraLeft.cm();
  Serial.print("Left Sensor: ");
  Serial.println(DistLeft);
  Serial.print("Right Sensor: ");
  Serial.println(DistRight);
  delay(2000);
}
