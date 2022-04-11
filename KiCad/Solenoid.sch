EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title "Detail: Solenoid or Motor Driver"
Date "2022-04-10"
Rev ""
Comp ""
Comment1 "Use solenoid OR motor circuit"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L dk_Diodes-Rectifiers-Single:1N4004-T_NRND D?
U 1 1 5F12D291
P 3850 2250
F 0 "D?" V 3903 2172 60  0000 R CNN
F 1 "1N4001" V 3797 2172 60  0000 R CNN
F 2 "digikey-footprints:DO-41" H 4050 2450 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds28002.pdf" H 4050 2550 60  0001 L CNN
F 4 "1N4004DICT-ND" H 4050 2650 60  0001 L CNN "Digi-Key_PN"
F 5 "1N4004-T" H 4050 2750 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 4050 2850 60  0001 L CNN "Category"
F 7 "Diodes - Rectifiers - Single" H 4050 2950 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds28002.pdf" H 4050 3050 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/1N4004-T/1N4004DICT-ND/160593" H 4050 3150 60  0001 L CNN "DK_Detail_Page"
F 10 "DIODE GEN PURP 400V 1A DO41" H 4050 3250 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 4050 3350 60  0001 L CNN "Manufacturer"
F 12 "Not For New Designs" H 4050 3450 60  0001 L CNN "Status"
	1    3850 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:L L?
U 1 1 5F12EEBA
P 4850 2250
F 0 "L?" H 4903 2296 50  0000 L CNN
F 1 "L" H 4903 2205 50  0000 L CNN
F 2 "" H 4850 2250 50  0001 C CNN
F 3 "~" H 4850 2250 50  0001 C CNN
	1    4850 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1850 4850 1950
Wire Wire Line
	3850 2050 3850 1950
Wire Wire Line
	3850 1950 4850 1950
Connection ~ 4850 1950
Wire Wire Line
	4850 1950 4850 2100
Wire Wire Line
	4850 2400 4850 2450
Wire Wire Line
	3850 2450 4850 2450
Text HLabel 3400 1850 0    59   Input ~ 0
Red_8V
Text HLabel 3550 2900 0    59   Input ~ 0
Green_CTL
Text HLabel 3550 3200 0    59   Input ~ 0
Black_GND
Text HLabel 6000 3200 2    59   Output ~ 0
Yellow_SENSE
Wire Wire Line
	3400 1850 4850 1850
Text Notes 11100 1700 2    157  ~ 31
see alternative https://cdn-shop-adafruit.com/product-files/412/solenoid_driver.pdf
Text Notes 7050 2650 0    79   ~ 16
Solenoid circuit connects when ready to fire,\n   disconnects when pulled out for loading.
$Comp
L dk_Transistors-FETs-MOSFETs-Single:FQP30N06L Q?
U 1 1 615DBD24
P 4850 2800
F 0 "Q?" H 4958 2853 60  0000 L CNN
F 1 "STP55NE06" H 4958 2747 60  0000 L CNN
F 2 "digikey-footprints:TO-220-3" H 5050 3000 60  0001 L CNN
F 3 "https://www.onsemi.com/pub/Collateral/FQP30N06L-D.pdf" H 5050 3100 60  0001 L CNN
F 4 "FQP30N06L-ND" H 5050 3200 60  0001 L CNN "Digi-Key_PN"
F 5 "FQP30N06L" H 5050 3300 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 5050 3400 60  0001 L CNN "Category"
F 7 "Transistors - FETs, MOSFETs - Single" H 5050 3500 60  0001 L CNN "Family"
F 8 "https://www.onsemi.com/pub/Collateral/FQP30N06L-D.pdf" H 5050 3600 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/on-semiconductor/FQP30N06L/FQP30N06L-ND/1055122" H 5050 3700 60  0001 L CNN "DK_Detail_Page"
F 10 "MOSFET N-CH 60V 32A TO-220" H 5050 3800 60  0001 L CNN "Description"
F 11 "ON Semiconductor" H 5050 3900 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5050 4000 60  0001 L CNN "Status"
	1    4850 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 3200 4850 3200
Wire Wire Line
	4850 2450 4850 2600
Connection ~ 4850 2450
Connection ~ 4850 2600
Wire Wire Line
	4850 2600 4850 3000
Connection ~ 4850 3200
Wire Wire Line
	4850 3200 6000 3200
$Comp
L Device:R_US R?
U 1 1 615DF9FD
P 5850 2750
F 0 "R?" H 5918 2796 50  0000 L CNN
F 1 "100K" H 5918 2705 50  0000 L CNN
F 2 "" V 5890 2740 50  0001 C CNN
F 3 "~" H 5850 2750 50  0001 C CNN
	1    5850 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 2900 5850 3000
Wire Wire Line
	5850 3000 4850 3000
Connection ~ 4850 3000
Wire Wire Line
	4850 3000 4850 3200
Text Notes 5050 2250 0    79   ~ 0
Solenoid is BH14D-257-B-4
Wire Wire Line
	4550 2900 3550 2900
Wire Wire Line
	4850 2450 5850 2450
Wire Wire Line
	5850 2450 5850 2600
