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
L Conn_01x01 GPIO_X
U 1 1 5A2505FF
P 2650 1950
F 0 "GPIO_X" H 2650 2050 50  0000 C CNN
F 1 "GPIO PIN" H 2650 1850 50  0000 C CNN
F 2 "" H 2650 1950 50  0001 C CNN
F 3 "" H 2650 1950 50  0001 C CNN
	1    2650 1950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5A250643
P 1850 1450
F 0 "#PWR?" H 1850 1300 50  0001 C CNN
F 1 "+5V" H 1850 1590 50  0000 C CNN
F 2 "" H 1850 1450 50  0001 C CNN
F 3 "" H 1850 1450 50  0001 C CNN
	1    1850 1450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5A250659
P 1850 2950
F 0 "#PWR?" H 1850 2700 50  0001 C CNN
F 1 "GND" H 1850 2800 50  0000 C CNN
F 2 "" H 1850 2950 50  0001 C CNN
F 3 "" H 1850 2950 50  0001 C CNN
	1    1850 2950
	1    0    0    -1  
$EndComp
$Comp
L C 0.22µF
U 1 1 5A25066F
P 1850 1750
F 0 "0.22µF" H 1875 1850 50  0000 L CNN
F 1 "Capacitor" H 1875 1650 50  0000 L CNN
F 2 "" H 1888 1600 50  0001 C CNN
F 3 "" H 1850 1750 50  0001 C CNN
	1    1850 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1600 1850 1450
$Comp
L POT Flex
U 1 1 5A2506CB
P 1850 2200
F 0 "Flex" V 1675 2200 50  0000 C CNN
F 1 "Sensor" V 1750 2200 50  0000 C CNN
F 2 "" H 1850 2200 50  0001 C CNN
F 3 "" H 1850 2200 50  0001 C CNN
	1    1850 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1900 1850 2050
Wire Wire Line
	1850 1950 2450 1950
Connection ~ 1850 1950
$Comp
L R Resistor
U 1 1 5A250720
P 1850 2600
F 0 "Resistor" V 1930 2600 50  0000 C CNN
F 1 "1K Ω" V 1850 2600 50  0000 C CNN
F 2 "" V 1780 2600 50  0001 C CNN
F 3 "" H 1850 2600 50  0001 C CNN
	1    1850 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 2350 1850 2450
Wire Wire Line
	1850 2750 1850 2950
$EndSCHEMATC
