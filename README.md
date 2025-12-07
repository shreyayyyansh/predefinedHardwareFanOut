1. Gesture-Controlled Media Remote Using Ultrasonic Sensors

This project implements a gesture-based media control system using an ESP8266 microcontroller and ultrasonic distance sensors. The system allows users to control media playback—such as play/pause, switching tracks, and adjusting volume—through simple and intuitive hand gestures, eliminating the need for physical buttons.

The project focuses on real-time gesture detection, signal smoothing, gesture-mapping logic, and mode switching, providing an efficient and touch-free human–machine interaction experience.

Project Overview:
The system uses one or two ultrasonic sensors to measure hand proximity and movement. After applying basic filtering to stabilize raw sensor readings, the Arduino interprets the gesture patterns to trigger corresponding media actions.

Two operational modes—Media Mode and Volume Mode—allow a broader set of controls within a simple interface. An LED or RGB indicator provides real-time feedback on the active mode and detected gestures.

Key Features:
a. Gesture Sensing
	•	Interfaces ultrasonic sensor(s) to accurately measure hand distance.
	•	Implements filtering/averaging algorithms to reduce noise and ensure stable readings.

b. Detects gestures such as:
	•	Play / Pause (Holding hand steady for 2 seconds)
	•	Next Track / Previous Track (Swipe Left / Swipe Right)
	•	Volume Up / Volume Down (Swipe Left and hold / Swipe Right and hold)

c. Mode Switching & Visual Feedback
	•	Supports two modes:
	•	Media Mode (playback controls)
	•	Volume Mode (volume adjustments)
	•	Mode switching performed through a special gesture (Holding hand steady for 4 seconds).
	•	LED or RGB indicators show:
	•	Active Mode



2. Proteus-Based Smart Home Automation Simulation
This project simulates a basic smart home automation system using Proteus and a microcontroller (Arduino/PIC). The system automatically controls household appliances—such as lights, fans, and motors—based on real-time sensor inputs. The goal is to demonstrate automation logic, proper circuit design, and sensor-driven decision-making in a virtual environment.

The simulation integrates essential components like LDR and temperature sensors, relays, and electrical loads, providing a complete demonstration of automated home control within Proteus.



Project Overview:
The smart home system monitors environmental conditions using sensors and activates appliances accordingly. An LDR controls lighting based on ambient brightness, while a temperature sensor regulates a fan or heater. The circuit is designed with correct wiring, relay interfacing, and microcontroller logic to mimic a realistic home automation setup.

Key Features:
a. Circuit Design & Layout:
	•	Arduino/PIC microcontroller
	•	Relays for load switching
	•	LDR and temperature sensor
	•	Household loads including bulb, motor, and fan
	•	Neat and accurate wiring with proper component placement for easy debugging and simulation.

b. Sensor Integration
	•	LDR-based light automation: Automatically turns lights ON/OFF depending on ambient light intensity.
	•	Temperature sensor integration: Controls fan or heater based on user-defined threshold temperatures.

c. Automation Logic
	•	Embedded control code monitors sensor readings and activates loads automatically.
	•	Threshold-based decision-making implements realistic home automation behaviour.
	•	Includes optional manual control inputs such as switches or keypad buttons for overriding automatic behaviour.
