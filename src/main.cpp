#include <WiFi.h>
#include <esp_now.h>
#include "M5Cardputer.h"

void display() {
    M5Cardputer.Display.clear(); // Limpia la pantalla para actualizar

    // Header
    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.setCursor(0, 0);
    M5Cardputer.Display.println("Cardputer Battery");
    M5Cardputer.Display.println();

    // Battery level
    M5Cardputer.Display.setTextSize(3);
    M5Cardputer.Display.printf("%03d %%", M5.Power.getBatteryLevel());
    M5Cardputer.Display.println();

    // Battery voltage
    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.println();
    M5Cardputer.Display.printf("%.3f V", M5.Power.getBatteryVoltage() / 1000.0);
}

void setup() {
    // Setup cardputer
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);

    // Setup display
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextColor(ORANGE, BLACK);
}

void loop() {
    // Display main screen
    display();

    // Do nothing interval
    delay(2000);
}
