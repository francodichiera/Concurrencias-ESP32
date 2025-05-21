
# 🛬 Simulación de Aterrizajes en un Aeropuerto con ESP32 y FreeRTOS

Este proyecto implementa una **simulación de sistema de control de aterrizajes en un aeropuerto** utilizando un microcontrolador **ESP32** con el sistema operativo en tiempo real **FreeRTOS**. La simulación incluye tareas para aviones que intentan aterrizar y una torre de control que autoriza el proceso, todo con manejo de sincronización y comunicación mediante semáforos, colas y mutex.

## 🚀 Descripción

El sistema simula:

-   **5 aviones** (tareas) que intentan aterrizar.
    
-   **3 pistas de aterrizaje**, cada una protegida por un **mutex**.
    
-   Una **torre de control** (tarea dedicada) que autoriza aterrizajes usando una **cola de solicitudes** y **semaforización por avión**.
    

Los aviones y la torre de control se ejecutan en **diferentes núcleos** del ESP32:

-   Aviones: Core 0
    
-   Torre de control: Core 1
    

La simulación imprime por puerto serie los eventos importantes del proceso: solicitud, autorización, aterrizaje y liberación de pista.

## ⚙️ Características Técnicas

-   ⚡ Basado en **ESP32 + FreeRTOS**.
    
-   ✅ Sincronización mediante **mutex** para pistas.
    
-   🔄 Comunicación mediante **colas** y **semaforización binaria** por avión.
    
-   ⌛ Tiempos aleatorios de aproximación y aterrizaje.
    
-   🧠 Gestión de concurrencia y asignación de tareas a núcleos específicos.
    

## 📦 Estructura del Código

-   `avionTask`: Tarea que simula un avión. Solicita aterrizaje, espera permiso, adquiere pista y aterriza.
    
-   `torreControlTask`: Tarea de torre de control. Autoriza aterrizajes en orden.
    
-   `pistas[]`: Mutex para cada pista de aterrizaje.
    
-   `permisos[]`: Semáforo binario para autorizar a cada avión individualmente.
    
-   `colaSolicitudes`: Cola de solicitudes de aterrizaje por parte de los aviones.
    


### 🖥️ Salida Serial (Ejemplo)

```Simulación de aterrizaje iniciada
Avión 2 solicita permiso para aterrizar
Torre autoriza al avión 2 para aterrizar
Avión 2 aterriza en pista 1
Avión 3 solicita permiso para aterrizar
Torre autoriza al avión 3 para aterrizar
Avión 2 libera pista 1```
...

## 🔧 Requisitos

-   ESP32 (cualquier modelo con doble núcleo)
    
-   Arduino IDE (con soporte para ESP32)
    
-   Biblioteca FreeRTOS (incluida en ESP32)
    
-   Conexión USB y monitor serial
    
    

## 📌 Notas

-   Puedes modificar la cantidad de pistas o aviones ajustando `NUM_AVIONES` y `NUM_PISTAS`.
    
-   Asegúrate de tener instalada la herramienta para programar ESP32 en el IDE.
    
-   El proyecto es una simulación didáctica de concurrencia y sincronización usando FreeRTOS.
    
