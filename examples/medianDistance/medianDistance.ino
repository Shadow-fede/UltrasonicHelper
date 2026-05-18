#include <UltrasonicHelper.h>

//Class object(_trigPin, _echoPin, _numReadings)
UltrasonicHelper ultrasonic(9,10,5);

void setup() {
  Serial.begin(9600);
  ultrasonic.begin();
}

void loop() {
  
  float medDistance = ultrasonic.medianDistance();

  if (medDistance > 0) {
    Serial.print("Median: ");
    Serial.print(medDistance);
    Serial.println(" cm");
  }
    
  delay(500); 
}
