bool trigger(__unused repeating_timer *timer) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    speakerChangeVolume(3);
    sleep_ms(100);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    return true;
}

int64_t alarm_trigger(__unused alarm_id_t id, __unused void *user_data) {
    speakerStopSong();
    song_playing = false;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    return true;
}

// Main Function
    // A repeating timer which slowly increases the volume
    repeating_timer timer;
    add_repeating_timer_ms(2000, trigger, NULL, &timer);

    // A one-use timer which will stop the song being played
    add_alarm_in_ms(10000, alarm_trigger, NULL, true);

    cancel_repeating_timer(&timer);