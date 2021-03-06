EESchema Schematic File Version 4
LIBS:WifiLedButton-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Wifi LED Button"
Date "2018-12-20"
Rev "1.0"
Comp "Dr.-Ing. Thorsten Ludewig"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:LED D1
U 1 1 5C1BA2A7
P 5400 4050
F 0 "D1" V 5438 3933 50  0000 R CNN
F 1 "LED" V 5347 3933 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 5400 4050 50  0001 C CNN
F 3 "~" H 5400 4050 50  0001 C CNN
	1    5400 4050
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5C1BA512
P 5400 4700
F 0 "R2" H 5470 4746 50  0000 L CNN
F 1 "150Ω" H 5470 4655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5330 4700 50  0001 C CNN
F 3 "~" H 5400 4700 50  0001 C CNN
	1    5400 4700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 5C1BA6B2
P 5800 3450
F 0 "J1" H 5700 3650 50  0000 L CNN
F 1 "Conn_01x04_Female" H 5650 3100 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-4_1x04_P2.54mm_Horizontal" H 5800 3450 50  0001 C CNN
F 3 "~" H 5800 3450 50  0001 C CNN
	1    5800 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5C1BA7C2
P 5400 5000
F 0 "#PWR04" H 5400 4750 50  0001 C CNN
F 1 "GND" H 5405 4827 50  0000 C CNN
F 2 "" H 5400 5000 50  0001 C CNN
F 3 "" H 5400 5000 50  0001 C CNN
	1    5400 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3650 5400 3900
Wire Wire Line
	5400 4850 5400 5000
$Comp
L power:GND #PWR03
U 1 1 5C1BA860
P 5400 3200
F 0 "#PWR03" H 5400 2950 50  0001 C CNN
F 1 "GND" H 5405 3027 50  0000 C CNN
F 2 "" H 5400 3200 50  0001 C CNN
F 3 "" H 5400 3200 50  0001 C CNN
	1    5400 3200
	-1   0    0    1   
$EndComp
Wire Wire Line
	5600 3350 5400 3350
Wire Wire Line
	5400 3350 5400 3200
Wire Wire Line
	5600 3650 5400 3650
$Comp
L Device:R R1
U 1 1 5C1BAB70
P 4600 4050
F 0 "R1" H 4670 4096 50  0000 L CNN
F 1 "10kΩ" H 4670 4005 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4530 4050 50  0001 C CNN
F 3 "~" H 4600 4050 50  0001 C CNN
	1    4600 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3900 4600 3450
$Comp
L Switch:SW_Push SW1
U 1 1 5C1BAD99
P 4600 4600
F 0 "SW1" V 4646 4552 50  0000 R CNN
F 1 "SW_Push" V 4555 4552 50  0000 R CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 4600 4800 50  0001 C CNN
F 3 "" H 4600 4800 50  0001 C CNN
	1    4600 4600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5C1BAE1C
P 4600 5000
F 0 "#PWR01" H 4600 4750 50  0001 C CNN
F 1 "GND" H 4605 4827 50  0000 C CNN
F 2 "" H 4600 5000 50  0001 C CNN
F 3 "" H 4600 5000 50  0001 C CNN
	1    4600 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 4200 4600 4300
Wire Wire Line
	4600 4800 4600 5000
Wire Wire Line
	4600 4300 5050 4300
Wire Wire Line
	5050 4300 5050 3550
Wire Wire Line
	5050 3550 5600 3550
Connection ~ 4600 4300
Wire Wire Line
	4600 4300 4600 4400
Wire Wire Line
	5400 4200 5400 4550
Text Notes 5850 3400 0    50   ~ 0
GND
Text Notes 5850 3500 0    50   ~ 0
3.3V
Text Notes 5850 3600 0    50   ~ 0
BUTTON_D7
Text Notes 5850 3700 0    50   ~ 0
WIFI_LED
Wire Wire Line
	4600 3450 5600 3450
$EndSCHEMATC
