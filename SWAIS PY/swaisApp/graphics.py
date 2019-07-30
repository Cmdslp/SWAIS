from tkinter import *
import tkinter as swaisApp
import os
import sys
import shutil
import glob
import fileinput
import zipfile
import serial.tools.list_ports
from tkinter import messagebox
import subprocess as sub



from itertools import islice
from subprocess import Popen, PIPE
from textwrap import dedent
from threading import Thread



str1 = ("void loop()")
str2 = ("inputs->InS_Rain_Sensor = 0")


#Extract automatic generated code 
def extractZIPfile():
	
	if os.path.isdir(os.getcwd() + r'\automaticCode\WAIS v'):
		shutil.rmtree(os.getcwd() + r'\automaticcode\WAIS v')
	
	for filename in [ os.getcwd()+'\\automaticCode\WAIS v.zip' ]:
		print ('%20s  %s' % (filename, zipfile.is_zipfile(filename)))

	if zipfile.is_zipfile(filename):
		print('\nCompressed .zip file exists...Extracting')
		zip_ref = zipfile.ZipFile(os.getcwd()+'\\automaticCode\WAIS v.zip', 'r')
		zip_ref.extractall(os.getcwd()+'\\automaticCode')
		zip_ref.close()
		print('OK!\n\n')
	else:
		print('No .zip file found...\n\n')

#Delete unecessary automatic generated files from IOPT Tools
def deleteFiles():
	path = os.getcwd()+'\\automaticCode\WAIS v'
	print('Deleting unnecessary files... ')

	# if os.path.exists(path+'\tmp_iopt.ino'):
		# os.remove(path+'\tmp_iopt.ino')
	# else:
		# print("The file tmp_iopt.ino does not exist !")
		
	if os.path.exists(path + '\dummy_gpio.c'):
		os.remove(path + '\dummy_gpio.c')
	else:
		print("The file dummy_gpio.c does not exist !")
		
	if os.path.exists(path + '\http_server.c'):
		os.remove(path + '\http_server.c')
	else:
		print("The file http_server.c does not exist !")
	
	if os.path.exists(path + '\http_server.h'):
		os.remove(path + '\http_server.h')
	else:
		print("The file http_server.h does not exist !")
	
	if os.path.exists(path + '\linux_sys_gpio.c'):
		os.remove(path + '\linux_sys_gpio.c')
	else:
		print("The file linux_sys_gpio.c does not exist !")
	
	if os.path.exists(path + '\Makefile'):
		os.remove(path + '\Makefile')
	else:
		print("The file Makefile does not exist !")
	
	if os.path.exists(path + '\\net_dbginfo.c'):
		os.remove(path + '\\net_dbginfo.c')
	else:
		print("The file net_dbginfo.c does not exist !")
	
	if os.path.exists(path + '\\net_server.c'):
		os.remove(path + '\\net_server.c')
	else:
		print("The file net_server.c does not exist !")
	
	if os.path.exists(path + '\\net_server.h'):
		os.remove(path + '\\net_server.h')
	else:
		print("The file net_server.h does not exist !")
	
	if os.path.exists(path + '\\raspi_mmap_gpio.c'):
		os.remove(path + '\\raspi_mmap_gpio.c')
	else:
		print("The file raspi_mmap_gpio.c does not exist !")

	print("OK!\n\n")

#Rename automatic generated files from IOPT Tool to .ino extension
def renameFiles():
	path = os.getcwd()+'\\automaticCode\WAIS v'
	
	# files = glob.glob(os.getcwd()+'\\automaticCode\WAIS v\*')
	# for f in files:
		# os.remove(f)
	
	print('Renaming files extensions...')
		
	if os.path.exists(path + '\\net_main.c'):
		os.rename(path + '\\net_main.c', path + '\\net_main.ino')	
	else:
		print("The file net_main.c does not exist !")
	
	if os.path.exists(path + '\\net_functions.c'):
		os.rename(path + '\\net_functions.c', path + '\\net_functions.ino')
	else:
		print("The file net_functions.c does not exist !")
	
	if os.path.exists(path + '\\net_io.c'):
		os.rename(path + '\\net_io.c', path + '\\net_io.ino')
	else:
		print("The file net_io.c does not exist !")
	
	if os.path.exists(path + '\\net_exec_step.c'):
		os.rename(path + '\\net_exec_step.c', path + '\\net_exec_step.ino')
	else:
		print("The file net_exec_step.c does not exist !")
	
	print('OK!\n\n')

#Copy the manual developed files to the automaticCode folder
def manualToautomatic():
	print('Copy manual developed files to the automaticCode folder...')
	src_fldr = os.getcwd()+'\\manualCode'
	dst_fldr = os.getcwd()+'\\automaticCode\WAIS v'
	files = os.listdir(src_fldr)
	for txt_file in glob.glob(src_fldr+"\\*.*"):
		shutil.copy2(txt_file, dst_fldr);
	print('OK!\n\n')	
	
