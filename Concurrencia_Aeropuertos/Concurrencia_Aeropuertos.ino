#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>

#define NUM_AVIONES 5
#define NUM_PISTAS 3

// === VARIABLES GLOBALES ===
SemaphoreHandle_t pistas[NUM_PISTAS];      // Mutex para cada pista
SemaphoreHandle_t permisos[NUM_AVIONES];   // Semáforos binarios por avión
QueueHandle_t colaSolicitudes;             // Cola para que los aviones pidan aterrizar

// === GENERADOR DE TIEMPOS ALEATORIOS (milisegundos) ===
int tiempoRandom(int minMs, int maxMs) {
  return random(minMs, maxMs + 1);
}

// === TAREA DE AVIÓN (CORE 0) ===
void avionTask(void *param) {
  int id = (int)param;

  while (true) {
    // Simula aproximación (espera aleatoria)
    vTaskDelay(pdMS_TO_TICKS(tiempoRandom(1000, 3000)));

    // Solicita aterrizaje
    Serial.printf("Avión %d solicita permiso para aterrizar\n", id);
    xQueueSend(colaSolicitudes, &id, portMAX_DELAY);

    // Espera autorización de torre
    xSemaphoreTake(permisos[id], portMAX_DELAY);

    // Intenta tomar una pista
    for (int i = 0; i < NUM_PISTAS; i++) {
      if (xSemaphoreTake(pistas[i], 0) == pdTRUE) {
        // Inicia aterrizaje
        Serial.printf("Avión %d aterriza en pista %d\n", id, i);
        vTaskDelay(pdMS_TO_TICKS(tiempoRandom(2000, 5000)));

        // Libera pista
        Serial.printf("Avión %d libera pista %d\n", id, i);
        xSemaphoreGive(pistas[i]);
        break;
      }
    }
  }
}

// === TAREA DE TORRE DE CONTROL (CORE 1) ===
void torreControlTask(void *param) {
  int avionID;

  while (true) {
    if (xQueueReceive(colaSolicitudes, &avionID, portMAX_DELAY)) {
      Serial.printf("Torre autoriza al avión %d para aterrizar\n", avionID);
      xSemaphoreGive(permisos[avionID]);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Simulación de aterrizaje iniciada");

  // Semilla para números aleatorios
  randomSeed(analogRead(0));

  // Inicializa mutex de pistas
  for (int i = 0; i < NUM_PISTAS; i++) {
    pistas[i] = xSemaphoreCreateMutex();
  }

  // Inicializa semáforos para cada avión
  for (int i = 0; i < NUM_AVIONES; i++) {
    permisos[i] = xSemaphoreCreateBinary();
  }

  // Inicializa cola de solicitudes
  colaSolicitudes = xQueueCreate(10, sizeof(int));

  // Crea tareas de aviones en Core 0
  for (int i = 0; i < NUM_AVIONES; i++) {
    xTaskCreatePinnedToCore(
      avionTask,         // Función
      "AvionTask",       // Nombre (debug)
      4096,              // Stack
      (void*)i,          // Parámetro: ID avión
      1,                 // Prioridad
      NULL,
      0                  // Core 0
    );
  }

  // Crea torre de control en Core 1
  xTaskCreatePinnedToCore(
    torreControlTask,
    "TorreControl",
    4096,
    NULL,
    1,
    NULL,
    1                  // Core 1
  );
}

void loop() {
  // === LOOP (NO USADO) ===
}
