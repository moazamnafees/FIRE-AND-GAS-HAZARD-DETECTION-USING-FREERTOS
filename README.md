# FIRE-AND-GAS-HAZARD-DETECTION-USING-FREERTOS

This project is an Arduino-based Gas and Flame Detection System implemented using FreeRTOS. It continuously monitors gas and flame levels using MQ2 and flame sensors and triggers a fan and LED as safety measures when dangerous conditions are detected.

🛠️ ## Hardware Requirements:

Arduino Board (e.g., Uno, Mega, Nano)

MQ2 Gas Sensor (connected to A0 for analog and D2 for digital)

Flame Sensor (connected to A1 for analog and D3 for digital)

Fan (connected to D9 with driver circuit if needed)

LED (connected to D10)

Jumper Wires

Breadboard

⚡ Pin Configuration:

Component

Arduino Pin

MQ2 Analog

A0

MQ2 Digital

D2

Flame Analog

A1

Flame Digital

D3

Fan Control

D9

LED Indicator

D10

📋 Features:

Real-time gas and flame monitoring

Automatic fan activation when high gas levels are detected

LED indicator for flame detection

Task management using FreeRTOS with multitasking capability

🚀 How It Works:

GasMonitorTask: Reads MQ2 sensor data and sends gas levels to the queue.

FlameMonitorTask: Monitors the flame sensor and sends flame levels to the queue.

FanControlTask: Activates the fan if gas levels exceed 600 (adjustable threshold).

LEDControlTask: Turns on the LED when flame levels exceed 1000 (adjustable threshold).

⚙️ Setup and Upload:

Install FreeRTOS Library in Arduino IDE:

Go to Sketch → Include Library → Manage Libraries.

Search for "FreeRTOS" and install it.

Connect the Arduino to your PC.

Upload the .ino file to your Arduino board.

Open the Serial Monitor to observe real-time sensor data.

📊 Sample Output (Serial Monitor):

Gas or Smoke Level: 450, Digital: 0
Flame Level: 800, Digital: 0
No gas detected: Fan OFF
No flame detected: LED OFF
Gas detected: Fan ON
Flame detected: LED ON

📝 Adjustable Parameters:

Gas Threshold: if (gasLevel > 600) → Change 600 as needed.

Flame Threshold: if (flameLevel > 1000) → Adjust 1000 as required.

📚 License:

This project is open-source and free to use for educational purposes.

Contributions are welcome! Feel free to fork, improve, or suggest enhancements
