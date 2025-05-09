#include <Arduino.h>
#include "data.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

const int LED_ROJO = 32;      // Pin D32 para LED rojo
const int LED_AMARILLO = 13;  // Pin D13 para LED amarillo
const int LED_VERDE = 12;     // Pin D12 para LED verde


QueueHandle_t myQueue;


void setup() {

  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);

  myQueue = xQueueCreate(5, sizeof(LedCommand));

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
    int command = randomCommand();

    if (command == LED_BLINK) {
      xQueueSendToFront(myQueue, &command, portMAX_DELAY);  // Envía al principio de la cola

    } else {
      xQueueSend(myQueue, &command, portMAX_DELAY);
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
void consumidor(void *pvParameters) {

  for (;;) {
    int receivedValue;
    xQueueReceive(myQueue, &receivedValue, portMAX_DELAY);

    if (receivedValue == LED_RED) {
      digitalWrite(32, HIGH);
      delay(1000);
      digitalWrite(32, LOW);
    }

    if (receivedValue == LED_GREEN) {
      digitalWrite(12, HIGH);
      delay(1000);
      digitalWrite(12, LOW);
    }

    if (receivedValue == LED_YELLOW) {
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
    }

    if (receivedValue == LED_BLINK) {
      // Parpadeo de todos los LEDs
      digitalWrite(LED_ROJO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_AMARILLO, HIGH);
      delay(1000);  // Todos los LEDs encendidos durante 1 segundo

      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARILLO, LOW);
    }
    delay(1000);  // Todos los LEDs apagados durante 1 segundo
  }
}





void loop() {
  // put your main code here, to run repeatedly:
}
