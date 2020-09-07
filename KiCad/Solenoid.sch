EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title "Detail: Solenoid Driver"
Date "2020-09-07"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L dk_Diodes-Rectifiers-Single:1N4004-T_NRND D?
U 1 1 5F12D291
P 5150 3350
F 0 "D?" V 5203 3272 60  0000 R CNN
F 1 "1N4004-T_NRND" V 5097 3272 60  0000 R CNN
F 2 "digikey-footprints:DO-41" H 5350 3550 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds28002.pdf" H 5350 3650 60  0001 L CNN
F 4 "1N4004DICT-ND" H 5350 3750 60  0001 L CNN "Digi-Key_PN"
F 5 "1N4004-T" H 5350 3850 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 5350 3950 60  0001 L CNN "Category"
F 7 "Diodes - Rectifiers - Single" H 5350 4050 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds28002.pdf" H 5350 4150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/1N4004-T/1N4004DICT-ND/160593" H 5350 4250 60  0001 L CNN "DK_Detail_Page"
F 10 "DIODE GEN PURP 400V 1A DO41" H 5350 4350 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 5350 4450 60  0001 L CNN "Manufacturer"
F 12 "Not For New Designs" H 5350 4550 60  0001 L CNN "Status"
	1    5150 3350
	0    -1   -1   0   
$EndComp
$Comp
L Device:L L?
U 1 1 5F12EEBA
P 6150 3300
F 0 "L?" H 6203 3346 50  0000 L CNN
F 1 "L" H 6203 3255 50  0000 L CNN
F 2 "" H 6150 3300 50  0001 C CNN
F 3 "~" H 6150 3300 50  0001 C CNN
	1    6150 3300
	1    0    0    -1  
$EndComp
$Comp
L dk_Transistors-Bipolar-BJT-Single:TIP120 Q?
U 1 1 5F12FE09
P 6050 4500
F 0 "Q?" H 6238 4553 60  0000 L CNN
F 1 "TIP120" H 6238 4447 60  0000 L CNN
F 2 "digikey-footprints:TO-220-3" H 6250 4700 60  0001 L CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/f9/ed/f5/44/26/b9/43/a4/CD00000911.pdf/files/CD00000911.pdf/jcr:content/translations/en.CD00000911.pdf" H 6250 4800 60  0001 L CNN
F 4 "497-2539-5-ND" H 6250 4900 60  0001 L CNN "Digi-Key_PN"
F 5 "TIP120" H 6250 5000 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 6250 5100 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 6250 5200 60  0001 L CNN "Family"
F 8 "http://www.st.com/content/ccc/resource/technical/document/datasheet/f9/ed/f5/44/26/b9/43/a4/CD00000911.pdf/files/CD00000911.pdf/jcr:content/translations/en.CD00000911.pdf" H 6250 5300 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/stmicroelectronics/TIP120/497-2539-5-ND/603564" H 6250 5400 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN DARL 60V 5A TO-220" H 6250 5500 60  0001 L CNN "Description"
F 11 "STMicroelectronics" H 6250 5600 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6250 5700 60  0001 L CNN "Status"
	1    6050 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F130714
P 4300 4500
F 0 "R?" V 4093 4500 50  0000 C CNN
F 1 "2.2K" V 4184 4500 50  0000 C CNN
F 2 "" V 4230 4500 50  0001 C CNN
F 3 "~" H 4300 4500 50  0001 C CNN
	1    4300 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	6150 2500 6150 2950
Wire Wire Line
	5150 3150 5150 2950
Wire Wire Line
	5150 2950 6150 2950
Connection ~ 6150 2950
Wire Wire Line
	6150 2950 6150 3150
Wire Wire Line
	6150 3450 6150 3800
Wire Wire Line
	5850 4500 4450 4500
Wire Wire Line
	5150 3550 5150 3800
Wire Wire Line
	5150 3800 6150 3800
Connection ~ 6150 3800
Wire Wire Line
	6150 3800 6150 4300
Text HLabel 2500 2500 0    59   Input ~ 0
White_8V
Text HLabel 2500 4500 0    59   Input ~ 0
Blue_CTL
Text HLabel 2500 5500 0    59   Input ~ 0
Black_GND
Text HLabel 8050 5500 2    59   Output ~ 0
Yellow_SENSE
Wire Wire Line
	2500 5500 6150 5500
Wire Wire Line
	6150 5500 6150 4700
Wire Wire Line
	8050 5500 6150 5500
Connection ~ 6150 5500
Wire Wire Line
	2500 4500 4150 4500
Wire Wire Line
	2500 2500 6150 2500
Text Notes 10850 1650 2    157  ~ 31
Derived from https://cdn-shop-adafruit.com/product-files/412/solenoid_driver.pdf
Text Notes 2950 6400 0    79   ~ 16
Solenoid circuit connects when ready to fire,\n   disconnects when pulled out for loading.
$EndSCHEMATC
