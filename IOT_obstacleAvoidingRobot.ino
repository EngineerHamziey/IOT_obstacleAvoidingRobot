void beginTheSerialMonitor() { Serial.begin(115200);}

#if 0

//Add software serial library so that you can add custom UART, tx, rx
#include <SoftwareSerial.h>
const int btTx = 2, btRx = 3;

SoftwareSerial btModule(btTx, btRx);

//back Wheels
const int
  back_rightMotorForward = 10,
  back_rightMotorBackward = 11,
  back_leftMotorForward = 13,
  back_leftMotorBackward = 12;

//front Wheels
const int
  front_rightMotorForward = 1,
  front_rightMotorBackward = 0,
  front_leftMotorForward = 8,
  front_leftMotorBackward = 7;

void setPinMode() {
  //tell arduino that these pins are OUTPUT
  //for backward motors
  pinMode(back_rightMotorForward, OUTPUT);
  pinMode(back_rightMotorBackward, OUTPUT);
  pinMode(back_leftMotorForward, OUTPUT);
  pinMode(back_leftMotorBackward, OUTPUT);

  //for forward motors
  pinMode(front_rightMotorForward, OUTPUT);
  pinMode(front_rightMotorBackward, OUTPUT);
  pinMode(front_leftMotorForward, OUTPUT);
  pinMode(front_leftMotorBackward, OUTPUT);
}


const char 
    forward = 'f',
    reverse = 'a',
    right = 'r',
    left = 'l',
    servoRight = 's',
    servoLeft = 't',
    servoFront = 'u';


void goForward() {  //motor right and left
  //right wheel, go forward
  digitalWrite(front_rightMotorForward, HIGH);  //GIVE THIS PIN +5V
  digitalWrite(front_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, go forward
  digitalWrite(front_leftMotorForward, HIGH);  //GIVE THIS PIN +5V
  digitalWrite(front_leftMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0

  
  //right wheel, go forward
  digitalWrite(back_rightMotorForward, HIGH);  //GIVE THIS PIN +5V
  digitalWrite(back_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, go forward
  digitalWrite(back_leftMotorForward, HIGH);  //GIVE THIS PIN +5V
  digitalWrite(back_leftMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
}

void goBackward() {  //motor right and left
  //right wheel, go BACKWARD
  digitalWrite(front_rightMotorForward, LOW);
  digitalWrite(front_rightMotorBackward, HIGH);
  //left wheel, go BACKWARD
  digitalWrite(front_leftMotorForward, LOW);
  digitalWrite(front_leftMotorBackward, HIGH);

  
  //right wheel, go BACKWARD
  digitalWrite(back_rightMotorForward, LOW);
  digitalWrite(back_rightMotorBackward, HIGH);
  //left wheel, go BACKWARD
  digitalWrite(back_leftMotorForward, LOW);
  digitalWrite(back_leftMotorBackward, HIGH);
}

void goLeft() {  //RIGHT == FORWARD, LEFT Stop
  //right wheel, go forward
  digitalWrite(front_rightMotorForward, HIGH);  //GIVE THIS PIN +5V
  digitalWrite(front_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, stay still
  digitalWrite(front_leftMotorForward, LOW);
  digitalWrite(front_leftMotorBackward, LOW);

  
  //right wheel, go forward
  digitalWrite(back_rightMotorForward, HIGH);  //GIVE THIS PIN +5V
  digitalWrite(back_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, stay still
  digitalWrite(back_leftMotorForward, LOW);
  digitalWrite(back_leftMotorBackward, LOW);
}

void goRight() {  //RIGHT == stop, LEFT = forward
  //right wheel, go forward
  digitalWrite(front_rightMotorForward, LOW);   //GIVE THIS PIN +5V
  digitalWrite(front_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, stay still
  digitalWrite(front_leftMotorForward, HIGH);
  digitalWrite(front_leftMotorBackward, LOW);

  
  //right wheel, go forward
  digitalWrite(back_rightMotorForward, LOW);   //GIVE THIS PIN +5V
  digitalWrite(back_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, stay still
  digitalWrite(back_leftMotorForward, HIGH);
  digitalWrite(back_leftMotorBackward, LOW);
}

void stopMoving() {  //RIGHT == stop, LEFT = forward
  //right wheel, go forward
  digitalWrite(front_rightMotorForward, LOW);   //GIVE THIS PIN +5V
  digitalWrite(front_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, stay still
  digitalWrite(front_leftMotorForward, LOW);
  digitalWrite(front_leftMotorBackward, LOW);

  
  //right wheel, go forward
  digitalWrite(back_rightMotorForward, LOW);   //GIVE THIS PIN +5V
  digitalWrite(back_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, stay still
  digitalWrite(back_leftMotorForward, LOW);
  digitalWrite(back_leftMotorBackward, LOW);
}


void servoRotateRight() {
  // code to rotate the servo to the right
}

void servoRotateLeft() {
  // code to rotate the servo to the left
}

void servoRotateFront() {
  // code to rotate the servo to the front
}

void setup() {
  setPinMode();
}
    

void IOTDrive(char command) {
  switch (command) {
    case forward:
      goForward();
      break;
    case reverse:
      goBackward();
      break;
    case right:
      goRight();
      break;
    case left:
      goLeft();
      break;
    case servoRight:
      servoRotateRight();
      break;
    case servoLeft:
      servoRotateLeft();
      break;
    case servoFront:
      servoRotateFront();
      break;
    default:
      stopMoving();
      break;
    }
}

void obstacleAvoidanceMode() {
  // drive automatically
}

const char
    autoDrive = 'd';


int moveDelay = 2000;
void loop() {
  
  goForward();
  delay(moveDelay);
  goBackward();
  delay(moveDelay);
  goLeft();
  delay(moveDelay);
  goRight();
  delay(moveDelay);

// /*
  if (btModule.available() > 0) {
    char receivedInstruction = Serial.read(); // read the incoming command
    switch(receivedInstruction) {
      case autoDrive:
        obstacleAvoidanceMode();
        break;
      default:
        IOTDrive(receivedInstruction);
        break;
    }
  }
// */

}

#endif

//========================================