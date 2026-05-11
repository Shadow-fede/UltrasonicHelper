#ifndef UltrasonicHelper_h
#define UltrasonicHelper_h

#include <Arduino.h>

class UltrasonicHelper {
public:
    UltrasonicHelper(int trigPin, int echoPin, int numReadings = 5);

    float calcDistance();
    float averageDistance();
    float medianDistance();  // Nuovo metodo
    void begin();
    void setTimeout(unsigned long timeout);  // Nuovo metodo

private:
    int _trigPin;
    int _echoPin;
    int _numReadings;
    unsigned long _timeout = 30000;  // 30ms timeout default

    float summedDistance(float distances[], int length);
    void sortArray(float arr[], int length);  // Nuovo metodo privato
    bool isValidReading(float distance);  // Nuovo metodo privato
};

#endif