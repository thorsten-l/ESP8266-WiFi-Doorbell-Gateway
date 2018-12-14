EESchema Schematic File Version 4
LIBS:WifiDoorBell-D1-mini-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "WifiDoorBell Wemos D1 mini"
Date "2018-12-06"
Rev "1.2"
Comp "Dr.-Ing. Thorsten Ludewig"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L WifiDoorBell-D1-mini-rescue:CONN_01X08 P1
U 1 1 5763EB78
P 8500 4800
F 0 "P1" H 8500 5250 50  0000 C CNN
F 1 "CONN_01X08" V 8600 4800 50  0000 C CNN
F 2 "D1_mini:D1_mini_Pin_Header" H 8500 4800 50  0001 C CNN
F 3 "" H 8500 4800 50  0000 C CNN
	1    8500 4800
	1    0    0    -1  
$EndComp
$Comp
L WifiDoorBell-D1-mini-rescue:CONN_01X08 P2
U 1 1 5763EBF2
P 8950 4800
F 0 "P2" H 8950 5250 50  0000 C CNN
F 1 "CONN_01X08" V 9050 4800 50  0000 C CNN
F 2 "D1_mini:D1_mini_Pin_Header" H 8950 4800 50  0001 C CNN
F 3 "" H 8950 4800 50  0000 C CNN
	1    8950 4800
	-1   0    0    -1  
$EndComp
Text Label 8300 4450 2    60   ~ 0
+5V
Text Label 8300 4550 2    60   ~ 0
GND
Text Label 8300 4650 2    60   ~ 0
D4
Text Label 8300 4750 2    60   ~ 0
D3
Text Label 8300 4850 2    60   ~ 0
D2
Text Label 8300 4950 2    60   ~ 0
D1
Text Label 8300 5050 2    60   ~ 0
RX
Text Label 8300 5150 2    60   ~ 0
TX
Text Label 9150 4450 0    60   ~ 0
+3.3V
Text Label 9150 4550 0    60   ~ 0
D8
Text Label 9150 4650 0    60   ~ 0
D7
Text Label 9150 4750 0    60   ~ 0
D6
Text Label 9150 4850 0    60   ~ 0
D5
Text Label 9150 4950 0    60   ~ 0
D0
Text Label 9150 5050 0    60   ~ 0
A0
Text Label 9150 5150 0    60   ~ 0
RST
Text Notes 8050 4650 2    60   ~ 0
GPIO2
Text Notes 8050 4750 2    60   ~ 0
GPIO0
Text Notes 8050 4850 2    60   ~ 0
GPIO4
Text Notes 8050 4950 2    60   ~ 0
GPIO5
Text Notes 9500 4550 0    60   ~ 0
GPIO15
Text Notes 9500 4650 0    60   ~ 0
GPIO13
Text Notes 9500 4750 0    60   ~ 0
GPIO12
Text Notes 9500 4850 0    60   ~ 0
GPIO14
Text Notes 9500 4950 0    60   ~ 0
GPIO16
Wire Notes Line
	7350 3900 7350 5500
Wire Notes Line
	7350 5500 10050 5500
Text Notes 7400 4000 0    60   ~ 0
D1 Mini Shield
$Comp
L Diode_Bridge:B40R D1
U 1 1 5BF97302
P 2050 1800
F 0 "D1" H 2391 1846 50  0000 L CNN
F 1 "B40R" H 2391 1755 50  0000 L CNN
F 2 "Diode_THT:Diode_Bridge_Round_D9.0mm" H 2200 1925 50  0001 L CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/b40r.pdf" H 2050 1800 50  0001 C CNN
	1    2050 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 5BF9735A
P 3400 1950
F 0 "C1" H 3518 1996 50  0000 L CNN
F 1 "10µF" H 3518 1905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 3438 1800 50  0001 C CNN
F 3 "~" H 3400 1950 50  0001 C CNN
	1    3400 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5BF973AA
P 3950 1950
F 0 "C2" H 4065 1996 50  0000 L CNN
F 1 "100nF" H 4065 1905 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L9.0mm_W2.5mm_P7.50mm_MKT" H 3988 1800 50  0001 C CNN
F 3 "~" H 3950 1950 50  0001 C CNN
	1    3950 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 5BF9746B
P 6600 1950
F 0 "C4" H 6718 1996 50  0000 L CNN
F 1 "1000µF" H 6718 1905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 6638 1800 50  0001 C CNN
F 3 "~" H 6600 1950 50  0001 C CNN
	1    6600 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1800 3400 1800
Wire Wire Line
	3400 1800 3950 1800
Connection ~ 3400 1800
Wire Wire Line
	3950 1800 4450 1800
