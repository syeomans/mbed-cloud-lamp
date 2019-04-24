# The Team
### Team Cloud Lamp
Members: Collin Moore, Samuel Yeomans, Sidharth Eleswarapu, Koh Hui Fang

# The Project
### Purpose 
Use a Raspberry Pi to periodically collect data from a free weather API online, then send the information to the MBED to display an animation corresponding to the current weather on an LED strip.

### Parts list: 
- [Raspberry Pi 3 Model B] (https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)
- [MBED LPC 1768] (https://os.mbed.com/platforms/mbed-LPC1768/)
- [Analog LED strip] (https://www.adafruit.com/product/285?length=1)
- [12 Volt Power Supply] (https://www.adafruit.com/product/798)
- Gallon water jug
- Bag of craft stuffing

### Getting Weather Data
To collect the weather data, this Python script hits the free weather API _. This script condenses the more granular weather conditions into general archetypes and sends the corresponding character to the MBED through the virtual COM USB serial port. Currently, the script has Atlanta set as the location. More information regarding the weather API, including a list of conditions and locations, can be found here _.

# Configuring settings via HTML
The Python script runs inside of a Node.js Express script which pushes a HTML page to port 8000. This page allows the user to change the mode of the Cloud Lamp. There are currently 4 modes:
1. Off (all the lights are turned off)
2. Demo (cycles thru the different animations)
3. Live Weather (displays the animation associated with the current weather condition)
4. Custom Color (displays the color specified by the values in the text boxes)

# Displaying the animations via the MBED
To display the animations, we use a analog LED strip connected to a 12V power adapter. The circuit below uses MOSFETS to control the red, green, and blue signals using PWM. For more information about using this LED strip, go here: https://learn.adafruit.com/rgb-led-strips/overview

![Wiring diagram for the analog LED strip](https://cdn-learn.adafruit.com/assets/assets/000/002/692/original/led_strips_ledstripfet.gif?1448059609)

This LED strip, along with the Pi and the MBED, are placed inside the water jug. We cut a door in the bottom of the jug to more easily access the innards. After the completion of the technical side of the project, we glued clumps of cotton all over it so that the jug resembled a cloud. More information about the “arts and crafts” aspect of this project can be found in this video _.
