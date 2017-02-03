# enigma_machine
my attempt at creating the enigma machine

usage: ./enigmaMachine stringtodecrypt/encrypt

compile with
#gcc -Wall -Werror -O -o enigmaMachine machine.c enigma.c
or
#make
if make is installed

test with
#./enigmaMachine message < setting

when writing a setting file

rotor 1 (1-8)
rotor 2 (1-8)
rotor 3 (1-8)
rotor 4 (1-8) or 0 if no 4th rotor
offset 1 (a-z)
offset 2 (a-z)
offset 3 (a-z)
offset 4 (a-z) or a if no 4th rotor
index 1 (1-26)
index 2 (1-26)
index 3 (1-26)
index 4 (1-26) or 1 if no 4th rotor
reflector (a-c)
number of switches (1-13)
(pairs of letters)
(pairs of letters)
...
...
...