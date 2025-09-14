// C++ includes
#include "oled.h"
#include "ironman.h"

oled_config oled;
uint8_t ironman_image[1024] = {0};

void Oled::initialise(uint8_t gpio1, uint8_t gpio2) {
    
    // Intialise GPIO pins
    i2c_init(i2c1, 400000);
    gpio_set_function(gpio1, GPIO_FUNC_I2C);
    gpio_set_function(gpio2, GPIO_FUNC_I2C);
    gpio_pull_up(gpio1);
    gpio_pull_up(gpio2);

    // Initialise disp
    oled.disp.external_vcc = false;  // Is this necessary?
    ssd1306_init(&oled.disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&oled.disp);

    // Intitialise Iron Man
    for (int x = 0; x < 128; x++) {
        for (int page = 0; page < 8; page++) {
            uint8_t byte = 0;
            for (int bit = 0; bit < 8; bit++) {
                int y = page * 8 + bit;
                if (ironman[y * 128 + x])
                    byte |= (1 << bit);
            }
            ironman_image[page * 128 + x] = byte;
        }
    }
}

void Oled::displayText(char text[]) {
    ssd1306_clear(&oled.disp);
    ssd1306_draw_string_with_font(&oled.disp, 8, 24, 2, OLED_FONT, text);
    ssd1306_show(&oled.disp);
}

void Oled::displayIronMan() {
    ssd1306_clear(&oled.disp);
    ssd1306_draw_image(&oled.disp, ironman_image, 128, 64);
    ssd1306_show(&oled.disp);
}