#Find loop() code line number in manual developed code
def find_Loop_Line():
	path = (os.getcwd()+'\\automaticCode\WAIS v')
	loopLine=0
	ln=0
	file = open(path + r'\LoRa_Rx_Local_System20032019.ino','r')	
	
	for line in file.readlines():
		ln += 1
		line = line.rstrip()  # remove '\n' at end of line
		if line.find(str1) >= 0:
			#print('Found ' + str + ' in line ', ln)
			loopLine=ln # Setup()line
	file.close()
	#print('Found ' + str1 + ' in line ', loopLine)
	return loopLine
	
#Find input-> code lines number in automated generated code	
def find_Input_Line():
	path = (os.getcwd()+'\\automaticCode\WAIS v')
	inputLine=0
	ln=0
	file = open(path + r'\net_io.ino','r')	
	for line in file.readlines():
		ln += 1
		line = line.rstrip()  # remove '\n' at end of line
		if line.find(str2) >= 0:
			#print('Found ' + str + ' in line ', ln)
			inputLine=ln # input->InS_Rain_Sensor line
			break
	file.close()
	#print('Found ' + str2 + ' in line ', inputLine)
	return inputLine	

#Open manual developed code and reads the loop cicle and writes in the new file tmp_iopt.ino
def copyLoop(): 
	print('Copy loop  function files...')
	path = (os.getcwd()+'\\manualCode')
	path2 = (os.getcwd()+'\\automaticCode\WAIS v')
	file = open(path + r'\LoRa_Rx_Local_System20032019.ino','r')
	copy = open(path2 + r'\tmp_iopt.ino','a') 
	for i, line in enumerate(file):
		if i > find_Loop_Line():
			copy.write(line) 
			#print(line)
	#print(data)
	file.close()
	copy.close()
	print('OK!\n\n')

#Write IOPT code lines and manual code in tmp_iopt file
def copySetup():
	print('Copy setup  function files...')
	path = (os.getcwd()+'\\automaticCode\WAIS v')
	with open(path + r'\tmp_iopt.ino', mode = 'w',encoding = 'utf-8') as file:

		file.write('#include "Rx.h"\n')
		file.write("#include <ArduinoJson.h>\n")
		file.write("#include <SoftwareSerial.h>\n")
		file.write("#include <stdlib.h>\n")
		file.write('#include "net_types.h"\n')
		file.write("\n")
		file.write("int trace_control = TRACE_CONT_RUN;\n")
		file.write("\n")
		file.write("static WAIS_v_7_NetMarking marking;\n")
		file.write("static WAIS_v_7_InputSignals inputs, prev_inputs;\n")
		file.write("static WAIS_v_7_PlaceOutputSignals place_out;\n")
		file.write("static WAIS_v_7_EventOutputSignals ev_out;\n")
		file.write("\n")
		file.write("void setup(){\n")
		file.write("	createInitial_WAIS_v_7_NetMarking( &marking );\n")
		file.write("	init_WAIS_v_7_OutputSignals( &place_out, &ev_out );\n")
		file.write("	WAIS_v_7_InitializeIO();\n")
		file.write("	WAIS_v_7_GetInputSignals( &prev_inputs, NULL );\n")
		file.write("\n")
		file.write("	Serial.begin(9600);\n")
		file.write("	LoraSerial.begin(9600);\n")
		file.write("	pinMode(RCV_LED_PIN, OUTPUT);\n")
		file.write("	pinMode(SIZE_ERR_PIN, OUTPUT);\n")
		file.write("	pinMode(SEND_LED_PIN, OUTPUT);\n")
		file.write("	configLoRa();\n")
		file.write("	resetLoRa();\n")
		file.write("	delay(200);\n")
		file.write("}\n")
		file.write("\n")
		file.write("void(* resetFunc) (void) = 0; //declare reset function @ address 0\n")
		file.write("\n")
		file.write("\n")
		file.write("void loop(){\n")
		file.write("\n")
		file.write("if( trace_control != TRACE_PAUSE )\n")
		file.write("	WAIS_v_7_ExecutionStep( &marking, &inputs, &prev_inputs, &place_out, &ev_out );\n")
		file.write("else WAIS_v_7_GetInputSignals( &inputs, NULL );\n")
		file.write("if( trace_control > TRACE_PAUSE ) --trace_control;\n")
		file.write("\n")
		file.close()
	print('OK!\n\n')

#Read all input signal lines from iopt automatic generated code and replace them with variables from manual generated code
def replaceInputs():
	print('Replace input signal code lines...')
	filename = (os.getcwd() + r'\automaticCode\WAIS v\net_io.ino')
	inputSignals = {'    inputs->InS_Rain_Sensor = 0;':'    inputs->InS_Rain_Sensor = inputIOPTrainSensorValue;', '    inputs->InS_Soil_Humidity_Sensor = 0;':'    inputs->InS_Soil_Humidity_Sensor = 20;'}
	for line in fileinput.input(filename, inplace=True):
		line = line.rstrip('\r\n')
		print(inputSignals.get(line, line))
	print('OK!\n\n')

