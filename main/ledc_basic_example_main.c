#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_library.h" // ¡Nuestra nueva biblioteca!

static const char *TAG = "main";

// El botón BOOT/FLASH en la mayoría de devkits es el GPIO 0
#define BUTTON_GPIO 0 

void app_main(void)
{
    // 1. Inicializar nuestra biblioteca de LED
    led_lib_init();
    ESP_LOGI(TAG, "Configuración de LEDC completada");

    // 2. Configurar el botón
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_GPIO, GPIO_PULLUP_ONLY); // Usar pull-up interno
    
    ESP_LOGI(TAG, "Configuración de Botón completada. Presiona el botón BOOT.");

    // 3. Lógica para ciclar colores
    int color_index = 0;
    bool button_pressed = false;

    // Lista de colores (R, G, B)
    uint8_t colors[5][3] = {
        {255, 0, 0},   // 1. Rojo
        {0, 255, 0},   // 2. Verde
        {0, 0, 255},   // 3. Azul
        {255, 255, 0}, // 4. Amarillo
        {0, 0, 0}      // 5. Apagado
    };
    int num_colors = 5;

    // Iniciar con un color (ej. Rojo)
    led_lib_set_rgb(colors[0][0], colors[0][1], colors[0][2]);
    ESP_LOGI(TAG, "Iniciado en color 0 (Rojo)");


    // ¡¡ESTE ES EL BUCLE QUE TE FALTA!!
    while (1) {
        // Lógica simple de detección de botón (con antirrebote)
        
        // 1. Detectar si el botón está presionado (GPIO 0 es active-low)
        if (gpio_get_level(BUTTON_GPIO) == 0 && !button_pressed) {
            button_pressed = true; // Marcar como presionado
            
            // Avanzar al siguiente color
            color_index = (color_index + 1) % num_colors;
            
            // Establecer el nuevo color
            uint8_t r = colors[color_index][0];
            uint8_t g = colors[color_index][1];
            uint8_t b = colors[color_index][2];
            led_lib_set_rgb(r, g, b);

            ESP_LOGI(TAG, "Cambiando a color %d (R:%d, G:%d, B:%d)", color_index, r, g, b);
            
            // Pequeña pausa para antirrebote (debounce)
            vTaskDelay(pdMS_TO_TICKS(50));
        }
        
        // 2. Detectar si el botón fue soltado
        if (gpio_get_level(BUTTON_GPIO) == 1) {
            button_pressed = false;
        }

        // Pausa para no saturar la CPU
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}