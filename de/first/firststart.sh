#!/bin/bash

# Notwendige Variablen definieren
HFUSE=0xd1
LFUSE=0xef
PROGRAMMER=usbasp
TARGET=first

# Den Benutzer informieren, 3 Sekunden warten und dann den NIBObee in den Werkszustand versetzen
printf '\E[31m'"\033[1mDas NIBObee Reset-Programm wird in 3 Sekunden geflasht\n\033[0m"
sleep 3
sudo avrdude -c $PROGRAMMER -p m16 -B 10 -U lfuse:w:$LFUSE:m -U hfuse:w:$HFUSE:m
sudo avrdude -c $PROGRAMMER -p m16 -B 2 -U flash:w:$TARGET.hex
