#include "UltrasonicHelper.h"

UltrasonicHelper::UltrasonicHelper(int trigPin, int echoPin, int numReadings) {
    _trigPin = trigPin;
    _echoPin = echoPin;
    _numReadings = max(3, numReadings);  // Minimo 3 letture per statistica significativa
}

void UltrasonicHelper::begin() {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    digitalWrite(_trigPin, LOW);  // Inizializza il pin a LOW
}

void UltrasonicHelper::setTimeout(unsigned long timeout) {
    _timeout = timeout;
}

float UltrasonicHelper::calcDistance() {
    long duration;
    float distance;

    // Assicura che il pin trigger sia LOW
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);

    // Invia impulso di 10 microsecondi
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    // Leggi la durata dell'eco con timeout
    duration = pulseIn(_echoPin, HIGH, _timeout);

    // Se timeout, ritorna -1 per indicare errore
    if (duration == 0) {
        return -1.0;
    }

    // Conversione tempo → distanza (cm)
    distance = duration * 0.034 / 2;

    // Validazione range realistico (2cm - 400cm per HC-SR04)
    if (distance < 2.0 || distance > 400.0) {
        return -1.0;
    }

    return distance;
}

float UltrasonicHelper::averageDistance() {
    float distances[_numReadings];
    int validCount = 0;

    // Raccogli le letture valide
    for (int i = 0; i < _numReadings; i++) {
        float reading = calcDistance();

        // Salva solo letture valide
        if (isValidReading(reading)) {
            distances[validCount] = reading;
            validCount++;
        }

        delay(10);  // Piccola pausa tra le letture
    }

    // Se non abbiamo abbastanza letture valide, ritorna errore
    if (validCount < 2) {
        return -1.0;
    }

    // Calcola la media rimuovendo outlier
    float sum = summedDistance(distances, validCount);
    return sum / (validCount - 2);
}

float UltrasonicHelper::medianDistance() {
    float distances[_numReadings];
    int validCount = 0;

    // Raccogli le letture valide
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

    // Ordina l'array e prendi la mediana
    sortArray(distances, validCount);

    // Se numero pari di elementi, media dei due centrali
    if (validCount % 2 == 0) {
        return (distances[validCount/2 - 1] + distances[validCount/2]) / 2.0;
    } else {
        return distances[validCount/2];
    }
}

float UltrasonicHelper::summedDistance(float distances[], int length) {
    if (length <= 2) {
        // Se abbiamo solo 1-2 letture valide, ritorna la somma semplice
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
    // Simple insertion sort per array piccoli
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
    // Considera valide solo letture nel range realistico del sensore
    return distance > 0 && distance >= 2.0 && distance <= 400.0;
}