#ifndef UltrasonicHelper_h
#define UltrasonicHelper_h

#include <Arduino.h>

class UltrasonicHelper {
    public:
        UltrasonicHelper(int trigPin, int echoPin, int numLetture);

        float calcDistance();
        float averageDistance();

    private:
        int _trigPin;
        int _echoPin;
        int _numReadings;
        float summedDistance(float distances[], int length);

};

#endif //UltrasonicHelper_h