Connection ~ 3950 1800
Wire Wire Line
	3400 2100 3950 2100
$Comp
L power:GND #PWR01
U 1 1 5BF976D8
P 1750 1950
F 0 "#PWR01" H 1750 1700 50  0001 C CNN
F 1 "GND" H 1755 1777 50  0000 C CNN
F 2 "" H 1750 1950 50  0001 C CNN
F 3 "" H 1750 1950 50  0001 C CNN
	1    1750 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1800 1750 1950
$Comp
L power:GND #PWR04
U 1 1 5BF97793
P 7200 4600
F 0 "#PWR04" H 7200 4350 50  0001 C CNN
F 1 "GND" H 7205 4427 50  0000 C CNN
F 2 "" H 7200 4600 50  0001 C CNN
F 3 "" H 7200 4600 50  0001 C CNN
	1    7200 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 4550 7200 4550
Wire Wire Line
	7200 4550 7200 4600
Wire Wire Line
	6600 1800 7200 1800
Wire Wire Line
	7200 1800 7200 4450
Connection ~ 6600 1800
Wire Wire Line
	8300 4450 7200 4450
$Comp
L Isolator:LTV-827 U2
U 1 1 5BF9813C
P 5200 5050
F 0 "U2" H 5200 5375 50  0000 C CNN
F 1 "LTV-827" H 5200 5284 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5000 4850 50  0001 L CIN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-70-96-0016/LTV-8X7%20series%20201610%20.pdf" H 5200 5050 50  0001 L CNN
	1    5200 5050
	1    0    0    -1  
$EndComp
$Comp
L Isolator:LTV-827 U2
U 2 1 5BF981B8
P 5200 5650
F 0 "U2" H 5200 5975 50  0000 C CNN
F 1 "LTV-827" H 5200 5884 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5000 5450 50  0001 L CIN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-70-96-0016/LTV-8X7%20series%20201610%20.pdf" H 5200 5650 50  0001 L CNN
	2    5200 5650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5BF98288
P 5700 5950
F 0 "#PWR03" H 5700 5700 50  0001 C CNN
F 1 "GND" H 5705 5777 50  0000 C CNN
F 2 "" H 5700 5950 50  0001 C CNN
F 3 "" H 5700 5950 50  0001 C CNN
	1    5700 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 5950 5700 5750
Wire Wire Line
	5700 5750 5500 5750
Wire Wire Line
	5700 5750 5700 5150
Wire Wire Line
	5700 5150 5500 5150
Connection ~ 5700 5750
Wire Wire Line
	8300 4950 5600 4950
Wire Wire Line
	5500 5550 5600 5550
Wire Wire Line
	5600 5550 5600 4950
Connection ~ 5600 4950
Wire Wire Line
	5600 4950 5500 4950
$Comp
L Device:R R5
U 1 1 5BF99778
P 5600 4500
F 0 "R5" H 5670 4546 50  0000 L CNN
F 1 "10kΩ" H 5670 4455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 5530 4500 50  0001 C CNN
F 3 "~" H 5600 4500 50  0001 C CNN
	1    5600 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4950 5600 4650
Wire Wire Line
	5600 4350 5600 4200
Wire Wire Line
	5600 4200 9800 4200
Wire Wire Line
	9800 4200 9800 4450
Wire Wire Line
	9800 4450 9150 4450
Wire Wire Line
	4900 5150 4500 5150
Wire Wire Line
	4500 5150 4500 5550
Wire Wire Line
	4500 5550 4900 5550
$Comp
L Device:R R1
U 1 1 5BF9A119
P 3950 4950
F 0 "R1" V 3743 4950 50  0000 C CNN
F 1 "390Ω" V 3834 4950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 3880 4950 50  0001 C CNN
F 3 "~" H 3950 4950 50  0001 C CNN
	1    3950 4950
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5BF9A1A2
P 3950 5150
F 0 "R2" V 3743 5150 50  0000 C CNN
F 1 "390Ω" V 3834 5150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 3880 5150 50  0001 C CNN
F 3 "~" H 3950 5150 50  0001 C CNN
	1    3950 5150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4100 4950 4350 4950
Wire Wire Line
	4100 5150 4500 5150
Connection ~ 4500 5150
Wire Wire Line
	4900 5750 4350 5750
Wire Wire Line
	4350 5750 4350 4950
Connection ~ 4350 4950
Wire Wire Line
	4350 4950 4900 4950
