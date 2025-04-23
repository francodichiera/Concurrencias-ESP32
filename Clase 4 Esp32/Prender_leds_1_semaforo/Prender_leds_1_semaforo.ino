// Declarar los pines de los LEDs
const int LED_ROJO = 32;   // Pin D32 para LED rojo
const int LED_AMARILLO = 13; // Pin D13 para LED amarillo
const int LED_VERDE = 12;   // Pin D12 para LED verde

// Crear un semáforo para controlar el acceso a los LEDs
SemaphoreHandle_t mySemaphore;

// Declarar la función de la tarea para controlar la secuencia del semáforo
void tareaSemaforo(void *parameter);

void setup() {
  // Inicializar el puerto serial para depuración
  Serial.begin(115200);

  // Configurar los pines de los LEDs como salida
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  // Inicializar el semáforo
  mySemaphore = xSemaphoreCreateMutex();

  // Crear la tarea que manejará el semáforo
  xTaskCreatePinnedToCore(
    tareaSemaforo,       // Función que ejecuta la tarea
    "Tarea_Semaforo",    // Nombre de la tarea
    4096,                // Tamaño del stack de la tarea
    NULL,                // Parámetro (no necesitamos en este caso)
    1,                   // Prioridad de la tarea
    NULL,                // No necesitamos un manejador de tarea aquí
    0                    // Core donde se ejecutará (core 0)
  );
}

void tareaSemaforo(void *parameter) {
  // Bucle infinito para alternar entre los LEDs
  for (;;) {
    // Tomamos el semáforo para que una tarea pueda controlar los LEDs
    if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE) {

      // Secuencia del semáforo: Rojo -> Amarillo -> Verde
      Serial.println("Semáforo: Rojo");
      digitalWrite(LED_ROJO, HIGH);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_VERDE, LOW);
      vTaskDelay(pdMS_TO_TICKS(3000));  // Rojo por 3 segundos

      Serial.println("Semáforo: Amarillo");
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AMARILLO, HIGH);
      digitalWrite(LED_VERDE, LOW);
      vTaskDelay(pdMS_TO_TICKS(1000));  // Amarillo por 1 segundo

      Serial.println("Semáforo: Verde");
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_VERDE, HIGH);
      vTaskDelay(pdMS_TO_TICKS(3000));  // Verde por 3 segundos

      // Liberar el semáforo para que otras tareas puedan usarlo si es necesario
      xSemaphoreGive(mySemaphore);
    }
  }
}

void loop() {
  // No es necesario hacer nada en el loop, las tareas se ejecutan independientemente.
}

