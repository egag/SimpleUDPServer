#!/bin/sh

echo "Compile server"
g++ -std=c++11 serverDriver.cpp -o server --pedantic -Wall -Werror -O3
echo "Compile client"
g++ -std=c++11 clientDriver.cpp -o client --pedantic -Wall -Werror -O3