$Comp
L Connector:Conn_01x03_Male J1
U 1 1 5BF9C7ED
P 950 3850
F 0 "J1" H 1056 4128 50  0000 C CNN
F 1 "Conn_01x03_Male" H 900 3650 50  0000 C CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-3_1x03_P2.54mm_Horizontal" H 950 3850 50  0001 C CNN
F 3 "~" H 950 3850 50  0001 C CNN
	1    950  3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 1500 1600 1500
Wire Wire Line
	3400 3850 3400 4950
Wire Wire Line
	3400 4950 3800 4950
Wire Wire Line
	1150 3950 3250 3950
Wire Wire Line
	3250 3950 3250 5150
Wire Wire Line
	3250 5150 3800 5150
Text Label 1150 3950 0    50   ~ 0
Doorbell-Button
Text Label 1150 3750 0    50   ~ 0
Doorbell-Trafo-A
Text Label 1150 3850 0    50   ~ 0
Doorbell-Trafo-B
$Comp
L Regulator_Linear:LM317_3PinPackage U1
U 1 1 5BFB9B79
P 4750 1800
F 0 "U1" H 4750 2042 50  0000 C CNN
F 1 "LM317_3PinPackage" H 4750 1951 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 4750 2050 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 4750 1800 50  0001 C CNN
	1    4750 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5BFBBD17
P 5400 1950
F 0 "R4" H 5470 1996 50  0000 L CNN
F 1 "220Ω" H 5470 1905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 5330 1950 50  0001 C CNN
F 3 "~" H 5400 1950 50  0001 C CNN
	1    5400 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5BFBD435
P 4750 2450
F 0 "R3" H 4820 2496 50  0000 L CNN
F 1 "680Ω" H 4820 2405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 4680 2450 50  0001 C CNN
F 3 "~" H 4750 2450 50  0001 C CNN
	1    4750 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5BFBD490
P 4750 2800
F 0 "#PWR02" H 4750 2550 50  0001 C CNN
F 1 "GND" H 4755 2627 50  0000 C CNN
F 2 "" H 4750 2800 50  0001 C CNN
F 3 "" H 4750 2800 50  0001 C CNN
	1    4750 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2600 4750 2700
Wire Wire Line
	4750 2100 4750 2200
Wire Wire Line
	5050 1800 5400 1800
Connection ~ 5400 1800
Wire Wire Line
	5400 2100 5400 2200
Wire Wire Line
	5400 2200 4750 2200
Connection ~ 4750 2200
Wire Wire Line
	4750 2200 4750 2300
Wire Wire Line
	3950 2100 3950 2700
Wire Wire Line
	3950 2700 4750 2700
Connection ~ 3950 2100
Connection ~ 4750 2700
Wire Wire Line
	4750 2700 4750 2800
Wire Wire Line
	5400 1800 6600 1800
Wire Wire Line
	6600 2700 6600 2100
Wire Wire Line
	4750 2700 6600 2700
Wire Wire Line
	1150 3850 1600 3850
Wire Wire Line
	2050 3750 2050 2100
Wire Wire Line
	1150 3750 2050 3750
Wire Wire Line
	1600 1500 1600 3850
Connection ~ 1600 3850
Wire Wire Line
	1600 3850 3400 3850
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 5C092302
P 10450 3600
F 0 "J2" H 10600 3850 50  0000 R CNN
F 1 "Conn_01x04_Male" H 10900 3250 50  0000 R CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-4_1x04_P2.54mm_Horizontal" H 10450 3600 50  0001 C CNN
F 3 "~" H 10450 3600 50  0001 C CNN
	1    10450 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	9800 4200 9800 3600
Wire Wire Line
	9800 3600 10250 3600
Connection ~ 9800 4200
$Comp
L power:GND #PWR05
U 1 1 5C094155
P 10000 3800
F 0 "#PWR05" H 10000 3550 50  0001 C CNN
F 1 "GND" H 10005 3627 50  0000 C CNN
F 2 "" H 10000 3800 50  0001 C CNN
F 3 "" H 10000 3800 50  0001 C CNN
	1    10000 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 3700 10000 3700
Wire Wire Line
	10000 3700 10000 3800
Wire Wire Line
	10250 3500 9400 3500
Wire Wire Line
	9400 3500 9400 4650
Wire Wire Line
	9400 4650 9150 4650
Wire Wire Line
	10250 3400 8700 3400
Wire Wire Line
	8700 3400 8700 4650
Wire Wire Line
	8700 4650 8300 4650
Text Label 10500 3700 0    50   ~ 0
GND
Text Label 10500 3600 0    50   ~ 0
3.3V
Text Label 10500 3500 0    50   ~ 0
BUTTON_D7
Text Label 10500 3400 0    50   ~ 0
WIFI_LED_D4
$EndSCHEMATC
