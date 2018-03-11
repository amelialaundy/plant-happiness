import serial
import time as time
import sys
from datetime import datetime
from datetime import timedelta 
ser = serial.Serial('/dev/ttyACM1', 9600)
now = datetime.now()

file_name = 'plant-reading-{0}.txt'.format(now.strftime('%Y-%m-%d %H:%M:%S'))

file = open(file_name,"w")

future_date = now + timedelta(hours=12)

while (datetime.now() < future_date):
    try:
        line = ser.readline()
        print(line)
        formatted_line = line.decode("utf-8")
        file.write(formatted_line)
        if (formatted_line.startswith("Soil humidity:")):
            file.write(datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
            file.write('\n\n')
    except:
        print(sys.exc_info()[0])
        file.close()
        raise
        

file.close()
