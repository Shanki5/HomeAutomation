import sys
import urllib2
from time import sleep
import Adafruit_DHT as dht
import paho.mqtt.client as mqtt

mqttc = mqtt.Client()
mqttc.connect("localhost",1883,60)
mqttc.loop_start()


# Enter Your API key here
myAPI = '5D2Q2LCHXIKJKRQT' 
# URL where we will send the data, Don't change it
baseURL = 'https://api.thingspeak.com/update?api_key=%s' % myAPI

cloud_state = [1, 1, 1, 1]
prev_state = [1, 1, 1, 1]

state_str = ''.join([str(elem) for elem in cloud_state])
mqttc.publish("test", state_str)

def DHT11_data():
	# Reading from DHT22 and storing the temperature and humidity
	humi, temp = dht.read_retry(dht.DHT11, 17) 
	return humi, temp
while True:
	try:
		humi, temp = DHT11_data()
		if temp > 27 :
			#mqttc.publish("test","1101")
                        		cloud_state[0] = 0
					print "entered temp check"
		else:
					cloud_state[0] = 1
		if(True):
					state_str = ''.join([str(elem) for elem in cloud_state])
					print "entered publish check"
                                        mqttc.publish("test", state_str)
		# If Reading is valid
		if isinstance(humi, float) and isinstance(temp, float):
			# Formatting to two decimal places
			humi = '%.2f' % humi 					   
			temp = '%.2f' % temp
			
			# Sending the data to thingspeak
			conn = urllib2.urlopen(baseURL + '&field1=%s&field2=%s' % (temp, humi))
			print conn.read()
			# Closing the connection
			conn.close()
		else:
			print 'Error'
		# DHT22 requires 2 seconds to give a reading, so make sure to add delay of above 2 seconds.
		prev_state = cloud_state
		sleep(2)
	except:
		print "break"
		break
