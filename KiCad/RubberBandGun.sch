EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 4
Title "FOOF Rubber Band Gun"
Date "2021-09-05"
Rev "---"
Comp ""
Comment1 "--- if wiring from bottom, reverse sides"
Comment2 "NOTE: chips/modules shown top view with notch at top"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR0102
U 1 1 5A3DEBCE
P 1250 4950
F 0 "#PWR0102" H 1250 4700 50  0001 C CNN
F 1 "GND" H 1250 4800 50  0000 C CNN
F 2 "" H 1250 4950 50  0001 C CNN
F 3 "" H 1250 4950 50  0001 C CNN
	1    1250 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5A459198
P 5000 1600
F 0 "R?" V 5080 1600 50  0000 C CNN
F 1 "220 ohm" V 4900 1600 50  0000 C CNN
F 2 "" V 4930 1600 50  0001 C CNN
F 3 "" H 5000 1600 50  0001 C CNN
	1    5000 1600
	-1   0    0    1   
$EndComp
$Comp
L mdoLibrary:UBEC #J0101
U 1 1 5A459C5D
P 2050 4450
F 0 "#J0101" H 2050 4450 60  0000 C CNN
F 1 "UBEC" H 2050 4550 60  0000 C CNN
F 2 "" H 2050 4450 60  0001 C CNN
F 3 "" H 2050 4450 60  0001 C CNN
	1    2050 4450
	1    0    0    -1  
$EndComp
$Comp
L mdoLibrary:Arduino A?
U 1 1 5A480803
P 5950 2400
F 0 "A?" H 5950 2400 60  0000 C CNN
F 1 "Arduino" H 5950 2500 60  0000 C CNN
F 2 "" H 5950 2400 60  0000 C CNN
F 3 "" H 5950 2400 60  0000 C CNN
	1    5950 2400
	1    0    0    -1  
$EndComp
$Comp
L switches:SW_Push SW?
U 1 1 5A4908F2
P 3600 4300
F 0 "SW?" H 3750 4410 50  0000 C CNN
F 1 "SW_PUSH" H 3600 4220 50  0000 C CNN
F 2 "" H 3600 4300 60  0000 C CNN
F 3 "" H 3600 4300 60  0000 C CNN
	1    3600 4300
	0    -1   -1   0   
$EndComp
$Comp
L switches:SW_Push SW?
U 1 1 5A490A22
P 4000 4300
F 0 "SW?" H 4150 4410 50  0000 C CNN
F 1 "SW_PUSH" H 4000 4220 50  0000 C CNN
F 2 "" H 4000 4300 60  0000 C CNN
F 3 "" H 4000 4300 60  0000 C CNN
	1    4000 4300
	0    -1   -1   0   
$EndComp
$Comp
L switches:SW_Push SW?
U 1 1 5A490A65
P 3800 5000
F 0 "SW?" H 3950 5110 50  0000 C CNN
F 1 "SW_PUSH" H 3800 4920 50  0000 C CNN
F 2 "" H 3800 5000 60  0000 C CNN
F 3 "" H 3800 5000 60  0000 C CNN
	1    3800 5000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5A49671E
P 3600 1250
F 0 "R?" V 3680 1250 50  0000 C CNN
F 1 "10K" V 3600 1250 50  0000 C CNN
F 2 "" V 3530 1250 30  0000 C CNN
F 3 "" H 3600 1250 30  0000 C CNN
	1    3600 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5A496756
P 3800 1250
F 0 "R?" V 3880 1250 50  0000 C CNN
F 1 "10K" V 3800 1250 50  0000 C CNN
F 2 "" V 3730 1250 30  0000 C CNN
F 3 "" H 3800 1250 30  0000 C CNN
	1    3800 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5A496794
P 4000 1250
F 0 "R?" V 4080 1250 50  0000 C CNN
F 1 "10K" V 4000 1250 50  0000 C CNN
F 2 "" V 3930 1250 30  0000 C CNN
F 3 "" H 4000 1250 30  0000 C CNN
	1    4000 1250
	1    0    0    -1  
$EndComp
Text Notes 5650 3300 0    60   ~ 0
Arduino Nano
$Comp
L Device:R R?
U 1 1 5A767559
P 4200 1250
F 0 "R?" V 4280 1250 50  0000 C CNN
F 1 "10K" V 4200 1250 50  0000 C CNN
F 2 "" V 4130 1250 30  0000 C CNN
F 3 "" H 4200 1250 30  0000 C CNN
	1    4200 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:Speaker LS?
