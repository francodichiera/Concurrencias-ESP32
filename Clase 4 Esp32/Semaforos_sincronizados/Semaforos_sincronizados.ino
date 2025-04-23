// Pines de los LEDs para el primer semáforo
const int LED_ROJO_1 = 32;      // Pin D32 para LED rojo
const int LED_AMARILLO_1 = 13;  // Pin D13 para LED amarillo
const int LED_VERDE_1 = 12;     // Pin D12 para LED verde

// Pines de los LEDs para el segundo semáforo
const int LED_ROJO_2 = 14;      // Pin D14 para LED rojo
const int LED_AMARILLO_2 = 27;  // Pin D27 para LED amarillo
const int LED_VERDE_2 = 25;     // Pin D25 para LED verde

// Semáforos para controlar el acceso a los LEDs de cada semáforo
SemaphoreHandle_t mySemaphore_1;
SemaphoreHandle_t mySemaphore_2;

// Variable para controlar cuál semáforo está en verde
volatile bool semaforoActivo = true; // true = semáforo 1 en verde, false = semáforo 2 en verde

// Declarar la función para las tareas del semáforo
void tareaSemaforo(void *parameter);

void setup() {
  // Inicializar el puerto serial
  Serial.begin(115200);

  // Configurar los pines de los LEDs como salida para el primer semáforo
  pinMode(LED_ROJO_1, OUTPUT);
  pinMode(LED_AMARILLO_1, OUTPUT);
  pinMode(LED_VERDE_1, OUTPUT);

  // Configurar los pines de los LEDs como salida para el segundo semáforo
  pinMode(LED_ROJO_2, OUTPUT);
  pinMode(LED_AMARILLO_2, OUTPUT);
  pinMode(LED_VERDE_2, OUTPUT);

  // Inicializar los semáforos
  mySemaphore_1 = xSemaphoreCreateMutex();
  mySemaphore_2 = xSemaphoreCreateMutex();

  // Crear las tareas para ambos semáforos en diferentes cores
  xTaskCreatePinnedToCore(
    tareaSemaforo,     // Función para los semáforos
    "Tarea_Semaforo",  // Nombre de la tarea
    4096,              // Tamaño del stack de la tarea
    NULL,              // Parámetro (no necesitamos en este caso)
    1,                 // Prioridad de la tarea
    NULL,              // No necesitamos un manejador de tarea aquí
    0                  // Core donde se ejecutará (core 0)
  );

  xTaskCreatePinnedToCore(
    tareaSemaforo,     // Función para los semáforos
    "Tarea_Semaforo",  // Nombre de la tarea
    4096,              // Tamaño del stack de la tarea
    NULL,              // Parámetro (no necesitamos en este caso)
    1,                 // Prioridad de la tarea
    NULL,              // No necesitamos un manejador de tarea aquí
    1                  // Core donde se ejecutará (core 1)
  );
}

void tareaSemaforo(void *parameter) {
  for (;;) {
    int core = xPortGetCoreID();  // Obtener el ID del core en el que se está ejecutando la tarea

    if (core == 0) {  // Si estamos en el core 0, manejamos el primer semáforo
      if (xSemaphoreTake(mySemaphore_1, portMAX_DELAY) == pdTRUE) {
        if (semaforoActivo) {  // Solo actuamos si semáforo 1 está en verde
          // Secuencia del primer semáforo: Rojo -> Amarillo -> Verde

          Serial.println("Semáforo 1: Verde");
          digitalWrite(LED_ROJO_1, LOW);
          digitalWrite(LED_AMARILLO_1, LOW);
          digitalWrite(LED_VERDE_1, HIGH);
          vTaskDelay(pdMS_TO_TICKS(3000));  // Verde por 3 segundos

          Serial.println("Semáforo 1: Amarillo");
          digitalWrite(LED_ROJO_1, LOW);
          digitalWrite(LED_AMARILLO_1, HIGH);
          digitalWrite(LED_VERDE_1, LOW);
          vTaskDelay(pdMS_TO_TICKS(500));  // Amarillo por 0.5 segundos

          Serial.println("Semáforo 1: Rojo");
          digitalWrite(LED_ROJO_1, HIGH);
          digitalWrite(LED_AMARILLO_1, LOW);
          digitalWrite(LED_VERDE_1, LOW);

          semaforoActivo = false; // Cambiar al semáforo 2
        }
        xSemaphoreGive(mySemaphore_1);  // Liberar el semáforo 1
      }
    }

    if (core == 1) {  // Si estamos en el core 1, manejamos el segundo semáforo
      if (xSemaphoreTake(mySemaphore_2, portMAX_DELAY) == pdTRUE) {
        if (!semaforoActivo) {  // Solo actuamos si semáforo 2 está en verde
          Serial.println("Semáforo 2: Rojo");
          digitalWrite(LED_ROJO_2, HIGH);
          digitalWrite(LED_AMARILLO_2, LOW);
          digitalWrite(LED_VERDE_2, LOW);

          Serial.println("Semáforo 2: Verde");
          digitalWrite(LED_ROJO_2, LOW);
          digitalWrite(LED_AMARILLO_2, LOW);
          digitalWrite(LED_VERDE_2, HIGH);
          vTaskDelay(pdMS_TO_TICKS(3000));  // Verde por 3 segundos

          Serial.println("Semáforo 2: Amarillo");
          digitalWrite(LED_ROJO_2, LOW);
          digitalWrite(LED_AMARILLO_2, HIGH);
          digitalWrite(LED_VERDE_2, LOW);
          vTaskDelay(pdMS_TO_TICKS(500));  // Amarillo por 0.5 segundos

          Serial.println("Semáforo 2: Rojo");
          digitalWrite(LED_ROJO_2, HIGH);
          digitalWrite(LED_AMARILLO_2, LOW);
          digitalWrite(LED_VERDE_2, LOW);

          semaforoActivo = true; // Cambiar al semáforo 1
        }
        xSemaphoreGive(mySemaphore_2);  // Liberar el semáforo 2
      }
    }
  }
}

void loop() {
  // El loop está vacío porque las tareas se ejecutan independientemente.
}
