void beginTheSerialMonitor() {Serial.begin(115200);}
#if 0

//Add software serial library so that you can add custom UART, tx, rx
#include <SoftwareSerial.h>
const int btTx = 2, btRx = 3;

SoftwareSerial btModule(btTx, btRx);

//back Wheels
const int
  back_rightMotorForward = 13,
  back_rightMotorBackward = 12,
  back_leftMotorForward = 10,
  back_leftMotorBackward = 11;

//front Wheels
const int
  front_rightMotorForward = 1,
  front_rightMotorBackward = 0,
  front_leftMotorForward = 8,
  front_leftMotorBackward = 7;

const int trigPin = A3;
const int echoPin = A1;

int calculateDistance() {//calculate distance in centimeter
  int calculatedDistance;
  long echoReturnTime;
  
  //signal the triger pin to make it send an ultrasonic sound waves
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //store the time taken for echo to return in a variable
  echoReturnTime = pulseIn(echoPin, HIGH);
  calculatedDistance = echoReturnTime / 58.2;//calculate distance using speed of sound which is 343m/s approxe
  delay(500);  // Adjust delay as needed

  return calculatedDistance;
}

void setPinMode() {
  // for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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

void goForward() {  //motor right and left
  //right wheel, go forward//////////////////--------------------------------WHEEL NOT WORKING
  digitalWrite(front_rightMotorForward, HIGH);  //GIVE THIS PIN +5V 
  digitalWrite(front_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, go forward  --------------------------------WORKING
  digitalWrite(front_leftMotorForward, HIGH);  //GIVE THIS PIN +5V
  digitalWrite(front_leftMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0

  
  //right wheel, go forward----------------------------------------------------WHEEL NOT WORKING
  digitalWrite(back_rightMotorForward, HIGH);  //GIVE THIS PIN +5V
  digitalWrite(back_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, go forward-----------------------------------WORKING
  digitalWrite(back_leftMotorForward, HIGH);  //GIVE THIS PIN +5V
  digitalWrite(back_leftMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
}

void goBackward() {  //motor right and left
  //right wheel, go BACKWARD----------------------------------NOT WORKING
  digitalWrite(front_rightMotorForward, LOW);
  digitalWrite(front_rightMotorBackward, HIGH);
  //left wheel, go BACKWARD-------------------------WORKING
  digitalWrite(front_leftMotorForward, LOW);
  digitalWrite(front_leftMotorBackward, HIGH);

  
  // right wheel, go BACKWARD-------------------------- WORKING
  digitalWrite(back_rightMotorForward, LOW);
  digitalWrite(back_rightMotorBackward, HIGH);
  // left wheel, go BACKWARD-----------------------------------WORKING
  digitalWrite(back_leftMotorForward, LOW);
  digitalWrite(back_leftMotorBackward, HIGH);
}

void goLeft() {  //RIGHT == FORWARD, LEFT Stop
  //right wheel, go BACKWARD
  digitalWrite(front_rightMotorForward, HIGH);   //GIVE THIS PIN +5V
  digitalWrite(front_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, GO FORWARD
  digitalWrite(front_leftMotorForward, LOW);
  digitalWrite(front_leftMotorBackward, HIGH);

  
  //right wheel, go BACKWARD
  digitalWrite(back_rightMotorForward, HIGH);   //GIVE THIS PIN +5V
  digitalWrite(back_rightMotorBackward, LOW);  //GIVE THIS PIN 0(GND) 0
  //left wheel, GO FORWARD
  digitalWrite(back_leftMotorForward, LOW);
  digitalWrite(back_leftMotorBackward, HIGH);
}

void goRight() {  //RIGHT == stop, LEFT = forward
  //right wheel, go forward
  digitalWrite(front_rightMotorForward, LOW);   //GIVE THIS PIN +5V
  digitalWrite(front_rightMotorBackward, HIGH);  //GIVE THIS PIN 0(GND) 0
  //left wheel, GO BACKWARD
  digitalWrite(front_leftMotorForward, HIGH);
  digitalWrite(front_leftMotorBackward, LOW);

  
  //right wheel, go forward
  digitalWrite(back_rightMotorForward, LOW);   //GIVE THIS PIN +5V
  digitalWrite(back_rightMotorBackward, HIGH);  //GIVE THIS PIN 0(GND) 0
  //left wheel, GO BACKWARD
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
    

void IOTDrive(char command) {

  const char 
    forward = 'f',
    reverse = 'b',
    right = 'r',
    left = 'l',
    servoRight = 'n',
    servoLeft = 't',
    servoFront = 'c';
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
    const int turnDelay = 3;// seconds

    if (calculateDistance() < 10) {
        // Obstacle detected, perform avoidance maneuver
        stopMoving();  // Stop the car
        servoRotateRight();
        int rightSideDistance = calculateDistance();
        servoRotateLeft();
        int leftSideDistance = calculateDistance();
        servoRotateFront();//return to normal postion
        (leftSideDistance > rightSideDistance) ? goLeft() : goRight();
        delay(turnDelay * 1000);
    } else {
        // No obstacle, continue normal operation
        goForward();
    }
}

void testAllMovements() {
  // RIGHT, LEFT, ETC ARE DETERMINED WHRN THE CAR FACES ME
  // //right wheel, go forward//////////////////-------------------------------- WORKING
  // digitalWrite(front_rightMotorForward, HIGH);  // FORWARD WORKING
  // digitalWrite(front_rightMotorBackward, LOW);  // BACKWARD WORKING

  //left wheel, go forward  --------------------------------WORKING
  // digitalWrite(front_leftMotorForward, HIGH);  //FORWARD WORING
  // digitalWrite(front_leftMotorBackward, LOW);  //BACKWARD WORKING

  
  //right wheel, go forward----------------------------------------------------WHEEL NOT WORKING
  // digitalWrite(back_rightMotorForward, LOW);  // FORWARD WORKING
  // digitalWrite(back_rightMotorBackward, HIGH);  //BACKWARD WORKING

  //left wheel, go forward-----------------------------------WORKING
  // digitalWrite(back_leftMotorForward, HIGH);  // FORWARD WORKING
  // digitalWrite(back_leftMotorBackward, LOW);  //BACKWARD WORKING

}


void setup() {
  btModule.begin(9600);
  setPinMode();
  stopMoving();
}

const char autoDrive = 'd';
int moveDelay = 2000;
void loop() {
  // testAllMovements();
  // goForward();
  // goRight();
  // goLeft();

  if (btModule.available() > 0) {
    char receivedInstruction = btModule.read(); // read the incoming command
    switch(receivedInstruction) {
      case autoDrive:
        obstacleAvoidanceMode();
        break;
      default:
        IOTDrive(receivedInstruction);
        break;
    }
  }

}

#endif