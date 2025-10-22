# Proyecto: Controlador LED RGB con PWM en ESP32

Este es un proyecto de firmware para el ESP32 (usando ESP-IDF v5.5) que controla un LED RGB de 4 patas (cátodo común) usando el periférico **LEDC (PWM)**. El color del LED se puede cambiar cíclicamente presionando el botón "BOOT" (GPIO 0) de la placa.

El código está refactorizado en una biblioteca simple (`led_library.c` y `led_library.h`) para una fácil reutilización y mantenimiento.

## 🚀 Características

* Control de 3 canales PWM independientes para Rojo, Verde y Azul.
* Resolución de 8 bits (0-255) para cada color.
* Uso del botón "BOOT" (GPIO 0) con pull-up interno para cambiar de color.
* Lógica de "antirrebote" (debounce) simple por software.
* Código de biblioteca modular para una fácil integración.

## Hardware Requerido

* 1 x Placa ESP32 DevKitC v4 (o similar)
* 1 x LED RGB de 4 patas (Cátodo Común)
* 3 x Resistencias de 220 $\Omega$ (Ohm)
* 1 x Breadboard y cables de conexión

## 🔌 Conexiones de Hardware

| Componente | Conexión | ESP32 Pin |
| :--- | :--- | :--- |
| **LED (Pin Rojo)** | Resistencia 220 $\Omega$ | **GPIO 12** (`D12`) |
| **LED (Pin Verde)** | Resistencia 220 $\Omega$ | **GPIO 13** (`D13`) |
| **LED (Pin Azul)** | Resistencia 220 $\Omega$ | **GPIO 14** (`D14`) |
| **LED (Pin Común)** | Directo | **GND** |
| **Botón** | (Interno) | **GPIO 0** (`BOOT`) |



## 💾 Estructura del Software

El proyecto está organizado en dos partes principales dentro de la carpeta `main/`:

* **`ledc_basic_example_main.c`**:
    * Contiene la lógica principal de la aplicación (`app_main`).
    * Inicializa la biblioteca de LED y el GPIO del botón.
    * Ejecuta el bucle infinito `while(1)` que comprueba el estado del botón y cambia los colores.
* **`led_library.c` / `led_library.h`**:
    * Una biblioteca de abstracción simple.
    * `led_lib_init()`: Configura el temporizador LEDC y los 3 canales PWM (R, G, B) asociados a los pines GPIO definidos.
    * `led_lib_set_rgb(r, g, b)`: Una función simple que recibe valores de 0-255 y actualiza el *duty cycle* de los 3 canales PWM.

## 🛠️ Cómo Compilar y Usar

Este proyecto se compila con el **ESP-IDF v5.5**.

1.  Clona el repositorio.
2.  Abre el proyecto en VS Code con la extensión de Espressif.
3.  Conecta tu ESP32.
4.  Selecciona el puerto COM correcto (ej. `COM9`).
5.  Haz clic en el botón "Build, Flash, and Monitor" (el icono del rayo con un monitor).

### Operación

* Al arrancar, el LED se encenderá en **Rojo**.
* Cada vez que presiones el botón `BOOT` (GPIO 0), el color cambiará en el siguiente orden:
    1.  Rojo
    2.  Verde
    3.  Azul
    4.  Amarillo
    5.  Apagado
* El ciclo se repite.