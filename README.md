The safe uses two ESP32s. One on the front of the safe acting as the camera and the other one controls everything else. There is also an LCD, a button, and an LED on the top of the safe. 
The safe unlocks when a face is recognised. When you are finished using the safe you press the button and safe will close itself and lock. 
The door opens and closes itself using servo motors. The LCD display shows different messages depending on what the safe is doing. 
The safe is locked using a solenoid lock connected to a relay module. When it is unlocked the LED will turn on. When the door is opening or closing a buzzer will sound.

There is a web server application on both ESP32s. 
The ESP32 with the camera has a camera web server that you can connect to, so you can enroll your face. 
It can enroll multiple faces so you can have more than one person with access to the safe. 
The second ESP32 has a simple website that allows you to disable access to the safe.
