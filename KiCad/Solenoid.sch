EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title "Detail: Solenoid Driver"
Date "2021-10-05"
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
F 1 "1N4001" V 5097 3272 60  0000 R CNN
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
	5150 3550 5150 3800
Wire Wire Line
	5150 3800 6150 3800
Text HLabel 2500 2500 0    59   Input ~ 0
Red_8V
Text HLabel 2350 4550 0    59   Input ~ 0
Green_CTL
Text HLabel 2500 5500 0    59   Input ~ 0
Black_GND
Text HLabel 8050 5500 2    59   Output ~ 0
Yellow_SENSE
Wire Wire Line
	2500 2500 6150 2500
Text Notes 11050 1250 2    157  ~ 31
see alternative https://cdn-shop-adafruit.com/product-files/412/solenoid_driver.pdf
Text Notes 2950 6400 0    79   ~ 16
Solenoid circuit connects when ready to fire,\n   disconnects when pulled out for loading.
$Comp
L dk_Transistors-FETs-MOSFETs-Single:FQP30N06L Q?
U 1 1 615DBD24
P 6150 4450
F 0 "Q?" H 6258 4503 60  0000 L CNN
F 1 "STP55NE06" H 6258 4397 60  0000 L CNN
F 2 "digikey-footprints:TO-220-3" H 6350 4650 60  0001 L CNN
F 3 "https://www.onsemi.com/pub/Collateral/FQP30N06L-D.pdf" H 6350 4750 60  0001 L CNN
F 4 "FQP30N06L-ND" H 6350 4850 60  0001 L CNN "Digi-Key_PN"
F 5 "FQP30N06L" H 6350 4950 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 6350 5050 60  0001 L CNN "Category"
F 7 "Transistors - FETs, MOSFETs - Single" H 6350 5150 60  0001 L CNN "Family"
F 8 "https://www.onsemi.com/pub/Collateral/FQP30N06L-D.pdf" H 6350 5250 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/on-semiconductor/FQP30N06L/FQP30N06L-ND/1055122" H 6350 5350 60  0001 L CNN "DK_Detail_Page"
F 10 "MOSFET N-CH 60V 32A TO-220" H 6350 5450 60  0001 L CNN "Description"
F 11 "ON Semiconductor" H 6350 5550 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6350 5650 60  0001 L CNN "Status"
	1    6150 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5500 6150 5500
Wire Wire Line
	6150 3800 6150 4250
Connection ~ 6150 3800
Connection ~ 6150 4250
Wire Wire Line
	6150 4250 6150 4300
Wire Wire Line
	6150 4650 6150 5050
Connection ~ 6150 5500
Wire Wire Line
	6150 5500 8050 5500
$Comp
L Device:R_US R?
U 1 1 615DF9FD
P 7150 4450
F 0 "R?" H 7218 4496 50  0000 L CNN
F 1 "100K" H 7218 4405 50  0000 L CNN
F 2 "" V 7190 4440 50  0001 C CNN
F 3 "~" H 7150 4450 50  0001 C CNN
	1    7150 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3800 7150 3800
Wire Wire Line
	7150 3800 7150 4300
Wire Wire Line
	7150 4600 7150 5050
Wire Wire Line
	7150 5050 6150 5050
Connection ~ 6150 5050
Wire Wire Line
	6150 5050 6150 5500
Text Notes 6400 3350 0    79   ~ 0
Solenoid is BH14D-257-B-4
Wire Wire Line
	5850 4550 2350 4550
$EndSCHEMATC
