#if 0

const int trigPin = 12;
const int echoPin = 11;

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
  delay(1000);  // Adjust delay as needed

  return calculatedDistance;
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
}

#endif