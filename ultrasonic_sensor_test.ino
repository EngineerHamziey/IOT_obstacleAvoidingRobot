#if 1

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

void obstacleAvoidanceMode() {
  const int turnDelay = 3;// seconds

  if (calculateDistance() < 10) {
    Serial.println("distance less than threshold");
    // stopMoving();  // Stop the car
    // Obstacle detected, perform avoidance maneuver
    // servoRotateRight();
    int rightSideDistance = calculateDistance();
    // servoRotateLeft();
    int leftSideDistance = calculateDistance();
    // servoRotateFront();//return to normal postion
    (leftSideDistance > rightSideDistance) ? Serial.println("go left") : Serial.println("go right");
    


    delay(turnDelay * 1000);
  } else {
      // No obstacle, continue normal operation
      // goForward();
      Serial.println("no obstacle, go forward");
  }
}

void setup() {
  beginTheSerialMonitor();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  Serial.print("Distance: ");
  Serial.print(calculateDistance());
  Serial.println(" cm");
  obstacleAvoidanceMode();
}

#endif