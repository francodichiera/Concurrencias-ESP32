## Clase 4 - Multiprocesamiento y uso de semáforos en ESP32

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
