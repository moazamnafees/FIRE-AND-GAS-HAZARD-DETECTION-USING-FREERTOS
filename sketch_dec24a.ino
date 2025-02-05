#include <Arduino_FreeRTOS.h>
#include <queue.h>

// Pin Definitions
#define MQ2_ANALOG_PIN A0
#define MQ2_DIGITAL_PIN 2
#define FLAME_ANALOG_PIN A1
#define FLAME_DIGITAL_PIN 3
#define FAN_CONTROL_PIN 9
#define LED_PIN 10

// Queue Handles
QueueHandle_t gasQueue;
QueueHandle_t fireQueue;

// Function to initialize pins
void setupPins() {
    pinMode(MQ2_ANALOG_PIN, INPUT);
    pinMode(MQ2_DIGITAL_PIN, INPUT);
    pinMode(FLAME_ANALOG_PIN, INPUT);
    pinMode(FLAME_DIGITAL_PIN, INPUT);
    pinMode(FAN_CONTROL_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
}

void setup() {
    Serial.begin(9600);
    setupPins();

    // Create queues
    gasQueue = xQueueCreate(1, sizeof(int));
    fireQueue = xQueueCreate(1, sizeof(int));

    if (gasQueue == NULL || fireQueue == NULL) {
        Serial.println("Error creating the queues");
        while (1);
    }

    // Create tasks
    xTaskCreate(GasMonitorTask, "GasMonitor", 128, NULL, 2, NULL);
    xTaskCreate(FlameMonitorTask, "FlameMonitor", 128, NULL, 2, NULL);
    xTaskCreate(FanControlTask, "FanControl", 128, NULL, 1, NULL);
    xTaskCreate(LEDControlTask, "LEDControl", 128, NULL, 1, NULL);
}

void loop() {
    // Empty since FreeRTOS handles tasks
}

void GasMonitorTask(void *pvParameters) {
    int gasLevel;
    bool gasDetected;
    while (1) {
        gasLevel = analogRead(MQ2_ANALOG_PIN);
        gasDetected = digitalRead(MQ2_DIGITAL_PIN);
        Serial.print("Gas or Smoke Level: ");
        Serial.print(gasLevel);
        Serial.print(", Digital: ");
        Serial.println(gasDetected);
        xQueueSend(gasQueue, &gasLevel, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void FlameMonitorTask(void *pvParameters) {
    int flameLevel;
    bool flameDetected;
    while (1) {
        flameLevel = analogRead(FLAME_ANALOG_PIN);
        flameDetected = digitalRead(FLAME_DIGITAL_PIN);
        Serial.print("Flame Level: ");
        Serial.print(flameLevel);
        Serial.print(", Digital: ");
        Serial.println(flameDetected);
        xQueueSend(fireQueue, &flameLevel, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void FanControlTask(void *pvParameters) {
    int gasLevel = 0;
    while (1) {
        xQueueReceive(gasQueue, &gasLevel, portMAX_DELAY);
        if (gasLevel > 600) { // Threshold for gas detection
            digitalWrite(FAN_CONTROL_PIN, HIGH); // Turn ON the fan when gas is detected
            Serial.println("Gas detected: Fan ON");
        } else {
            digitalWrite(FAN_CONTROL_PIN, LOW);  // Turn OFF the fan when no gas is detected
            Serial.println("No gas detected: Fan OFF");
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100ms
    }
}

void LEDControlTask(void *pvParameters) {
    int flameLevel = 0;
    while (1) {
        xQueueReceive(fireQueue, &flameLevel, portMAX_DELAY);
        if (flameLevel > 1000) { // Threshold for flame detection
            digitalWrite(LED_PIN, HIGH); // Turn ON the LED
            Serial.println("Flame detected: LED ON");
        } else {
            digitalWrite(LED_PIN, LOW);  // Turn OFF the LED
            Serial.println("No flame detected: LED OFF");
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100ms
    }
}
