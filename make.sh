#!/bin/bash

gcc -g -c categoria.c
gcc -g -c carrello.c
gcc -g -c prodotti.c
gcc -g -c utenti.c
gcc -g -c main.c
gcc main.o utenti.o prodotti.o carrello.o categoria.o -o prova

