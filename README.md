# Proyecto Semáforos y Multitarea en ESP32

<p align="center">
    <img width="200" src="https://joy-it.net/files/files/Produkte/SBC-NodeMCU-ESP32/SBC-NodeMCU-ESP32-01.png">
</p>

Este repositorio contiene varios proyectos de ejemplo utilizando el microcontrolador ESP32, donde se exploran conceptos de multitarea y sincronización utilizando FreeRTOS y semáforos.

## CLASE 4 Multiprocesamiento y uso de semáforos en ESP32

### 1. **Multitarea en el ESP32: Imprimir en Cada Core**

Este proyecto es una introducción al uso de las capacidades de los dos núcleos del ESP32. Se crea una tarea que imprime un mensaje cada segundo, indicando en qué core está corriendo la tarea (Core 0 o Core 1). El propósito de este proyecto es aprender a asignar tareas a núcleos específicos y utilizar el sistema multitarea que ofrece el ESP32 con FreeRTOS.

### 2. **Prender LEDs con Secuencia de Semáforo**

En este proyecto se crea una simulación de semáforo con tres LEDs (rojo, amarillo y verde). Los LEDs están controlados mediante tareas en un sistema operativo en tiempo real (FreeRTOS), utilizando semáforos para gestionar el acceso a los LEDs. El semáforo sigue la secuencia típica:

-   **Rojo** por 3 segundos
    
-   **Amarillo** por 1 segundo
    
-   **Verde** por 3 segundos
    

El código utiliza un semáforo para asegurar que solo una tarea pueda acceder a los LEDs en un momento dado, garantizando que la secuencia de luces sea segura y sin interferencias.


### 3. **Semáforos Sincronizados con Dos Semáforos**

En este proyecto se manejan dos semáforos, cada uno controlado por un conjunto de LEDs (rojo, amarillo y verde). Ambos semáforos son controlados de forma independiente en dos núcleos del ESP32, pero se sincronizan para que solo uno de ellos esté en verde en un momento dado.

-   **Semáforo 1** y **Semáforo 2** se alternan el estado verde, asegurando que ambos semáforos nunca estén en verde al mismo tiempo.  
    El proyecto utiliza semáforos para garantizar que las tareas que controlan los LEDs de cada semáforo se ejecuten de manera ordenada y sin conflictos.

  <p align="center">
  <img src="imgs/gif.gif" />
</p>


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



## Tecnologías y Herramientas Utilizadas

-   **ESP32**: Microcontrolador de doble núcleo que ejecuta las tareas en los dos núcleos de manera simultánea.
    
-   **FreeRTOS**: Sistema operativo en tiempo real utilizado para crear tareas y manejar semáforos.
    
-   **Arduino IDE**: Entorno de desarrollo utilizado para programar el ESP32.
