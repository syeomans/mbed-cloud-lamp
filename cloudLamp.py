# Import modules
import time
import urllib3
# import certifi
import json
import serial
import sys

# Get the condition from javascript
jsMode = str(sys.argv[1])
jsRed = str(sys.argv[2])
jsGreen = str(sys.argv[3])
jsBlue = str(sys.argv[4])
jsWeather = str(sys.argv[5])


def getWeather():
	"""
	Make an api call to openweathermap.org
	"""
	# Set up a pool manager for urllib3 with certificates
	# http = urllib3.PoolManager(cert_reqs='CERT_REQUIRED',ca_certs=certifi.where())
	http = urllib3.PoolManager() # Update: Do this without certificates

	# Generate API request
	apiKey = "1be18276dbf6dd7f92eb0d144ef88985"
	url = "https://api.openweathermap.org/data/2.5/weather?id=4180439&APPID=" + apiKey
	request = http.request('GET', url)
	data = json.loads(request.data)

	# Parse the data we care about
	weatherData = data['weather'][0]['main']
	sunriseTime = int(data['sys']['sunrise'])
	sunsetTime = int(data['sys']['sunset'])

	# Get the current time
	currentTime = time.time()

	# Generate the single character to send to the Mbed
	weatherChar = ""
	if weatherData == "Clear":
		if sunriseTime - currentTime > 600 or sunsetTime - currentTime < 0:
			weatherChar = "n"
		elif sunriseTime - currentTime <= 600 and sunriseTime - currentTime > 0:
			weatherChar = "b"
		elif sunsetTime - currentTime <= 600 and sunsetTime - currentTime > 0:
			weatherChar = "e"
		else:
			weatherChar = "L"
	elif weatherData in ["Drizzle", "Rain"]:
		weatherChar = "r"
	elif weatherData in ["Clouds", "Fog", "Mist", "Smoke", "Haze"]:
		weatherChar = "c"
	elif weatherData == "Thunderstorm":
		weatherChar = "t"
	elif weatherData == "Snow":
		weatherChar = "s"
	else:
		weatherChar = "L"

	# Return the character
	return(weatherChar)

if jsMode == "f":
	ser = serial.Serial('/dev/ttyACM0')  # open serial port
	ser.write(jsMode)     # write a string
	ser.close()             # close port
elif jsMode == "d":
	ser = serial.Serial('/dev/ttyACM0')  # open serial port
	ser.write(jsWeather)     # write a string
	ser.close()             # close port
elif jsMode == "w":
	currentWeather = getWeather()
	ser = serial.Serial('/dev/ttyACM0')  # open serial port
	ser.write(currentWeather)     # write a string
	ser.close()             # close port
elif jsMode == "u":
	ser = serial.Serial('/dev/ttyACM0')  # open serial port
	ser.write(jsMode)     # write a string
	ser.write(jsRed)
	ser.write(jsGreen)
	ser.write(jsBlue)
	ser.close()             # close port
