import urllib
import httplib
import serial
import time
import os

key = 'CR01TTKM5380SCYU'
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
ser2 = serial.Serial('/dev/ttyUSB1', 9600, timeout=1)
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
    global tmp,hum,light,rain,airdust,UNOtmp,UNOhum,adc
    try:
        ser.write('T\r\n')
        tmp = float(ser.readline())
        print 'Temperature: ' + str(tmp) + ' C'
    except:
        print 'ERROR GET Temperature value'
        
    try:
        ser.write('H\r\n')
        hum = float(ser.readline())
        print 'Humidity:    ' + str(hum) + ' %'
    except:
        print 'ERROR GET Humidity value'
        
    try:
        ser.write('L\r\n')
        light = int(ser.readline())
        print 'Light:       ' + str(light) + ' lux'
    except:
        print 'ERROR GET Light value'
        
    try:
        ser.write('R\r\n')
        rain = int(ser.readline())
        print 'Check if is rainng: ' + str(bool(rain))
    except:
        print 'ERROR GET Rain state'
        
    try:
        ser.write('A\r\n')
        airdust = long(ser.readline())
    except:
        print 'ERROR GET Airdust value'
        
    calcVoltage = airdust * (5.0 / 1024)
    dustDensity = (0.17 * calcVoltage - 0.1)*1000
    print 'Airdust value: ' + str(dustDensity)
        
    try:
        ser.write('U\r\n')
        adc = float(ser.readline())
        print 'adc value:   ' + str(adc)
    except:
        print 'ERROR GET Airdust value'

    transmit(str(999))
    UNOtmp = float(ser2.readline())
    transmit(str(899))
    UNOhum = float(ser2.readline())

    transmit(str((tmp*100)+10000))
    transmit(str((hum*100)+20000))
    transmit(str(light+30000))
    transmit(str(rain+40000))
    transmit(str(airdust+50000))
    
    print 'Local Temperature: ' + str(UNOtmp) + ' C'
    print 'Local Humidity:    ' + str(UNOhum) + ' %'
    
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
    headers = {'Content-type': 'application/x-www-form-urlencoded',
               'Accept': 'text/plain'}
    conn = httplib.HTTPConnection('api.thingspeak.com:80')
    try:
        conn.request('POST', '/update', params, headers)
        response = conn.getresponse()
        print 'Thingspeak connection status:'
        print response.status
        print response.reason
        data = response.read()
        conn.close()
    except:
        print "connection to thingspeak failed"
        
    try:
        httpServ = httplib.HTTPConnection('127.0.0.1:80')
        httpServ.connect()
        httpServ.request('GET', '/print.php?temp='+str(tmp)+'&hum='+str(hum)+'&light='+str(light)+'&rain='+str(rain)+'&airdust='+str(airdust)+'&UNOtmp='+str(UNOtmp)+'&UNOhum='+str(UNOhum))
        response = httpServ.getresponse()
        print 'Local database connection status:'
        print response.status
        print response.reason
        #if response.status == httplib.OK:
        #    httpServ.close()
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
        
