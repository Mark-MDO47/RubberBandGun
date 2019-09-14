EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:mdoLibrary
LIBS:Arduino_Nano-cache
LIBS:GradCap2017-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SW_SPST_LED SW?
U 1 1 5B063DEB
P 2550 1950
F 0 "SW?" H 2575 2175 50  0000 L CNN
F 1 "SW_SPST_LED" H 2550 1825 50  0000 C CNN
F 2 "" H 2550 2250 50  0001 C CNN
F 3 "" H 2550 2250 50  0001 C CNN
	1    2550 1950
	1    0    0    -1  
$EndComp
$Comp
L SW_SPST SW?
U 1 1 5B064065
P 2450 4800
F 0 "SW?" H 2450 4925 50  0000 C CNN
F 1 "SW_SPST" H 2450 4700 50  0000 C CNN
F 2 "" H 2450 4800 50  0001 C CNN
F 3 "" H 2450 4800 50  0001 C CNN
	1    2450 4800
	1    0    0    -1  
$EndComp
$Comp
L UBEC J?
U 1 1 5B0640A0
P 3600 4900
F 0 "J?" H 3600 4900 60  0000 C CNN
F 1 "UBEC" H 3600 5000 60  0000 C CNN
F 2 "" H 3600 4900 60  0001 C CNN
F 3 "" H 3600 4900 60  0001 C CNN
	1    3600 4900
	1    0    0    -1  
$EndComp
$Comp
L UBEC J?
U 1 1 5B064219
P 7250 1950
F 0 "J?" H 7250 1950 60  0000 C CNN
F 1 "UBEC" H 7250 2050 60  0000 C CNN
F 2 "" H 7250 1950 60  0001 C CNN
F 3 "" H 7250 1950 60  0001 C CNN
	1    7250 1950
	1    0    0    -1  
$EndComp
$Comp
L Battery BT?
U 1 1 5B0646F6
P 1050 1900
F 0 "BT?" H 1150 2000 50  0000 L CNN
F 1 "Battery" H 1150 1900 50  0000 L CNN
F 2 "" V 1050 1960 50  0001 C CNN
F 3 "" V 1050 1960 50  0001 C CNN
	1    1050 1900
	1    0    0    -1  
$EndComp
$Comp
L Battery BT?
U 1 1 5B06472D
P 1000 4800
F 0 "BT?" H 1100 4900 50  0000 L CNN
F 1 "Battery" H 1100 4800 50  0000 L CNN
F 2 "" V 1000 4860 50  0001 C CNN
F 3 "" V 1000 4860 50  0001 C CNN
	1    1000 4800
	1    0    0    -1  
$EndComp
$Comp
L LEDring Z?
U 1 1 5B064AB4
P 9600 1600
F 0 "Z?" H 9600 1600 60  0000 C CNN
F 1 "LEDring" H 9600 1750 60  0000 C CNN
F 2 "" H 9600 1750 60  0001 C CNN
F 3 "" H 9600 1750 60  0001 C CNN
	1    9600 1600
	1    0    0    -1  
$EndComp
$Comp
L Arduino A?
U 1 1 5B064E47
P 5600 5450
F 0 "A?" H 5600 5450 60  0000 C CNN
F 1 "Arduino" H 5600 5550 60  0000 C CNN
F 2 "" H 5600 5450 60  0000 C CNN
F 3 "" H 5600 5450 60  0000 C CNN
	1    5600 5450
	1    0    0    -1  
$EndComp
Text Notes 5100 4450 0    197  ~ 39
Times 4
Text Notes 9000 850  0    197  ~ 39
Times 4
Wire Wire Line
	4300 5050 5000 5050
Wire Wire Line
	7950 2100 7950 6400
Wire Wire Line
	7950 6400 4300 6400
Wire Wire Line
	4300 6400 4300 5050
Wire Wire Line
	9550 2300 9550 2500
Wire Wire Line
	9550 2500 7950 2500
Connection ~ 7950 2500
Wire Wire Line
	7950 1700 7950 950 
Wire Wire Line
	7950 950  10350 950 
Wire Wire Line
	10350 950  10350 2500
Wire Wire Line
	10350 2500 9650 2500
Wire Wire Line
	9650 2500 9650 2300
Wire Wire Line
	2650 4800 3100 4800
Wire Wire Line
	3100 4800 3100 4650
Wire Wire Line
	1000 5000 1000 5050
Wire Wire Line
	1000 5050 3100 5050
Wire Wire Line
	1000 4600 2250 4600
Wire Wire Line
	2250 4600 2250 4800
Wire Wire Line
	1050 1700 2350 1700
Wire Wire Line
	2350 1700 2350 1850
Wire Wire Line
	1050 2100 1050 2300
Wire Wire Line
	1050 2300 6750 2300
Wire Wire Line
	6750 2300 6750 2100
Wire Wire Line
	2750 1850 6750 1850
Wire Wire Line
	6750 1850 6750 1700
Wire Wire Line
	2900 1850 2900 1950
Wire Wire Line
	2900 1950 2750 1950
Connection ~ 2900 1850
$Comp
L R R?
U 1 1 5B0651BC
P 2150 2150
F 0 "R?" V 2230 2150 50  0000 C CNN
F 1 "R" V 2150 2150 50  0000 C CNN
F 2 "" V 2080 2150 50  0001 C CNN
F 3 "" H 2150 2150 50  0001 C CNN
	1    2150 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1950 2150 1950
Wire Wire Line
	2150 1950 2150 2000
Wire Wire Line
	4300 4650 4300 4550
Wire Wire Line
	4300 4550 6500 4550
Wire Wire Line
	6500 4550 6500 5050
Wire Wire Line
	6500 5050 6200 5050
Wire Wire Line
	5000 5250 4700 5250
Wire Wire Line
	4700 5250 4700 6300
Wire Wire Line
	4700 6300 9750 6300
Wire Wire Line
	9750 6300 9750 2300
Text Notes 1400 4400 0    197  ~ 39
Knife Switch
Text Notes 1900 1500 0    197  ~ 39
LED Switch
Text Notes 1800 2500 0    118  ~ 0
5.5K Ohm
Text Notes 7550 3900 0    118  ~ 0
Times 2
Text Notes 9350 3900 0    118  ~ 0
Times 4
$Comp
L CAP U?
U 1 1 5B0781E4
P 7350 3000
F 0 "U?" H 7350 3000 60  0001 C CNN
F 1 "CAP" H 8650 2700 60  0000 C CNN
F 2 "" H 7350 3000 60  0001 C CNN
F 3 "" H 7350 3000 60  0001 C CNN
	1    7350 3000
	1    0    0    -1  
$EndComp
Text Notes 8150 3000 0    197  ~ 39
Grad Cap
$EndSCHEMATC
