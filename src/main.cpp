#include "M5Cardputer.h"

// Timing for inactivity and display refresh
unsigned long lastActivityTime = 0;
unsigned long inactivityTimeout = 15000;  // 15 seconds

unsigned long displayPreviousMillis = 0;
const long displayInterval = 2000;  // 2 seconds

void display() {
    M5Cardputer.Display.clear();

    // Header
    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.setCursor(0, 0);
    M5Cardputer.Display.println("Cardputer Battery");
    M5Cardputer.Display.println();

    // Battery level
    float currentBatteryLevel = M5.Power.getBatteryLevel();
    M5Cardputer.Display.setTextSize(3);
    M5Cardputer.Display.printf("%03d %%", (int)currentBatteryLevel);
    M5Cardputer.Display.println();

    // Battery voltage
    float currentVoltage = M5.Power.getBatteryVoltage() / 1000.0;
    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.printf("%.3f V", currentVoltage);
    M5Cardputer.Display.println();
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
    unsigned long currentMillis = millis();

    // Refresh the display at regular intervals
    if (currentMillis - displayPreviousMillis >= displayInterval) {
        displayPreviousMillis = currentMillis;
        display();
    }

    // Handle inactivity timeout
    if (currentMillis - lastActivityTime > inactivityTimeout) {
        M5.Display.sleep();
    }

    // Wake up on keypress
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
        lastActivityTime = millis();  // Update the last activity time

        // Wake up display
        M5.Display.wakeup();
        display();
    }

    // Short delay to do nothing
    delay(100);
}