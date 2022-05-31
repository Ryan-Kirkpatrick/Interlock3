import paho.mqtt.client as mqtt
import random

brokerAddr = "192.168.1.102"
brokerPort = 1883
outTopic = "AccessControl/Auth/FrontDoor"
inTopic = "AccessControl/CardSwipes/+"
logTopic = "AccessControl/Log/+"

with open("testcards.txt", "r") as file:
    cards = file.read()
    mqttReponse = str(hash(cards))+"\n"+cards
    print(mqttReponse)

def on_message(client, userdata, msg):
    msg_string = msg.payload.decode("utf-8")
    print(f"{msg_string} in {msg.topic}")
    if msg.topic == inTopic:
        client.publish(outTopic, str(mqttReponse))

client = mqtt.Client()
client.connect(brokerAddr, brokerPort)
client.subscribe(inTopic)
client.on_message = on_message
client.loop_forever()