U 1 1 5D7C69A9
P 4600 4200
F 0 "LS?" H 4650 4425 50  0000 R CNN
F 1 "Speaker" H 4650 4350 50  0000 R CNN
F 2 "" H 4600 4000 50  0001 C CNN
F 3 "" H 4590 4150 50  0001 C CNN
	1    4600 4200
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5D7D3856
P 4400 1250
F 0 "R?" V 4480 1250 50  0000 C CNN
F 1 "10K" V 4400 1250 50  0000 C CNN
F 2 "" V 4330 1250 30  0000 C CNN
F 3 "" H 4400 1250 30  0000 C CNN
	1    4400 1250
	1    0    0    -1  
$EndComp
Text Notes 1450 3850 0    118  ~ 0
8.3 Volts
$Comp
L Device:R R?
U 1 1 5D915A72
P 4950 3500
F 0 "R?" V 5030 3500 50  0000 C CNN
F 1 "1K" V 4950 3500 50  0000 C CNN
F 2 "" V 4880 3500 50  0001 C CNN
F 3 "" H 4950 3500 50  0001 C CNN
	1    4950 3500
	1    0    0    -1  
$EndComp
Text Notes 2200 2300 0    60   ~ 0
D04 = Trigger
Text Notes 2200 2400 0    59   ~ 0
D05 = Yellow
Text Notes 2200 2500 0    59   ~ 0
D06 = Green
Text Notes 2200 2600 0    59   ~ 0
D07 = Red
Text Notes 2200 2900 0    59   ~ 0
D08 = Barrel (Yellow)\n    grounded = closed
$Comp
L switches:SW_Push SW?
U 1 1 5E22B63A
P 4200 5000
F 0 "SW?" H 4350 5110 50  0000 C CNN
F 1 "SW_PUSH" H 4200 4920 50  0000 C CNN
F 2 "" H 4200 5000 60  0000 C CNN
F 3 "" H 4200 5000 60  0000 C CNN
	1    4200 5000
	0    -1   -1   0   
$EndComp
$Comp
L mdoLibrary:YX5200 A?
U 1 1 5D90CF9F
P 6400 4600
F 0 "A?" H 6400 4500 60  0000 C CNN
F 1 "YX5200" H 6400 4400 60  0000 C TNN
F 2 "" H 6400 4600 60  0000 C CNN
F 3 "" H 6400 4600 60  0000 C CNN
	1    6400 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 4600 3050 4900
Wire Wire Line
	2750 4600 3050 4600
Wire Wire Line
	1250 4600 1550 4600
Wire Wire Line
	1250 4950 1250 4900
Wire Wire Line
	3200 4200 3050 4200
Wire Wire Line
	3200 950  3200 4200
Connection ~ 3400 6400
Wire Wire Line
	3400 6400 3400 2000
Wire Wire Line
	3400 2000 5350 2000
Wire Wire Line
	5350 2300 3600 2300
Wire Wire Line
	3600 1400 3600 2300
Wire Wire Line
	5350 2400 3800 2400
Wire Wire Line
	3800 1400 3800 2400
Wire Wire Line
	5350 2500 4000 2500
Wire Wire Line
	4000 1400 4000 2500
Wire Wire Line
	3600 4500 3600 6400
Connection ~ 3600 6400
Wire Wire Line
	3800 5200 3800 6400
Connection ~ 3800 6400
Wire Wire Line
	4000 4500 4000 6400
Connection ~ 4000 6400
Wire Wire Line
	3600 1100 3600 950 
Connection ~ 3600 950 
Wire Wire Line
	3800 950  3800 1100
Connection ~ 3800 950 
Wire Wire Line
	4000 950  4000 1100
Connection ~ 4000 950 
Connection ~ 3600 2300
Connection ~ 3800 2400
Connection ~ 4000 2500
Wire Wire Line
	9950 6000 9950 1800
Wire Wire Line
	6550 2000 6950 2000
Wire Wire Line
	4200 1100 4200 950 
Connection ~ 4200 950 
Wire Wire Line
	5350 2600 4200 2600
Connection ~ 4200 2600
Wire Wire Line
	4400 1100 4400 950 
