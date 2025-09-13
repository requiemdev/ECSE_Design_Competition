#ifndef OLED_H
#define OLED_H

// C defines

#ifdef __cplusplus
extern "C" {
#endif

#include "ssd1306.h"
#include "font.h"

#ifdef __cplusplus
}
#endif

#define OLED_FONT font_8x5

typedef struct {
    ssd1306_t disp;
    uint8_t font[];
} oled_config;

namespace Oled {
    void initialise(uint8_t gpio1, uint8_t gpio2);
    void displayText(char text[]);
}

#endif // OLED_H