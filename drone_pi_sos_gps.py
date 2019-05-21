import sys
import time
from Adafruit_IO import MQTTClient, Feed, Client

ADAFRUIT_IO_KEY      = 'f9a9be44e75144ac94d31ae666cedc68'
ADAFRUIT_IO_USERNAME = 'Scintilladist'
SOS_GPS_LOC = '0.000000,0.000000'

def connected(client):
    print('Connected to Adafruit IO!  Listening for SOS signals...')
    client.subscribe('sos')
    
def disconnected(client):
    print('Disconnected from Adafruit IO!')
    sys.exit(1)

def message(client, feed_id, payload):
    print('SOS ALERT!')
    if feed_id == 'sos':
        if payload != '0.000000,0.000000':
            SOS_GPS_LOC = payload
            print('{0} Alert at: {1}'.format(feed_id, payload))
        else:
            print('{0} GPS not locked in ERROR: {1}'.format(feed_id, payload))

client = MQTTClient(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

client.on_connect    = connected
client.on_disconnect = disconnected
client.on_message    = message

client.connect()
client.loop_blocking()





















