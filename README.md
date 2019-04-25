# The Team
### Team Cloud Lamp
Members: Collin Moore, Samuel Yeomans, Sidharth Eleswarapu, Koh Hui Fang

# The Project
### Purpose 
Use a Raspberry Pi to periodically collect data from a free weather API online, then send the information to the MBED to display an animation corresponding to the current weather on an LED strip.

Click the image below to view a video of the lamp in operation.

[![Cloud Lamp](https://img.youtube.com/vi/CS85uOtd2Cg/0.jpg)](https://youtu.be/CS85uOtd2Cg "Cloud Lamp")

### Getting Weather Data
To collect the weather data, this Python script sends an API request to openweathermap.org. This script condenses the more granular weather conditions into general archetypes and sends the corresponding character to the MBED through the virtual COM USB serial port. Currently, the script has Atlanta set as the location. More information regarding the weather API, including a list of conditions and locations, can be found [here](https://openweathermap.org/current).

### Configuring settings via HTML
The Python script runs inside of a Node.js Express script which pushes a HTML page to port 8000. This page allows the user to change the mode of the Cloud Lamp. There are currently 4 modes:
1. Off (all the lights are turned off)
2. Demo (cycles thru the different animations)
3. Live Weather (displays the animation associated with the current weather condition)
4. Custom Color (displays the color specified by the values in the text boxes)

When the submit button is pressed on the website, the Python script runs as a child process of the Node.js script, polls the weather API (if necessary), and sends the desired state to the MBED via serial port.

### Displaying the animations via the MBED
To display the animations, we use a analog LED strip connected to a 12V power adapter. The circuit below uses MOSFETS to control the red, green, and blue signals using PWM. For more information about using this LED strip, see [here](https://learn.adafruit.com/rgb-led-strips/overview).

![Circuit diagram](https://github.com/syeomans/mbed-cloud-lamp/blob/master/Circuit%20Diagram.png)

![Wiring for the analog LED strip](https://i.groupme.com/1224x1632.jpeg.54044aa65b5b4004841e978d1b89a970.large)

This LED strip, along with the Pi and the MBED, are placed inside the water jug. We cut a door in the bottom of the jug to more easily access the innards. After the completion of the technical side of the project, we glued clumps of cotton all over it so that the jug resembled a cloud. Below is a block diagram detailing the operation of the code

![Block diagram](https://github.com/syeomans/mbed-cloud-lamp/blob/master/blockDiagram.png?raw=true)

# The Case

The team built the cloud-shaped casing by following Household Hacker's [How To Make A Cloud Light](https://www.youtube.com/watch?v=07m0e7NwzKc) with a few modifications to make a door out of the bottom of the bottle. 

### Parts list
- Gallon water jug
- Bag of craft stuffing
- Small, flat door hinges (x2)
- Small hook latch
- Bolts, nuts, and washers that fit with your hinges and latch

### Build steps
1. Cut out a large rectangle from the base of the jug
2. Attach hinges and latch
3. Hot glue stuffing to the outside of the bottle

# The Build

### Parts list
- [Raspberry Pi 3 Model B](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)
- [MBED LPC 1768](https://os.mbed.com/platforms/mbed-LPC1768/)
- [Analog LED strip](https://www.adafruit.com/product/285?length=1)
- [12 Volt Power Supply](https://www.adafruit.com/product/798)
- Extension Cord

### Build steps

1. Solder jumper wires onto the LED strip and place a weatherproof heat wrap over the connections for stability
2. Construct the MOSFET MBED circuit shown above and use electrical tape to secure the wires in place.
3. Feed the extension cord through the top of the jug.
4. Plug the 12 V power supply and Pi power supply into the extension cord, plug the MBED into a USB port on the Pi, and place all the components inside the jug

# Limitations and Trade-offs
- You need to know the IP address of the Pi to access the HTML config page. For easy access, you have to configure the router to assign the Pi a static IP address
- We considered using more complicated LEDs which allow each segment to be individually assigned, but we decided to use the simpler analog LEDs that accept PWM inputs. You could also use a longer analog LED strip to make the cloud lamp brighter without altering the code