Connection ~ 4400 950 
Wire Wire Line
	7000 4500 7050 4500
Wire Wire Line
	7050 4500 7050 6400
Connection ~ 7050 6400
Wire Wire Line
	4950 4000 5800 4000
Wire Wire Line
	4850 4100 5800 4100
Wire Wire Line
	4850 2900 4850 4100
Wire Wire Line
	4950 3000 4950 3350
Wire Wire Line
	4950 3650 4950 4000
Wire Wire Line
	5350 3000 4950 3000
Wire Wire Line
	5350 2900 4850 2900
Wire Wire Line
	7000 3900 7000 3700
Wire Wire Line
	7000 3700 5350 3700
Wire Wire Line
	5350 3700 5350 3100
Connection ~ 4200 6400
Wire Wire Line
	4200 1400 4200 2600
Wire Wire Line
	4200 5200 4200 6400
Wire Wire Line
	9050 2750 10050 2750
Wire Wire Line
	10050 2750 10050 1800
Wire Wire Line
	7600 3400 9850 3400
Connection ~ 9850 3400
Wire Wire Line
	9050 2550 9850 2550
Connection ~ 9850 2550
Wire Wire Line
	7600 3400 7600 2750
Wire Wire Line
	7600 2750 7850 2750
Wire Wire Line
	3200 950  3600 950 
Wire Wire Line
	9050 950  9050 2150
Wire Wire Line
	9350 2650 9050 2650
Wire Wire Line
	3400 6400 3050 6400
Wire Wire Line
	3600 6400 3400 6400
Wire Wire Line
	3800 6400 3600 6400
Wire Wire Line
	4000 6400 3800 6400
Wire Wire Line
	3600 950  3800 950 
Wire Wire Line
	3800 950  4000 950 
Wire Wire Line
	4000 950  4200 950 
Wire Wire Line
	3600 2300 3600 4100
Wire Wire Line
	3800 2400 3800 4800
Wire Wire Line
	4000 2500 4000 4100
Wire Wire Line
	4200 950  4400 950 
Wire Wire Line
	4200 2600 4200 4800
Wire Wire Line
	4200 6400 4000 6400
Wire Wire Line
	9850 3400 9850 6400
Wire Wire Line
	9850 2550 9850 3400
Wire Wire Line
	9850 1800 9850 2550
Wire Wire Line
	4400 1400 4400 2700
Wire Wire Line
	5350 2700 4400 2700
Connection ~ 4400 2700
Text Notes 6600 3100 0    59   ~ 0
D13 = Solenoid\n   (Blue)
Wire Wire Line
	6550 3100 7200 3100
Wire Wire Line
	3200 4200 3200 6000
Connection ~ 3200 4200
Wire Wire Line
	3200 6000 5150 6000
Wire Wire Line
	1250 4900 3050 4900
Connection ~ 1250 4900
Wire Wire Line
	1250 4900 1250 4600
Connection ~ 3050 4900
Wire Wire Line
	3050 4900 3050 6400
Text Notes 1750 5000 0    59   ~ 0
Yes - connect GND
Wire Wire Line
	6950 950  6950 2000
Connection ~ 6950 950 
Wire Wire Line
	6950 950  7750 950 
Wire Wire Line
	4200 6400 5250 6400
$Comp
L mdoLibrary:SN74HCT125N A?
U 1 1 5E333EFD
P 8450 2850
F 0 "A?" H 8450 2750 60  0000 C CNN
F 1 "SN74HCT125N" H 8450 2650 60  0000 C TNN
F 2 "" H 8450 2850 60  0000 C CNN
F 3 "" H 8450 2850 60  0000 C CNN
	1    8450 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3100 7200 4500
Wire Wire Line
	1400 750  1400 4200
Wire Wire Line
	1550 4200 1400 4200
$Comp
L power:+8V #PWR?
U 1 1 5F0E58C5
P 650 3950
F 0 "#PWR?" H 650 3800 50  0001 C CNN
F 1 "+8V" H 665 4123 50  0000 C CNN
F 2 "" H 650 3950 50  0001 C CNN
F 3 "" H 650 3950 50  0001 C CNN
	1    650  3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  4200 650  3950
Wire Wire Line
	7600 5000 8650 5000
Wire Wire Line
	7950 6400 7950 4850
Wire Wire Line
	7950 4850 8650 4850
Connection ~ 7950 6400
Wire Wire Line
	7950 6400 9850 6400
