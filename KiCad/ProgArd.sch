EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title "Programming Arduino"
Date "2021-09-05"
Rev ""
Comp ""
Comment1 "--- if wiring from bottom, reverse left and right"
Comment2 "Note - Arduino shown top view with notch on top"
Comment3 ""
Comment4 "Programs the KCX_BT_EMITTER Bluetooth Module"
$EndDescr
$Comp
L mdoLibrary:Arduino A?
U 1 1 5F566EBE
P 5650 4350
F 0 "A?" H 5650 5337 60  0000 C CNN
F 1 "Arduino" H 5650 5231 60  0000 C CNN
F 2 "" H 5650 4350 60  0000 C CNN
F 3 "" H 5650 4350 60  0000 C CNN
	1    5650 4350
	1    0    0    -1  
$EndComp
Text Notes 5100 3100 0    79   ~ 16
Programming Arduino does not need to be a Nano.\nIt must be an Arduino with 5V interfaces\nPower via USB and use Serial Monitor to control
Text HLabel 4650 3950 0    79   Input ~ 16
GND
Text HLabel 4650 4750 0    79   Input ~ 16
9_TX
Text HLabel 4650 4450 0    79   Input ~ 16
2_RX
Wire Wire Line
	4650 4750 5050 4750
Text Notes 3800 4800 0    79   ~ 16
YELLOW
Text Notes 3800 4500 0    79   ~ 16
GREEN
Text Notes 3800 4000 0    79   ~ 16
BLACK
Text Notes 4150 2450 0    79   ~ 16
Only connect Programming Arduino\nwhen programming KCX_BT_EMITTER\nBluetooth Audio Module
Text Notes 3150 6100 0    79   ~ 16
These 3 connectors should be male jumper wires.\nUse the color code suggested to avoid connection errors.\nMatching labels to female jumpers suggested:\n   GND\n   2 RX\n   9 TX
Wire Wire Line
	4650 4450 4850 4450
Wire Wire Line
	4850 4450 4850 4050
Wire Wire Line
	4850 4050 5050 4050
Wire Wire Line
	4650 3950 5050 3950
$EndSCHEMATC
