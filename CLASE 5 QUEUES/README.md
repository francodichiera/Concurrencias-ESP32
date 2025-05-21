## Clase 5 - Comunicación entre Tareas con Queues

### ¿Qué es una cola?

Una **cola** (o _queue_) es una estructura de datos en la que los elementos se agregan por un extremo y se retiran por el otro. Funciona bajo el principio **FIFO** (_First In, First Out_), es decir, **el primero en entrar es el primero en salir**. Es como una fila de personas: quien llega primero es atendido primero.

### ¿Cómo se usan las colas en FreeRTOS?

En **FreeRTOS**, las colas se utilizan para permitir la **comunicación segura entre tareas**. Son ideales cuando una tarea necesita enviar datos a otra. Por ejemplo, si una tarea mide temperatura y otra la muestra en pantalla, pueden usar una cola para compartir la información sin conflictos.

#### Funciones principales:

-   `xQueueCreate`: Crea una nueva cola.
    
-   `xQueueSend` / `xQueueSendToFront` / `xQueueSendToBack`: Envía datos a la cola.
    
-   `xQueueReceive`: Recibe datos de la cola.
    

> 📦 Ejemplo real: Una caja de sugerencias donde una persona deja un papel con su mensaje y otra lo saca más tarde para leerlo.

----------

### Ejercicio 1: Envío de Estructuras entre Tareas

Se implementan dos tareas:

-   **Productor**: genera una persona aleatoria (`Person`) y la envía a la cola.
    
-   **Consumidor**: recibe los datos y los imprime por el monitor serial.
    

Esto demuestra cómo usar estructuras personalizadas dentro de una cola, manteniendo la separación de responsabilidades entre las tareas.

**Temas clave**:

-   Uso de `xQueueCreate` con `sizeof(Person)`
    
-   Comunicación entre núcleos
    
-   `portMAX_DELAY` para espera indefinida
    

----------

### Ejercicio 2: Control de LEDs mediante Comandos en la Cola

Otra aplicación práctica donde:

-   Una tarea **productora** genera comandos de control de LEDs (rojo, amarillo, verde o parpadeo).
    
-   Una tarea **consumidora** ejecuta las acciones de acuerdo con los comandos recibidos.
    

**Destacado**: Si se genera el comando especial de **parpadeo**, este se envía al **frente de la cola** usando `xQueueSendToFront`, dándole prioridad.
