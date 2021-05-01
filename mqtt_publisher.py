import paho.mqtt.client as mqtt

mqttc = mqtt.Client()
mqttc.connect("localhost",1883,60)
mqttc.loop_start()

mqttc.publish("test","1100")