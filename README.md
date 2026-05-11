# UltrasonicHelper
**Una libreria Arduino leggera e ottimizzata per il sensore HC-SR04/05.**

Questa libreria permette di leggere la distanza tramite sensori a ultrasuoni, implementando un **filtro statistico** per eliminare i picchi di errore (flicker). Calcola la media dei campioni scartando automaticamente il valore massimo e il valore minimo rilevati in ogni ciclo di lettura.

## Caratteristiche
* **Filtro Anti-Flicker:** Rimuove i valori estremi (outliers) per una precisione superiore.
* **Media Mobile:** Numero di campionamenti configurabile.
* **Codice Pulito:** Astrazione completa dell'hardware tramite classe C++.
* **Affidabilità:** Gestione dei tempi di trigger ottimizzata.

## Installazione

1. Scarica questa repository come file `.zip`.
2. Apri l'IDE di Arduino.
3. Vai su **Sketch** -> **#include libreria** -> **Aggiungi libreria da file .ZIP...**
4. Seleziona il file scaricato.
