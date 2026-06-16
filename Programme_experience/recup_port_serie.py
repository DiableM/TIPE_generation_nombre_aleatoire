import serial
import time
from datetime import datetime

# set up the serial line
sensor="pile"
serial_port = '/dev/ttyACM0'
baud_rate=2000000
ser = serial.Serial(serial_port, baud_rate)
time.sleep(1)

path = "/media/msoucaze/Partage/Data{}.txt"
t_start = time.time()
nb_par_fichier = 100000
nb_fichier = 1
initial = 0

for i in range(initial, nb_fichier+initial):
   output_file = open(path.format(i), "w+")
   for j in range(nb_par_fichier):
      line = ser.readline()
      line = line.strip()
      if (len(line) != 4):
         print("Pb dans le moniteur série", line, j, "fichier", i) #affiche une alerte en cas de différence de longueur dans le moniteur série
      try:
         line_str = str(line,'UTF-8')
         output_file.writelines([line_str,"\n"])
      except:
         pass

   print("fin fichier ", i)
   output_file.close()

t_final = time.time()
output_file.close()
print("temp execution {}s".format(t_final-t_start)) #affiche le temps d'acquisition