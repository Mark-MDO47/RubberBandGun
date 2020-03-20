EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "Rubber Band Gun"
Date "2020-03-20"
Rev "---"
Comp ""
Comment1 "Solenoid Circuit"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 1600 2050 0    118  Input ~ 0
+7.4V
Text HLabel 1400 5950 0    118  Input ~ 0
GND
Text HLabel 1600 4150 0    118  Input ~ 0
Solenoid
Text HLabel 10150 3500 2    118  Output ~ 0
Cnct
$Comp
L dk_Transistors-Bipolar-BJT-Single:TIP120 Q?
U 1 1 5E74F659
P 5350 4150
F 0 "Q?" H 5538 4203 60  0000 L CNN
F 1 "TIP120" H 5538 4097 60  0000 L CNN
F 2 "digikey-footprints:TO-220-3" H 5550 4350 60  0001 L CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/f9/ed/f5/44/26/b9/43/a4/CD00000911.pdf/files/CD00000911.pdf/jcr:content/translations/en.CD00000911.pdf" H 5550 4450 60  0001 L CNN
F 4 "497-2539-5-ND" H 5550 4550 60  0001 L CNN "Digi-Key_PN"
F 5 "TIP120" H 5550 4650 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 5550 4750 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 5550 4850 60  0001 L CNN "Family"
F 8 "http://www.st.com/content/ccc/resource/technical/document/datasheet/f9/ed/f5/44/26/b9/43/a4/CD00000911.pdf/files/CD00000911.pdf/jcr:content/translations/en.CD00000911.pdf" H 5550 4950 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/stmicroelectronics/TIP120/497-2539-5-ND/603564" H 5550 5050 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN DARL 60V 5A TO-220" H 5550 5150 60  0001 L CNN "Description"
F 11 "STMicroelectronics" H 5550 5250 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5550 5350 60  0001 L CNN "Status"
	1    5350 4150
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4004 D?
U 1 1 5E75324C
P 4850 3250
F 0 "D?" V 4804 3329 50  0000 L CNN
F 1 "1N4004" V 4895 3329 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 4850 3075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4850 3250 50  0001 C CNN
	1    4850 3250
	0    1    1    0   
$EndComp
$Comp
L Device:L L?
U 1 1 5E754503
P 5450 3250
F 0 "L?" H 5503 3296 50  0000 L CNN
F 1 "L" H 5503 3205 50  0000 L CNN
F 2 "" H 5450 3250 50  0001 C CNN
F 3 "~" H 5450 3250 50  0001 C CNN
	1    5450 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2050 5450 2050
Wire Wire Line
	5450 2050 5450 2800
Wire Wire Line
	5450 2800 4850 2800
Wire Wire Line
	4850 2800 4850 3100
Connection ~ 5450 2800
Wire Wire Line
	5450 2800 5450 3100
Wire Wire Line
	5450 3950 5450 3700
Wire Wire Line
	4850 3400 4850 3700
Wire Wire Line
	4850 3700 5450 3700
Connection ~ 5450 3700
Wire Wire Line
	5450 3700 5450 3400
Wire Wire Line
	1450 5950 5450 5950
Wire Wire Line
	5450 5950 5450 4350
Wire Wire Line
	5450 5950 8950 5950
Connection ~ 5450 5950
Wire Wire Line
	10150 3500 8950 3500
Wire Wire Line
	8950 3500 8950 5950
$Comp
L Device:R R?
U 1 1 5E75A301
P 4400 4150
F 0 "R?" V 4193 4150 50  0000 C CNN
F 1 "2.2K" V 4284 4150 50  0000 C CNN
F 2 "" V 4330 4150 50  0001 C CNN
F 3 "~" H 4400 4150 50  0001 C CNN
	1    4400 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 4150 5150 4150
Wire Wire Line
	4250 4150 1600 4150
Text Notes 2400 1350 0    118  ~ 0
Derived from https://cdn-shop.adafruit.com/product-files/412/solenoid_driver.pdf
$EndSCHEMATC
