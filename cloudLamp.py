# Import modules
# import time
# import RPi.GPIO as GPIO
import urllib2
import json

def getWeather():
	"""
	Make an api call to openweathermap.org

	Returns one of:
	['Clear', 'Drizzle', 'Clouds', 'Thunderstorm', 'Rain', 'Snow', 'Fog', 'Mist', 'Smoke', 'Haze', 'Ash']
		(Technically it can return more, but these are the only ones we care about. 
		Link to see the rest: https://openweathermap.org/weather-conditions )
	"""
	apiKey = "1be18276dbf6dd7f92eb0d144ef88985"
	url = "https://api.openweathermap.org/data/2.5/weather?id=4671576&APPID=" + apiKey

	request = urllib2.Request(url)
	contents = json.load(urllib2.urlopen(request))
	return(contents['weather'][0]['main'])

# Main loop
currentWeather = getWeather()
print(currentWeather)

