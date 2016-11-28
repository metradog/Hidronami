import serial
import string
import MySQLdb
import pprint
import time

db = MySQLdb.connect(host="db4free.net", # your host, usually localhost
                     user="hidronami", # your username
                      passwd="hidronami", # your password
                      db="hidronami") # name of the data base
cur = db.cursor() 

arduinoPort = 'COM5'
ser = serial.Serial('COM5', 9600, timeout=0)

ser.setPort(arduinoPort) #boundRate 9600 automatically set




ser.setTimeout(6)

try:
        ser.open()
#except: 
#       print('Wow, dude: error!')
except Exception as e: print(e) #Visualiza el error encontrado
        

#else:
for i in range (51):
                
                ardString = ser.readline() #Leyendo el valor del arduino
                poop = float(ardString)
                cambio = [poop]
                
              
                ##valueMatrix= ardString.split(' ')
                if int(i)%2 == 0  :
                        print('----------------------------------')
                        print(i)
                        print('Temperatura:')
                        print(ardString)
                        print('----------------------------------')
                        cur.execute('INSERT INTO temperatura (temperatura, fecha) VALUES (%s, now())', cambio)
                        db.commit()
                else:
                        print('----------------------------------')
                        print(i)
                        print('Caudal:')
                        print(ardString)
                        print('----------------------------------')
                        cur.execute('INSERT INTO caudal (caudal, fecha) VALUES (%s, now())', cambio)
                        db.commit()

ser.close()
print('connection closed')
db.close()
print('database closed')
print('end')
