#!/bin/sh
#Compilador basico 
fich=$1

gcc -c -Wall -Wshadow -g $fich

gcc -o hello hello.o

exit 0