Wire Wire Line
	8650 4300 7500 4300
Wire Wire Line
	8650 4500 7200 4500
Text Notes 8300 4300 0    59   ~ 0
Red
Text Notes 8300 4500 0    59   ~ 0
Green
Text Notes 8300 4850 0    59   ~ 0
Black
Text Notes 8300 5000 0    59   ~ 0
Yellow
$Comp
L switches:SW_SPST SW?
U 1 1 5F12E089
P 1000 4200
F 0 "SW?" H 1000 4450 50  0001 C CNN
F 1 "ToggleSW" H 1000 4344 50  0000 C CNN
F 2 "" H 1000 4200 50  0001 C CNN
F 3 "" H 1000 4200 50  0001 C CNN
	1    1000 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  4200 800  4200
Wire Wire Line
	1200 4200 1400 4200
Connection ~ 1400 4200
Text Notes 8700 5000 0    157  ~ 31
U\nS\nB
$Sheet
S 8950 4200 700  900 
U 5F12AD06
F0 "Solenoid" 59
F1 "Solenoid.sch" 59
$EndSheet
Text HLabel 8950 4300 2    59   Input ~ 0
Red_8V
Text HLabel 8950 4500 2    59   Input ~ 0
Green_CTL
Text HLabel 8950 4850 2    59   Input ~ 0
Black_GND
Text HLabel 8950 5000 2    59   Output ~ 0
Yellow_SENSE
$Sheet
S 9500 900  850  900 
U 5F14546D
F0 "LEDrings" 79
F1 "LEDrings.sch" 0
$EndSheet
Text HLabel 9850 1800 1    59   Input ~ 0
GND
Text HLabel 9950 1800 1    59   Input ~ 0
5V
Text HLabel 10050 1800 1    59   Input ~ 0
DIN
Wire Wire Line
	4400 950  4550 950 
Wire Wire Line
	4550 3900 4550 950 
Wire Wire Line
	4550 3900 5800 3900
Connection ~ 4550 950 
Wire Wire Line
	4700 1100 9350 1100
Wire Wire Line
	9350 1100 9350 2650
$Comp
L mdoLibrary:WS2812bSingle U?
U 1 1 5F417DD5
P 8350 1300
F 0 "U?" H 8350 1300 79  0001 C CNN
F 1 "WS2812bSingle" H 8528 1250 79  0000 L CNN
F 2 "" H 8350 1300 79  0001 C CNN
F 3 "" H 8350 1300 79  0001 C CNN
	1    8350 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F41D9F7
P 4700 1600
F 0 "R?" V 4780 1600 50  0000 C CNN
F 1 "220 ohm" V 4600 1600 50  0000 C CNN
F 2 "" V 4630 1600 50  0001 C CNN
F 3 "" H 4700 1600 50  0001 C CNN
	1    4700 1600
	-1   0    0    1   
$EndComp
Wire Wire Line
	5350 2200 4700 2200
Wire Wire Line
	4700 2200 4700 1750
Wire Wire Line
	4700 1450 4700 1100
Wire Wire Line
	5350 2100 5000 2100
Wire Wire Line
	5000 2100 5000 1750
Wire Wire Line
	5000 1450 5000 1250
Wire Wire Line
	7500 4300 7500 750 
Wire Wire Line
	1400 750  7500 750 
$Comp
L mdoLibrary:BlueToothAudioR U?
U 1 1 5F4589F3
P 4700 4650
F 0 "U?" H 4700 4650 79  0001 C CNN
F 1 "BluetoothAudioModule" H 5100 3500 79  0000 C CNN
F 2 "" H 4700 4650 79  0001 C CNN
F 3 "" H 4700 4650 79  0001 C CNN
	1    4700 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 5900 4400 5900
Wire Wire Line
	4400 2700 4400 5900
Wire Wire Line
	7600 5000 7600 5900
Wire Wire Line
	5000 5700 5150 5700
Wire Wire Line
	5150 5700 5150 6000
Connection ~ 5150 6000
Wire Wire Line
	5150 6000 9950 6000
Wire Wire Line
	5000 5600 5250 5600
Wire Wire Line
	5250 5600 5250 6400
Connection ~ 5250 6400
Wire Wire Line
	5000 1250 8000 1250
Wire Wire Line
	8000 1450 7600 1450