$Comp
L dk_PMIC-Voltage-Regulators-Linear:LD1117V33 U?
U 1 1 6254E98F
P 4000 4350
F 0 "U?" H 4000 4637 60  0000 C CNN
F 1 "LD1117V33" H 4000 4531 60  0000 C CNN
F 2 "digikey-footprints:TO-220-3" H 4200 4550 60  0001 L CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/99/3b/7d/91/91/51/4b/be/CD00000544.pdf/files/CD00000544.pdf/jcr:content/translations/en.CD00000544.pdf" H 4200 4650 60  0001 L CNN
F 4 "497-1491-5-ND" H 4200 4750 60  0001 L CNN "Digi-Key_PN"
F 5 "LD1117V33" H 4200 4850 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 4200 4950 60  0001 L CNN "Category"
F 7 "PMIC - Voltage Regulators - Linear" H 4200 5050 60  0001 L CNN "Family"
F 8 "http://www.st.com/content/ccc/resource/technical/document/datasheet/99/3b/7d/91/91/51/4b/be/CD00000544.pdf/files/CD00000544.pdf/jcr:content/translations/en.CD00000544.pdf" H 4200 5150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/stmicroelectronics/LD1117V33/497-1491-5-ND/586012" H 4200 5250 60  0001 L CNN "DK_Detail_Page"
F 10 "IC REG LINEAR 3.3V 800MA TO220AB" H 4200 5350 60  0001 L CNN "Description"
F 11 "STMicroelectronics" H 4200 5450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 4200 5550 60  0001 L CNN "Status"
	1    4000 4350
	1    0    0    -1  
$EndComp
$Comp
L dk_Transistors-Bipolar-BJT-Single:TIP120 Q?
U 1 1 625511D4
P 5500 4900
F 0 "Q?" H 5688 4953 60  0000 L CNN
F 1 "TIP120" H 5688 4847 60  0000 L CNN
F 2 "digikey-footprints:TO-220-3" H 5700 5100 60  0001 L CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/f9/ed/f5/44/26/b9/43/a4/CD00000911.pdf/files/CD00000911.pdf/jcr:content/translations/en.CD00000911.pdf" H 5700 5200 60  0001 L CNN
F 4 "497-2539-5-ND" H 5700 5300 60  0001 L CNN "Digi-Key_PN"
F 5 "TIP120" H 5700 5400 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 5700 5500 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 5700 5600 60  0001 L CNN "Family"
F 8 "http://www.st.com/content/ccc/resource/technical/document/datasheet/f9/ed/f5/44/26/b9/43/a4/CD00000911.pdf/files/CD00000911.pdf/jcr:content/translations/en.CD00000911.pdf" H 5700 5700 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/stmicroelectronics/TIP120/497-2539-5-ND/603564" H 5700 5800 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN DARL 60V 5A TO-220" H 5700 5900 60  0001 L CNN "Description"
F 11 "STMicroelectronics" H 5700 6000 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5700 6100 60  0001 L CNN "Status"
	1    5500 4900
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4001 D?
U 1 1 625518E9
P 5000 3850
F 0 "D?" H 5000 4066 50  0000 C CNN
F 1 "1N4001" H 5000 3975 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5000 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5000 3850 50  0001 C CNN
	1    5000 3850
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC M?
U 1 1 625528DB
P 4900 4350
F 0 "M?" V 5195 4300 50  0000 C CNN
F 1 "Motor_DC" V 5104 4300 50  0000 C CNN
F 2 "" H 4900 4260 50  0001 C CNN
F 3 "~" H 4900 4260 50  0001 C CNN
	1    4900 4350
	0    -1   -1   0   
$EndComp
Text HLabel 3350 5700 0    59   Input ~ 0
Black_GND
Text HLabel 4600 4900 0    59   Input ~ 0
Green_CTL
Text HLabel 3350 4350 0    59   Input ~ 0
Red_8V
Wire Wire Line
	3350 4350 3700 4350
Wire Wire Line
	4300 4350 4700 4350
Wire Wire Line
	4850 3850 4750 3850
Wire Wire Line
	4750 3850 4750 4350
Wire Wire Line
	5150 3850 5200 3850
Wire Wire Line
	5200 3850 5200 4350
Wire Wire Line
	5200 4350 5600 4350
Wire Wire Line
	5600 4350 5600 4700
Connection ~ 5200 4350
Wire Wire Line
	5600 5100 5600 5700
Wire Wire Line
	5600 5700 4000 5700
Wire Wire Line
	4000 4650 4000 5700
Connection ~ 4000 5700
Wire Wire Line
	4000 5700 3350 5700
Text HLabel 6550 5700 2    59   Output ~ 0
Yellow_SENSE
Wire Wire Line
	5600 5700 6550 5700
Connection ~ 5600 5700
Text Notes 1650 2400 0    79   ~ 16
Solenoid circuit - SILVER
Text Notes 1650 5050 0    79   ~ 16
Motor Circuit - SIDEWINDER
Text Notes 5550 4150 0    79   ~ 0
Motor is Mini Motor Low-speed Gearbox (4-speed) by Tamiya 70189**860.\n  assembled with 661.2:1 gear ratio
$Comp
L Device:R_US R?
U 1 1 62576287
P 4950 4900
F 0 "R?" H 5018 4946 50  0000 L CNN
F 1 "1K" H 5018 4855 50  0000 L CNN
F 2 "" V 4990 4890 50  0001 C CNN
F 3 "~" H 4950 4900 50  0001 C CNN
	1    4950 4900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4600 4900 4800 4900
Wire Wire Line
	5100 4900 5300 4900
$EndSCHEMATC
