#include "led_library.h"
#include "driver/ledc.h"
#include "esp_err.h"

// --- Configuración del Hardware ---
// ¡Cambia estos pines por los que vayas a usar!
#define LEDC_TIMER          LEDC_TIMER_0
#define LEDC_MODE           LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES       LEDC_TIMER_8_BIT // Resolución de 8 bits (0-255)
#define LEDC_FREQUENCY      (4000) // Frecuencia en Hertz

// Canales y Pines para RGB
#define LEDC_R_GPIO         (12) // Pin para Rojo
#define LEDC_R_CHANNEL      LEDC_CHANNEL_0

#define LEDC_G_GPIO         (13) // Pin para Verde
#define LEDC_G_CHANNEL      LEDC_CHANNEL_1

#define LEDC_B_GPIO         (14) // Pin para Azul
#define LEDC_B_CHANNEL      LEDC_CHANNEL_2
// ----------------------------------

void led_lib_init(void)
{
    // 1. Configurar el Timer (solo 1 vez)
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // 2. Configurar Canal ROJO
    ledc_channel_config_t ledc_channel_r = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_R_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_R_GPIO,
        .duty           = 0, // Iniciar apagado
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_r));

    // 3. Configurar Canal VERDE
    ledc_channel_config_t ledc_channel_g = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_G_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_G_GPIO,
        .duty           = 0, // Iniciar apagado
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_g));

    // 4. Configurar Canal AZUL
    ledc_channel_config_t ledc_channel_b = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_B_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_B_GPIO,
        .duty           = 0, // Iniciar apagado
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel_b));
}

void led_lib_set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    // Establecer el duty (brillo) para cada canal
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_R_CHANNEL, r));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_R_CHANNEL));

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_G_CHANNEL, g));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_G_CHANNEL));

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_B_CHANNEL, b));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_B_CHANNEL));
}