Wire Wire Line
	4550 950  6950 950 
Wire Wire Line
	7750 950  7750 1350
Connection ~ 7750 950 
Wire Wire Line
	7750 950  9050 950 
Wire Wire Line
	7750 1350 8000 1350
$Comp
L Device:C C?
U 1 1 5F4A44E0
P 3050 4400
F 0 "C?" H 3165 4446 50  0000 L CNN
F 1 "100uF" H 3165 4355 50  0000 L CNN
F 2 "" H 3088 4250 50  0001 C CNN
F 3 "~" H 3050 4400 50  0001 C CNN
	1    3050 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 4250 3050 4200
Connection ~ 3050 4200
Wire Wire Line
	3050 4200 2750 4200
Wire Wire Line
	3050 4550 3050 4600
Connection ~ 3050 4600
Wire Wire Line
	7600 2750 7600 1450
Connection ~ 7600 2750
Wire Wire Line
	7050 6400 7950 6400
Wire Wire Line
	5250 6400 7050 6400
$Comp
L conn:Conn_01x03_Female J?
U 1 1 5F539118
P 5450 5400
F 0 "J?" H 5478 5426 50  0001 L CNN
F 1 "Conn_Female" H 5000 5250 50  0000 L CNN
F 2 "" H 5450 5400 50  0001 C CNN
F 3 "~" H 5450 5400 50  0001 C CNN
	1    5450 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5600 5250 5500
Connection ~ 5250 5600
Text Notes 6050 5550 0    79   ~ 0
9 TX Yellow\n2 RX Green\nGND Black
$Sheet
S 3700 6950 500  500 
U 5F557D0B
F0 "Programming Arduino" 79
F1 "ProgArd.sch" 79
$EndSheet
Wire Wire Line
	5000 5300 5250 5300
Wire Wire Line
	5000 5400 5250 5400
Text HLabel 4200 7350 0    79   Input ~ 16
9_TX
Text HLabel 4200 7200 0    79   Input ~ 16
2_RX
Text HLabel 4200 7050 0    79   Input ~ 16
GND
$Comp
L conn:Conn_01x03_Male J?
U 1 1 5F5917B1
P 5600 5400
F 0 "J?" H 5708 5681 50  0001 C CNN
F 1 "Conn_Male" H 5800 5250 50  0000 C CNN
F 2 "" H 5600 5400 50  0001 C CNN
F 3 "~" H 5600 5400 50  0001 C CNN
	1    5600 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 7050 5850 7050
Wire Wire Line
	4200 7200 5950 7200
Wire Wire Line
	5950 7200 5950 5400
Wire Wire Line
	5950 5400 5800 5400
Text Notes 1500 7400 0    79   ~ 16
Only connect Programming Arduino\nwhen programming KCX_BT_EMITTER\nBluetooth Audio Module
Wire Wire Line
	5850 7050 5850 5500
Wire Wire Line
	6050 5300 6050 7350
Wire Wire Line
	4200 7350 6050 7350
Wire Wire Line
	6050 5300 5800 5300
Wire Wire Line
	5800 5500 5850 5500
Wire Wire Line
	4900 4600 4900 4300
Wire Wire Line
	4900 4300 4800 4300
Wire Wire Line
	5800 4200 5700 4200
Wire Wire Line
	5800 4300 5750 4300
Wire Wire Line
	5800 4500 5650 4500
Wire Wire Line
	5700 5100 5700 4200
Wire Wire Line
	5000 5100 5700 5100
Wire Wire Line
	5750 5200 5750 4300
Wire Wire Line
	5000 5200 5750 5200
Wire Wire Line
	5650 5000 5650 4500
Wire Wire Line
	5000 5000 5650 5000
$Comp
L mdoLibrary:SW_SPST SW?
U 1 1 5F5ADEC3
P 5250 4600
F 0 "SW?" H 5250 4835 50  0000 C CNN
F 1 "SW_SPST" H 5250 4744 50  0000 C CNN
F 2 "" H 5250 4600 50  0001 C CNN
F 3 "" H 5250 4600 50  0001 C CNN
	1    5250 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4600 5450 4600
Wire Wire Line
	5050 4600 4900 4600
Wire Wire Line
	5800 4400 5600 4400
Wire Wire Line
	5600 4400 5600 4200
Wire Wire Line
	4800 4200 5600 4200
$EndSCHEMATC
