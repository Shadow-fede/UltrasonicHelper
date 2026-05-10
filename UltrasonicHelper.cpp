#include "UltrasonicHelper.h"

UltrasonicHelper::UltrasonicHelper(int trigPin, int echoPin, int numReadings) {
    _trigPin = trigPin;
    _echoPin = echoPin;
    _numReadings = numReadings;


}

void UltrasonicHelper::begin(){
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, OUTPUT);
}

float UltrasonicHelper::averageDistance() {
    float distanze[_numReadings];
    for(int i = 0; i < _numReadings; i++){
        distanze[i] = calcDistance();
        delay(10);
    }

    float somma = summedDistance(distanze, _numReadings);
    return somma/(_numReadings - 2);
}

float UltrasonicHelper::calcDistance() {
    long durata;
    float distanza;

    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    durata = pulseIn(_echoPin, HIGH);
    distanza = durata * 0.034 / 2; // Conversione tempo → distanza (cm)

    return distanza;
}

float UltrasonicHelper::summedDistance(float distances[], int length) {
    float max = distances[0];
    float min = distances[0];
    float sum = distances[0];
    for(int i = 1; i < length; i++){
        if(distances[i] > max){
            max = distances[i];
        }else if(distances[i] < min){
            min = distances[i];
        }

        sum += distances[i];

    }

    sum -= max;
    sum -= min;

    return sum;
}


