import urllib
import httplib
import serial

key = '50K4ERTOTXTA8GX4'
ser = serial.Serial('dev/ttyUSB0', 9600, timeout = 1)
ser2 = serial.Serial('dev/ttyISB1', 9600, timeout = 1)
def sendData():
    try:
        tmp = int(ser.readline())
        hum = int(ser.readline())
        
    params = urllib.urlencode({'field1':temp, 'key':key})
    headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
    conn = httplib.HTTPConnection("api.thingspeak.com:80")
    try:
        conn.request("POST", "/update", params, headers)
        response = conn.getresponse()
        print response.status
        print response.reason
        data = response.read()
        conn.close()
    except:
        print "connection failed"
if __name__ == "__main__":
    while True:
        sendData()
