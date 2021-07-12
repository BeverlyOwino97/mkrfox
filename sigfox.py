# -*- coding: utf-8 -*-
"""
Created on Thu June 17 16:21:34 2021

@author: bevakinyi
"""


import paho.mqtt.client as mqtt
import json
from influxdb import InfluxDBClient

INFLUXDB_DATABASE = 'techgsm'

WRITE_API_KEY = "88AV5P0SAJGD504K"
CHANNEL_ID = 1407158
READ_API_KEY = "44R0FICEJYE2RSG9"
MQTT_ADDRESS = 'mqtt.thingspeak.com'
MQTT_USER = 'gsm2'
MQTT_PASSWORD = 'NJOXL2SQHURNCH8Q'


MQTT_TOPIC  = 'channels/1407158/subscribe/json/44R0FICEJYE2RSG9'
MQTT_CLIENT_ID = 'MQTTInfluxDBBridge'

influxdb_client = InfluxDBClient(host='35.230.100.15', port=8086, username='admin', password='bK2eCWuuAJHTgPRE',ssl=True)


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe(MQTT_TOPIC)


def on_message(client, userdata, msg):
    print(msg.topic+" "+ msg.payload.decode('utf-8'))
    savedata(msg.topic , msg.payload.decode('utf-8'))

# influxdb
def savedata(topic, data):
    #client = InfluxDBClient(INFLUXDB_ADDRESS, 8086, 'root', '', 'Sensor') 
    
    data = json.loads(data)
    datas = [
        {
            "measurement": "distance",
            "tags": {
                "topic": topic
            },
            "fields": data
        }
    ]
    
    influxdb_client.write_points(datas)
    
def _init_influxdb_database():
    databases = influxdb_client.get_list_database()
    if len(list(filter(lambda x: x['name'] == INFLUXDB_DATABASE, databases))) == 0:
        influxdb_client.create_database(INFLUXDB_DATABASE)
    influxdb_client.switch_database(INFLUXDB_DATABASE)
    '''result = list(influxdb_client.query('select * from distance').get_points())
    print(result) '''

def main():
    _init_influxdb_database()


    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.username_pw_set(MQTT_USER,MQTT_PASSWORD)
    client.connect(MQTT_ADDRESS, 1883, 60)
    client.loop_forever()
    
if __name__ == '__main__':
    print('MQTT to InfluxDB bridge')
    main()