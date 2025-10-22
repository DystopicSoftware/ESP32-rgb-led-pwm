#ifndef LED_LIBRARY_H
#define LED_LIBRARY_H

#include <stdint.h>

/**
 * @brief Inicializa los 3 canales PWM para el LED RGB
 * * Configura un temporizador LEDC y 3 canales (R, G, B) asociados a él.
 * Debes definir los pines GPIO en el archivo .c
 */
void led_lib_init(void);

/**
 * @brief Establece el color del LED RGB
 * * @param r Valor de rojo (0-255)
 * @param g Valor de verde (0-255)
 * @param b Valor de azul (0-255)
 */
void led_lib_set_rgb(uint8_t r, uint8_t g, uint8_t b);

#endif // LED_LIBRARY_H