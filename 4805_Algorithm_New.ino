#include <EZDist.h>

#define LFS_R A1//4
#define LFS_M A2//6
#define LFS_L A0//5

#define IRDetect A3

#define TrigPinLeft 28
#define EchoPinLeft 30
#define TrigPinRight 32
#define EchoPinRight 34

EZDist UltraLeft(TrigPinLeft, EchoPinLeft);
EZDist UltraRight(TrigPinRight, EchoPinRight);

volatile int counter = 0;
volatile int input;
int IRState;
int IRFlag = 0;
int DistLeft = 450;
int DistRight = 450;
//distance to avoid obstacle with ultrasonic
const int DistMin = 30;
const int DistStop = 20;
int Turn = 0;
int x;

void setup() {
  Serial.begin(9600);
  pinMode(LFS_L, INPUT);
  pinMode(LFS_M, INPUT);
  pinMode(LFS_R, INPUT);
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(IRDetect, INPUT);
  wdt_disable(); 
  delay(3000);  
  wdt_enable(WDTO_2S); 

}

void loop() {
  wdt_reset(); 
  handle_ultrasonic();

  if (analogRead(LFS_M) > 850 || analogRead(LFS_R) > 850 || analogRead(LFS_L) > 850) {
    if (analogRead(LFS_L) > 850) {
      Serial.println(analogRead(LFS_L));
      motorBack();
      delay(800);
      motorRight();
      delay(2000);
    }
    else if(analogRead(LFS_R) > 850) {
      Serial.println(analogRead(LFS_R));
      motorBack();
      delay(800);
      motorLeft();
      delay(2000);
    }

    else {
      Serial.println(analogRead(LFS_M));
      motorBack();
      delay(800);
      randomdirection();
      delay(random(1000, 2000));
    }
    // input = counter%2;
    // switch(input) {
    //     case 0: {
    //       motorBack();
    //       delay(1000);
    //       motorRight();
    //       delay(3500);
    //       break;
    //     }
    //     case 1: {
    //       motorBack();
    //       delay(1000);
    //       motorLeft();
    //       delay(3500);
    //       break;
    //     }
    }
    //counter++;


  if (analogRead(IRDetect) < 100) {
    Serial.println(analogRead(IRDetect));
    handle_IRDetect();
    delay(200);
  }

  if((DistLeft <= DistStop) || (DistRight <= DistStop))
  {
    Serial.println("UltraSonic Stop");
    //handle_IRDetect();
    motorRight();
  }
  //If one of our sensors is slightly close to an object
  if((DistLeft <= DistMin) || (DistRight <= DistMin)){  
  
    if ((DistLeft < DistMin ) && (DistRight < DistMin))
    {
      Serial.println("Both UltraSonic detected");
      //motorBack();
      motorRight();   
      delay(300);   
    }
    //Only one ultrasonic detects
    //Turn left or right depending on Turn value
    else if (Turn == 1)
    {
      Serial.println("UltraSonic turn right");
      motorRight();
      delay(300);
    }

    else if (Turn == 0) {
      Serial.println("UltraSonic turn left");
      motorLeft();
      delay(300);
    }
  }

  else {
    motorFwd();
  }
}


void IR_read() {
  //Reading Front Sensor
  IRState = digitalRead(IRDetect);

  //Front Sensor Flag
  if((IRFlag == 0) && (IRState == 1))
  {
    IRFlag = 1;   
  }
  else {
    IRFlag = 0;
  }
}

void handle_ultrasonic() {
  //Read both UltraSonic Sensors
  int Left = UltraLeft.cm();
  int Right = UltraRight.cm();
  
  //Debouncing
  if((Left > 0)) 
  {
    DistLeft = Left;
    Serial.println(digitalRead(DistLeft));
  }
  if((Right > 0))
  {
    DistRight = Right; 
    Serial.println(digitalRead(DistRight));
  }
  //Setting Turn to left or right
  if((DistRight < 25) || (DistLeft < 25) && (DistLeft != DistRight))
  {
    if((DistLeft > DistRight))            
    {
      Turn = 0;        
    }
    else
    {
      Turn = 1;
    }
  }
}
//Right turn
void motorRight() {
  digitalWrite(2, 150);
  digitalWrite(22, HIGH);
  digitalWrite(24, LOW);
}

//Left turn
void motorLeft() {
  digitalWrite(2, 150);
  digitalWrite(22, LOW);
  digitalWrite(24, HIGH);
}
//FWD
void motorFwd() {
  digitalWrite(2, 150);
  digitalWrite(22, HIGH);
  digitalWrite(24, HIGH);
}

//Back 
void motorBack() {
  digitalWrite(2, 150);
  digitalWrite(22, LOW);
  digitalWrite(24, LOW);
}
void stop() {
  analogWrite(2, 0);
}

void snakeRight() {
  motorBack();
  delay(1000);
  motorRight();
  delay(2000);
  motorFwd();
  delay(500);
  motorRight();
  delay(2000);
}

void snakeLeft() {
  motorBack();
  delay(1000);
  motorLeft();
  delay(2000);
  motorFwd();
  delay(500);
  motorLeft();
  delay(2000);
}

void handle_IRDetect() {
  stop();
  delay(200);
  //motorBack();
  //delay(1000);
  randomdirection();
  delay(random(1000, 2000));
}

void randomdirection(){
  x = random(1, 2);
  if (x = 1){
    motorRight();
  }
  else{
    motorLeft();
  }

}