#Replace output signal lines in net_io.ino
def replaceOutputs():
	print('Replace output signal code lines...')
	filename = (os.getcwd() + r'\automaticCode\WAIS v\net_io.ino')
	outputSignals = {'    /* event_out->OuS_Valve */':'    if (event_out->OuS_Valve == 1){\n        digitalWrite(10, HIGH);\n    }else{\n        digitalWrite(10, LOW);\n    }\n'}
	for line in fileinput.input(filename, inplace=True):
		line = line.rstrip('\r\n')
		print(outputSignals.get(line, line))
	print('OK!\n\n')

#Copy changed files to the new folder swais_main
def copyNewfolder():
	print('Copy changed files to the new folder...')
	src_fldr = os.getcwd() + r'\automaticCode\WAIS v'
	dst_fldr = os.getcwd() + r'\swais_main'
	files = os.listdir(src_fldr)
	for txt_file in glob.glob(src_fldr + "\\*.*"):
		shutil.copy2(txt_file, dst_fldr);
	print('OK!\n\n')


def verifyCOM():
	
	print('Verify COM ports avaiable...')
	ports = serial.tools.list_ports.comports()
	for port, desc, hwid in sorted(ports):
		print("{}: {} [{}]".format(port, desc, hwid))
	print('OK!\n\n')
	
	
def sendToMCU():
	print('Compile code to MCU...')
	#"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-objcopy.exe" -I ihex IOPT_20032019.ino.hex -O binary IOPT_20032019.ino.bin
	# Change to project folder 
	#print('Changind folder...\n')
	os.chdir("/")
	os.chdir("C:/Users/César Penha/AppData/Local/Temp/arduino_build_752414")
	#print(os.getcwd())
	path_avrdude = 'C:/Program Files (x86)/Arduino/hardware/tools/avr/etc/avrdude.conf'
	path_avrdude = os.path.normpath(path_avrdude);
	pathFile = ('avrdude -v -patmega328p -carduino -PCOM9 -b57600 -D -Uflash:w:IOPT_20032019.ino.hex -D -C "'+path_avrdude+'"')
	os.system(pathFile)
	print('OK!\n\n')


def callback():
	print ("click!")
	os.system('cls')

	#arg 1 : saber folder onde se encontra o zip do iopt tools
	#arg 2 : saber onde se encontra os files desenvolvidos manualmente
	#arg 3 : saber qual o caminho da  pasta de destino 

	# print('sys.argv[0] =', sys.argv[0])             
	# pathname = os.path.dirname(sys.argv[0])        
	# print('path =', pathname)
	# print('full path =', os.path.abspath(pathname)) 



	extractZIPfile()

	deleteFiles()

	renameFiles()

	manualToautomatic()

	copySetup()

	copyLoop()

	replaceInputs()

	replaceOutputs()


	#Rename tmp_iopt.ino to swais_main.ino
	if os.path.exists(os.getcwd() + r'\automaticCode\WAIS v\tmp_iopt.ino'):
		if os.path.isfile(os.getcwd() + 'r\automaticCode\WAIS v\swais_main.ino'): #True -> Se existir apaga
			os.remove(os.getcwd() + r'\automaticCode\WAIS v\swais_main.ino')
		os.rename(os.getcwd() + r'\automaticCode\WAIS v\tmp_iopt.ino', os.getcwd() + '\\automaticCode\WAIS v\swais_main.ino')	
	else:
		print('The file tmp_iopt.c does not exist !\n\n')

	#Create the new output directory
	if os.path.isdir(os.getcwd() + r'\swais_main'):
		shutil.rmtree(os.getcwd() + r'\swais_main')
	os.mkdir(os.getcwd() + r'\swais_main')
	print ('Successfully created the directory: %s' % os.getcwd() + r'\swais_main')
	print('\n\n')

	copyNewfolder()
		
	#Remove the unecessary original manual developed files from swais_main
	os.remove(os.getcwd() + r'\swais_main\LoRa_Rx_Local_System20032019.ino')
	os.remove(os.getcwd() + r'\swais_main\net_main.ino')

	# Verify COM port avaiable
	verifyCOM()

	# Send the code to microcontroller
	sendToMCU()

	#convert .hex em .bin
	#os.system("C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-objcopy.exe" "-I ihex IOPT_20032019.ino.hex -O binary IOPT_20032019.ino.bin")

	os.chdir(r"C:/Users/César Penha/Desktop/SWAIS PY")

	
	
	print(os.getcwd())
	messagebox.showinfo("Information","SWAIS Code Finished !")
	print('EVERYTHING DONE !\n\n')


master = swaisApp.Tk()

master.iconbitmap("swais_ico.ico")
master.title('SWAIS')
frame = Frame(master, height=100, width=400)
frame.pack_propagate(0)
frame.grid(row=3, column=3, columnspan=3)

btn_text = swaisApp.StringVar()
btn_text.trace("w", callback)
btn_text.set("GENERATE CODE")
buttonGenerate = Button(master, textvariable=btn_text, command=callback)
buttonGenerate.grid(row=2, column=2, columnspan=10, rowspan=10)

master.mainloop()

















