#include "UltrasonicHelper.h"

UltrasonicHelper::UltrasonicHelper(int trigPin, int echoPin, int numReadings) {
    _trigPin = trigPin;
    _echoPin = echoPin;
    _numReadings = max(3, numReadings);
}

void UltrasonicHelper::begin() {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    digitalWrite(_trigPin, LOW);
}

void UltrasonicHelper::setTimeout(unsigned long timeout) {
    _timeout = timeout;
}

float UltrasonicHelper::calcDistance() {
    long duration;
    float distance;

    
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    duration = pulseIn(_echoPin, HIGH, _timeout);

    if (duration == 0) {
        return -1.0;
    }

    distance = duration * 0.034 / 2;

    if (distance < 2.0 || distance > 400.0) {
        return -1.0;
    }

    return distance;
}

float UltrasonicHelper::averageDistance() {
    float distances[_numReadings];
    int validCount = 0;

    for (int i = 0; i < _numReadings; i++) {
        float reading = calcDistance();

        if (isValidReading(reading)) {
            distances[validCount] = reading;
            validCount++;
        }

        delay(10); 
    }

    if (validCount < 2) {
        return -1.0;
    }

    float sum = summedDistance(distances, validCount);
    return sum / (validCount - 2);
}

float UltrasonicHelper::medianDistance() {
    float distances[_numReadings];
    int validCount = 0;

    for (int i = 0; i < _numReadings; i++) {
        float reading = calcDistance();

        if (isValidReading(reading)) {
            distances[validCount] = reading;
            validCount++;
        }

        delay(10);
    }

    if (validCount == 0) {
        return -1.0;
    }

    sortArray(distances, validCount);

    if (validCount % 2 == 0) {
        return (distances[validCount/2 - 1] + distances[validCount/2]) / 2.0;
    } else {
        return distances[validCount/2];
    }
}

float UltrasonicHelper::summedDistance(float distances[], int length) {
    if (length <= 2) {
        float sum = 0;
        for (int i = 0; i < length; i++) {
            sum += distances[i];
        }
        return sum;
    }

    float max = distances[0];
    float min = distances[0];
    float sum = distances[0];

    for (int i = 1; i < length; i++) {
        if (distances[i] > max) {
            max = distances[i];
        } else if (distances[i] < min) {
            min = distances[i];
        }
        sum += distances[i];
    }

    sum -= max;
    sum -= min;

    return sum;
}

void UltrasonicHelper::sortArray(float arr[], int length) {
    for (int i = 1; i < length; i++) {
        float key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

bool UltrasonicHelper::isValidReading(float distance) {
    return distance > 0 && distance >= 2.0 && distance <= 400.0;
}
