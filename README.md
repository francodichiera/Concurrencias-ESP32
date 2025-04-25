# Proyecto Semáforos y Multitarea en ESP32

Este repositorio contiene varios proyectos de ejemplo utilizando el microcontrolador ESP32, donde se exploran conceptos de multitarea y sincronización utilizando FreeRTOS y semáforos.

## Descripción de los proyectos

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
    

## Tecnologías y Herramientas Utilizadas

-   **ESP32**: Microcontrolador de doble núcleo que ejecuta las tareas en los dos núcleos de manera simultánea.
    
-   **FreeRTOS**: Sistema operativo en tiempo real utilizado para crear tareas y manejar semáforos.
    
-   **Arduino IDE**: Entorno de desarrollo utilizado para programar el ESP32.
