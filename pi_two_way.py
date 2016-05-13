import urllib
import httplib
import serial
import time
import os

key = '50K4ERTOTXTA8GX4'
ser = serial.Serial('/dev/ttyUSB1', 9600, timeout=1)
ser2 = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
tmp = 0.0
hum = 0.0
light = 0
rain = 0
airdust = 0
UNOtmp = 0
UNOhum = 0
adc = 0.0
#/dev/ttyUSB0
#/dev/ttyUSB1
def sendData():
    try:
        ser.write('Start_nano\r\n')
        print 'Start_nano'
        #print ser.readline()
        global tmp,hum,light,rain,airdust,UNOtmp,UNOhum,adc
        tmp = float(ser.readline())
        hum = float(ser.readline())
        light = int(ser.readline())
        rain = int(ser.readline())
        airdust = int(ser.readline())
        adc = float(ser.readline())
    except:
        print 'ERROR serial1'
    
    print 'Temperature: ' + str(tmp) + ' C'
    print 'Humidity:    ' + str(hum) + ' %'
    print 'Light:       ' + str(light) + ' lux'
    print 'Check if is rainng: ' + str(bool(rain))
    calcVoltage = airdust * (5.0 / 1024)
    dustDensity = (0.17 * calcVoltage - 0.1)*1000
    print 'Airdust value: ' + str(dustDensity)
    print 'adc value:   ' + str(adc)

    transmit((tmp*100)+10000)
    transmit((hum*100)+20000)
    transmit(str(light+30000))
    transmit(str(rain+40000))
    transmit(str(airdust+50000))

    params = urllib.urlencode({
        'field1': tmp,
        'field2': hum,
        'field3': light,
        'field4': rain,
        'field5': dustDensity,
        'field6': UNOtmp,
        'field7': UNOhum,
        'key': key,
        })
    headers = {'Content-typZZe': 'application/x-www-form-urlencoded',
               'Accept': 'text/plain'}
    conn = httplib.HTTPConnection('api.thingspeak.com:80')
    try:
        conn.request('POST', '/update', params, headers)
        response = conn.getresponse()
        print 'Thingspeak connection start'
        print response.status
        print response.reason
        data = response.read()
        conn.close()
    except:
        print "connection to thingspeak failed"
        
    try:
        httpServ = httplib.HTTPConnection("127.0.0.1", 80)
        httpServ.connect()
        httpServ.request('GET', '/print.php?temp='+str(tmp)+'&hum='+str(hum)+'&light='+str(light)+'&rain='+str(rain)+'&airdust='+str(dustDensity)+'&UNOtmp='+str(UNOtmp)+'&UNOhum='+str(UNOhum)+'')
        response = httpServ.getresponse()
        print 'Local database connection start'
        print response.status
        print response.reason
        if response.status == httplib.OK:
            httpServ.close()
    except:
        print  "connection to local server failed"

def sendTime():
    try:
        ser2.write('Adj_time')
        print 'Adj_time'
        ser2.write(time.strftime("%S"))       #second
        ser2.write(time.strftime("%M"))      #minutes
        ser2.write(time.strftime("%H"))      #hour
        ser2.write(time.strftime("%w"))      #day of week
        ser2.write(time.strftime("%d"))      #day
        ser2.write(time.strftime("%m"))     #month
        ser2.write(time.strftime("%Y"))      #year
    except:

        # seconds, minutes, hours, day of the week, day of the month, month, year

        print "ERROR adjTime"
def transmit(data):

        ser2.write(str(data))
        try:

                ser2.readline()
        except:
                print 'read ERROR'


if __name__ == '__main__':
    while True:
        os.system('cls' if os.name == 'nt' else 'clear')
        time.sleep(5)
        sendData()
        time.sleep(10)
        
