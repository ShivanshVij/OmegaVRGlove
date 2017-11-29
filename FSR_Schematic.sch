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
LIBS:Task1-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L R 1K
U 1 1 5A1075CF
P 5000 2150
F 0 "1K" V 5080 2150 50  0000 C CNN
F 1 "R" V 5000 2150 50  0000 C CNN
F 2 "" V 4930 2150 50  0001 C CNN
F 3 "" H 5000 2150 50  0001 C CNN
	1    5000 2150
	0    1    1    0   
$EndComp
$Comp
L POT FSR
U 1 1 5A1077B9
P 4550 1800
F 0 "FSR" V 4375 1800 50  0000 C CNN
F 1 "POT" V 4450 1800 50  0000 C CNN
F 2 "" H 4550 1800 50  0001 C CNN
F 3 "" H 4550 1800 50  0001 C CNN
	1    4550 1800
	1    0    0    -1  
$EndComp
$Comp
L C 0.11uF
U 1 1 5A107804
P 4550 2550
F 0 "0.11uF" H 4575 2650 50  0000 L CNN
F 1 "C" H 4575 2450 50  0000 L CNN
F 2 "" H 4588 2400 50  0001 C CNN
F 3 "" H 4550 2550 50  0001 C CNN
	1    4550 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5A107A29
P 4550 1450
F 0 "#PWR?" H 4550 1200 50  0001 C CNN
F 1 "GND" H 4550 1300 50  0000 C CNN
F 2 "" H 4550 1450 50  0001 C CNN
F 3 "" H 4550 1450 50  0001 C CNN
	1    4550 1450
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR?
U 1 1 5A107CB0
P 4550 2950
F 0 "#PWR?" H 4550 2800 50  0001 C CNN
F 1 "VCC" H 4550 3100 50  0000 C CNN
F 2 "" H 4550 2950 50  0001 C CNN
F 3 "" H 4550 2950 50  0001 C CNN
	1    4550 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	4550 1650 4550 1450
Wire Wire Line
	5150 2150 5350 2150
Connection ~ 4550 2150
Wire Wire Line
	4550 2150 4850 2150
Wire Wire Line
	4550 1950 4550 2400
Wire Wire Line
	4550 2950 4550 2700
$Comp
L Conn_01x01 GPIO_X
U 1 1 5A121990
P 5550 2150
F 0 "GPIO_X" H 5550 2250 50  0000 C CNN
F 1 "Conn_01x01" H 5550 2050 50  0000 C CNN
F 2 "" H 5550 2150 50  0001 C CNN
F 3 "" H 5550 2150 50  0001 C CNN
	1    5550 2150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
