#include <Arduino.h>
#include "data.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#define QUEUE_LENGTH 10


QueueHandle_t myQueue;

void setup() {

  myQueue = xQueueCreate(5, sizeof(Person));

  Serial.begin(115200);

  // Crear la tarea y asignarla al core 0
  xTaskCreatePinnedToCore(
    productor,     // Función que ejecuta la tarea
    "Task_Core1",  // Nombre de la tarea (usado solo para depuración)
    4096,          // Tamaño del stack de la tarea
    NULL,          // Parámetro para la función (en este caso no se pasa ninguno)
    1,             // Prioridad de la tarea
    NULL,          // No necesitamos un manejador de tarea aquí
    0              // Core en el que queremos que se ejecute (Core 0)
  );

  // Crear la tarea y asignarla al core 1
  xTaskCreatePinnedToCore(
    consumidor,    // Función que ejecuta la tarea
    "Task_Core0",  // Nombre de la tarea (usado solo para depuración)
    4096,          // Tamaño del stack de la tarea
    NULL,          // Parámetro para la función
    1,             // Prioridad de la tarea
    NULL,          // No necesitamos un manejador de tarea aquí
    1              // Core en el que queremos que se ejecute (Core 1)
  );
}


void productor(void *pvParameters) {

  for (;;) {
    int id = randomId();
    Person p = getPersonById(id);

    // Intentar enviarla a la cola (bloquea si está llena)
    xQueueSend(myQueue, &p, portMAX_DELAY);

    ESP_LOGI("PRODUCTOR", "Persona enviada a la cola: %s %s (ID: %d)", p.name, p.last_name, p.id);

    // Espera aleatoria entre 500 y 2000 ms
    int delayMs = (esp_random() % 1501) + 500;
    vTaskDelay(pdMS_TO_TICKS(delayMs));
  }
}

void consumidor(void *pvParameters) {
  Person p;

  for (;;) {
    // Espera fija de 1 segundo
    vTaskDelay(pdMS_TO_TICKS(1000));

    // Recibe persona de la cola (bloquea si está vacía)
    if (xQueueReceive(myQueue, &p, portMAX_DELAY) == pdTRUE) {
      // Imprimir los datos por Serial
      Serial.printf("Consumido -> ID: %d, Nombre: %s, Apellido: %s, Email: %s \n",
                    p.id, p.name, p.last_name, p.email);
    } else {
      Serial.println("Error al recibir de la cola.");
    }
  }
}

void loop() {
  //
}
