#include <UltrasonicHelper.h>

//Class object(_trigPin, _echoPin, _numReadings)
UltrasonicHelper ultrasonic(9,10,5);

void setup() {
  Serial.begin(9600);
  ultrasonic.begin();
}

void loop() {
  
  float avgDistance = ultrasonic.averageDistance();

  if (avgDistance > 0) {
    Serial.print("Average Distance: ");
    Serial.print(avgDistance);
    Serial.println(" cm");
  }
    
  delay(500); 
}
