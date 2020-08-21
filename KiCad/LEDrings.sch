EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date "2020-08-21"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L mdoLibrary:LEDring Z?
U 1 1 5F1537C1
P 3150 2850
F 0 "Z?" H 3710 2811 60  0000 L CNN
F 1 "LEDring" H 3710 2705 60  0000 L CNN
F 2 "" H 3150 3000 60  0001 C CNN
F 3 "" H 3150 3000 60  0001 C CNN
	1    3150 2850
	1    0    0    -1  
$EndComp
$Comp
L mdoLibrary:LEDring Z?
U 1 1 5F155A52
P 3100 5200
F 0 "Z?" H 3660 5161 60  0000 L CNN
F 1 "LEDring" H 3660 5055 60  0000 L CNN
F 2 "" H 3100 5350 60  0001 C CNN
F 3 "" H 3100 5350 60  0001 C CNN
	1    3100 5200
	1    0    0    -1  
$EndComp
$Comp
L mdoLibrary:LEDring_med Z?
U 1 1 5F16160C
P 5200 2600
F 0 "Z?" H 6028 2570 60  0000 L CNN
F 1 "LEDring_med" H 6028 2464 60  0000 L CNN
F 2 "" H 5200 2750 60  0001 C CNN
F 3 "" H 5200 2750 60  0001 C CNN
	1    5200 2600
	1    0    0    -1  
$EndComp
$Comp
L mdoLibrary:LEDring_big Z?
U 1 1 5F167885
P 7800 2450
F 0 "Z?" H 8828 2445 60  0000 L CNN
F 1 "LEDring_big" H 8828 2339 60  0000 L CNN
F 2 "" H 7800 2600 60  0001 C CNN
F 3 "" H 7800 2600 60  0001 C CNN
	1    7800 2450
	1    0    0    -1  
$EndComp
$Comp
L mdoLibrary:LEDring_med Z?
U 1 1 5F170202
P 5200 4950
F 0 "Z?" H 6028 4920 60  0000 L CNN
F 1 "LEDring_med" H 6028 4814 60  0000 L CNN
F 2 "" H 5200 5100 60  0001 C CNN
F 3 "" H 5200 5100 60  0001 C CNN
	1    5200 4950
	1    0    0    -1  
$EndComp
$Comp
L mdoLibrary:LEDring_big Z?
U 1 1 5F170C6C
P 7800 4800
F 0 "Z?" H 8828 4795 60  0000 L CNN
F 1 "LEDring_big" H 8828 4689 60  0000 L CNN
F 2 "" H 7800 4950 60  0001 C CNN
F 3 "" H 7800 4950 60  0001 C CNN
	1    7800 4800
	1    0    0    -1  
$EndComp
Text Notes 5750 1800 2    79   ~ 0
Front Facing Group
Text Notes 5800 4150 2    79   ~ 0
Rear Facing Group
Text HLabel 1050 3650 0    79   Input ~ 0
DIN
Text HLabel 1050 4400 0    79   Input ~ 0
5V
Text HLabel 1050 4050 0    79   Input ~ 0
GND
Wire Wire Line
	1050 3650 1500 3650
Wire Wire Line
	1500 3650 1500 1000
Wire Wire Line
	1500 1000 10450 1000
Wire Wire Line
	10450 1000 10450 3550
Wire Wire Line
	10450 3550 7950 3550
Wire Wire Line
	7600 3550 5350 3550
Wire Wire Line
	5050 3550 3300 3550
Wire Wire Line
	7950 5900 10450 5900
Wire Wire Line
	10450 5900 10450 3550
Connection ~ 10450 3550
Wire Wire Line
	7600 5900 5350 5900
Wire Wire Line
	5050 5900 3250 5900
Wire Wire Line
	1700 4050 1050 4050
Wire Wire Line
	3100 3550 3100 3650
Wire Wire Line
	3100 3650 1700 3650
Wire Wire Line
	1700 3650 1700 4050
Wire Wire Line
	3100 3650 5150 3650
Wire Wire Line
	5150 3650 5150 3550
Connection ~ 3100 3650
Wire Wire Line
	5150 3650 7750 3650
Wire Wire Line
	7750 3650 7750 3550
Connection ~ 5150 3650
Wire Wire Line
	7850 3550 7850 3750
Wire Wire Line
	7850 3750 5250 3750
Wire Wire Line
	1800 3750 1800 4400
Wire Wire Line
	1800 4400 1050 4400
Wire Wire Line
	3200 3550 3200 3750
Connection ~ 3200 3750
Wire Wire Line
	3200 3750 1800 3750
Wire Wire Line
	5250 3550 5250 3750
Connection ~ 5250 3750
Wire Wire Line
	5250 3750 3200 3750
Wire Wire Line
	3050 5900 3050 6050
Wire Wire Line
	3050 6050 1700 6050
Wire Wire Line
	1700 6050 1700 4050
Connection ~ 1700 4050
Wire Wire Line
	3050 6050 5150 6050
Wire Wire Line
	5150 6050 5150 5900
Connection ~ 3050 6050
Wire Wire Line
	5150 6050 7750 6050
Wire Wire Line
	7750 6050 7750 5900
Connection ~ 5150 6050
Wire Wire Line
	3150 5900 3150 6200
Wire Wire Line
	3150 6200 1800 6200
Wire Wire Line
	1800 6200 1800 4400
Connection ~ 1800 4400
Wire Wire Line
	5250 5900 5250 6200
Wire Wire Line
	5250 6200 3150 6200
Connection ~ 3150 6200
Wire Wire Line
	7850 5900 7850 6200
Wire Wire Line
	7850 6200 5250 6200
Connection ~ 5250 6200
$EndSCHEMATC
