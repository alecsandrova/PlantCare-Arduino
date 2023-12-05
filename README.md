# PlantCare Arduino Component

## Overview
This Arduino script is part of the PlantCare system, designed to monitor soil moisture and water level, and control a water pump based on signals from a Flutter mobile app.

## Features
- **Moisture Sensing**: Detects soil moisture level using a sensor.
- **Water Level Monitoring**: Checks the water level in the container.
- **Pump Control**: Activates a pump to water the plant based on moisture levels and app commands.
- **Bluetooth Communication**: Receives watering instructions from the mobile app and sends status updates.

## Hardware Requirements
- Arduino board (e.g., Uno, Mega)
- Soil moisture sensor
- Water level sensor
- Water pump
- Bluetooth module (e.g., HC-05 or HC-06)
- Jumper wires and breadboard

## Setup
1. Connect the soil moisture sensor to A0.
2. Connect the water level sensor to A5.
3. Connect the water pump control to digital pin 7.
4. Attach the Bluetooth module to RX and TX pins.
5. Upload this script to your Arduino board.

## Operation
1. The script continuously monitors soil moisture and water level.
2. When moisture is below the threshold, the pump is activated if the water level is adequate.
3. The Arduino communicates with the mobile app via Bluetooth for manual watering control.

