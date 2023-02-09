#!/bin/bash

#Program: Gnome Run Create
#Author: Joseph Eggers

echo "compile driver.cpp using the g++ compiler standard 2017"
g++ -c -Wall -no-pie -m64 -std=c++17 -o main.o main.cc

echo "compile isFloat.cpp using the g++ compiler standard 2017"
g++ -c -Wall -no-pie -m64 -std=c++17 -o game.o game.cc

echo "compile isFloat.cpp using the g++ compiler standard 2017"
g++ -c -Wall -no-pie -m64 -std=c++17 -o player.o player.cc

echo "compile isFloat.cpp using the g++ compiler standard 2017"
g++ -c -Wall -no-pie -m64 -std=c++17 -o opponent.o opponent.cc

echo "compile isFloat.cpp using the g++ compiler standard 2017"
g++ -c -Wall -no-pie -m64 -std=c++17 -o game_element.o game_element.cc

echo "Link object files using the gcc Linker standard 2017"
g++ -c -Wall -m64 -no-pie -o gnomeRun.out game_element.o opponent.o player.o main.o game.o -std=c++17

echo "Run the Float Comparator Program:"
./gnomeRun.out