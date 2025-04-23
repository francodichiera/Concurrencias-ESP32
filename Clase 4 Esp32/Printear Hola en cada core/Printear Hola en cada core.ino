// tienen que crear una funcion llamada tarea que use xportgetcore y printear hola estoy corriendo el core x en el esp y correrlo en el core 0 y el core 1
void setup() {
  Serial.begin(115200); // Inicia la comunicación serial

    // Crear la tarea y asignarla al core 1
  xTaskCreatePinnedToCore(
    tarea,           // Función que ejecuta la tarea
    "Task_Core1",    // Nombre de la tarea (usado solo para depuración)
    4096,            // Tamaño del stack de la tarea
    NULL,            // Parámetro para la función (en este caso no se pasa ninguno)
    1,               // Prioridad de la tarea
    NULL,            // No necesitamos un manejador de tarea aquí
    1                // Core en el que queremos que se ejecute (Core 1)
  );

  // Crear la tarea y asignarla al core 0
  xTaskCreatePinnedToCore(
    tarea,           // Función que ejecuta la tarea
    "Task_Core0",    // Nombre de la tarea (usado solo para depuración)
    4096,            // Tamaño del stack de la tarea
    NULL,            // Parámetro para la función
    1,               // Prioridad de la tarea
    NULL,            // No necesitamos un manejador de tarea aquí
    0                // Core en el que queremos que se ejecute (Core 0)
  );
}

void tarea(void *parameter) {
  for (;;) {
    // Obtener el ID del core en el que se está ejecutando la tarea
    int core = xPortGetCoreID();
    
    // Imprimir el mensaje indicando en qué core está ejecutando la tarea
    Serial.printf("Hola, estoy corriendo en el core %d\n", core);

    // Esperar un poco para que el Serial pueda imprimir
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void loop() {
  // El loop principal no hace nada porque todo el trabajo lo realiza la tarea
}



