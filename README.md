Gesture-Controlled Media Remote Using Ultrasonic Sensors

This project implements a gesture-based media control system using an ESP8266 microcontroller and ultrasonic distance sensors. The system allows users to control media playback—such as play/pause, switching tracks, and adjusting volume—through simple and intuitive hand gestures, eliminating the need for physical buttons.

The project focuses on real-time gesture detection, signal smoothing, gesture-mapping logic, and mode switching, providing an efficient and touch-free human–machine interaction experience.

Project Overview:
The system uses one or two ultrasonic sensors to measure hand proximity and movement. After applying basic filtering to stabilize raw sensor readings, the Arduino interprets the gesture patterns to trigger corresponding media actions.

Two operational modes—Media Mode and Volume Mode—allow a broader set of controls within a simple interface. An LED or RGB indicator provides real-time feedback on the active mode and detected gestures.

Key Features:
1. Gesture Sensing
	•	Interfaces ultrasonic sensor(s) to accurately measure hand distance.
	•	Implements filtering/averaging algorithms to reduce noise and ensure stable readings.

2. Detects gestures such as:
	•	Play / Pause (Holding hand steady for 2 seconds)
	•	Next Track / Previous Track (Swipe Left / Swipe Right)
	•	Volume Up / Volume Down (Swipe Left and hold / Swipe Right and hold)

3. Mode Switching & Visual Feedback
	•	Supports two modes:
	•	Media Mode (playback controls)
	•	Volume Mode (volume adjustments)
	•	Mode switching performed through a special gesture (Holding hand steady for 4 seconds).
	•	LED or RGB indicators show:
	•	Active Mode
