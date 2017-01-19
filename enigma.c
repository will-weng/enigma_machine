//
// William Weng, Andrew Carmichael
// Enigma Machine blackbox
// 16/01/2017
//

#include "enigma.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_NUM 26
#define SWITCH_NUM 10

typedef struct _setting {
    char plugBoard[ALPHABET_NUM];
    char rotors[4][ALPHABET_NUM];
    int rotorId[3];
    int rotorPos[3];
} setting;

static void addWheel(int num, char *wheel);
static int index(char letter);
static int findIndexInRotor(char *rotorArray, int cha);
static int* getNotchIndex(int rotor);

// create new enigma machine
Setting newEnigma() {
    //create a new enigma machine to use including settings
    Setting e = malloc(sizeof(struct _setting));
    
    int choice, i;
    char line[ALPHABET_NUM];

    for(i = 0; i < 6; i++) {
        if(i < 3) {
            printf("Choose the rotor for position %d:\n", i + 1);
        } else {
            printf("Choose index for rotor %d:\n", i - 2);

        }
        if(fgets(line, sizeof(line), stdin) != NULL && sscanf(line, "%d", &choice)){
            if(i < 3) {
                e->rotorId[i] = choice;
                addWheel(choice, e->rotors[i]);
            } else {
                e->rotorPos[i - 3] = choice;
            }
        } else {
            printf("Invalid choice, please retry\n");
            i--;
        }
    }
    printf("Choose the reflector:\n");
    if(scanf("%d ", &choice) > 0) {
       addWheel(choice, e->rotors[4]);
    }

    strcpy(e->plugBoard, "abcdefghijklmnopqrstuvwxy"); e->plugBoard[ALPHABET_NUM - 1] = 'z';
    char switch1, switch2;
    for(i = 0; i < SWITCH_NUM; i++) {
        printf("Enter a pair of switches(%d):\n", i + 1);
        if(fgets(line, sizeof(line), stdin) != NULL && scanf("%c %c ", &switch1, &switch2) > 0) {
            e->plugBoard[switch1 - 'a'] = switch2;
            e->plugBoard[switch2 - 'a'] = switch1;
        } else {
            printf("Didn't read properly please re-enter\n");
            i--;
        }
    }
    return e;
}

// encodes a letter given depending on the settings
char scramble(char c, Setting e){

    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";


    //Read in the rotor settings
    int rotOne = e->rotorPos[0];
    int rotTwo = e->rotorPos[1];
    int rotThree = e->rotorPos[2];

    //Plugboard
    char start = e->plugBoard[index(c)];

    //Rotor 1
    char one = e->rotors[0][((index(start) + rotOne)%26 + 26)%26];

    //Rotor 2
    char two = e->rotors[1][((index(one) + rotTwo)%26 + 26)%26];

    //Rotor 3
    char three = e->rotors[2][((index(two) + rotThree)%26 + 26)%26];

    //Reflector
    char reflect = e->rotors[3][index(three)];

    //Reverse 3
    int indexThree = findIndexInRotor(e->rotors[2],reflect);
    char rThree = alphabet[((indexThree-e->rotorPos[2])%26+26)%26];

    //Reverse 2
    int indexTwo = findIndexInRotor(e->rotors[1],rThree);
    char rTwo = alphabet[((indexTwo-e->rotorPos[1])%26+26)%26];

    //Reverse 1
    int indexOne = findIndexInRotor(e->rotors[0],rTwo);
    char rOne = alphabet[((indexOne-e->rotorPos[0])%26+26)%26];

    //Reverse Plugboard
    int retVal = e->plugBoard[index(rOne)];

    //Checking for notch incrementation on rotor 1
    if (e->rotorPos[0] == getNotchIndex(e->rotorId[0])[0] || e->rotorPos[0] == getNotchIndex(e->rotorId[0])[1]){
        e->rotorPos[1]++;
    }

    //Checking for notch incrementation on rotor 2
    if (e->rotorPos[1] == index(getNotchIndex(e->rotorId[1])[0]) || e->rotorPos[1] == index(getNotchIndex(e->rotorId[1])[1])){
        e->rotorPos[2]++;
    }

    //Increment rotors
    e->rotorPos[0]++;
    e->rotorPos[1]++;
    e->rotorPos[2]++;


    //Limit rotor positions 
    if(e->rotorPos[0] == 26){
        e->rotorPos[0] = 0;
    }
    else if (e->rotorPos[0] == 27){
        e->rotorPos[0] = 1;
    }

    if(e->rotorPos[1] == 26){
        e->rotorPos[1] = 0;
    }
    else if (e->rotorPos[1] == 27){
        e->rotorPos[1] = 1;
    }

    if(e->rotorPos[2] == 26){
        e->rotorPos[2] = 0;
    }
    else if (e->rotorPos[2] == 27){
        e->rotorPos[2] = 1;
    }

    //Return value
    return retVal;
}

// free's all the malloced memory
void deleteEnigma(Setting e) {
    int i;
    for(i = 0; i < 4; i++) free(e->rotors[i]);
    free(e);
}

// adds a preset wheel onto the enigma machine
static void addWheel(int num, char *wheel) {
    switch(num) {
        case '1' :
            wheel = "ejmzalyxvbwfcrquontspikhgd";
            break;
        case '2' :
            wheel = "yruhqsldpxngokmiebfzcwvjat";
            break;
        case '4' :
            wheel = "esovpzjayquirhxlnftgkdcmwb";
            break;
        case '5' :
            wheel = "vzbrgityupsdnhlxawmjqofeck";
            break;
        case '6' :
            wheel = "jpgvoumfyqbenhzrdkasxlictw";
            break;
        case '7' :
            wheel = "nzjhgrcxmyswboufaivlpekqdt";
            break;
        case '8' :
            wheel = "fkqhtlxocbjspdzramewniuygv";
            break;
    }
}

static int index(char letter){
    return letter - 'a';
}

//Because why the hell not include another library for a single function -.-
static int findIndexInRotor(char *rotorArray, int cha) {
    char *loc;
    int index;
    loc = strchr(rotorArray, cha);
    index = (int)(loc - rotorArray);
    return index;
}


//Returns an 2 element array containing the notch indicies
static int* getNotchIndex(int rotor){
    int retVal[2];

    switch(rotor){
        case 1 :
            retVal[0] = index('j');
            retVal[1] = index('j');
            break;  
        case 2 :
            retVal[0] = index('z');
            retVal[1] = index('z');
            break;
        case 3 :
            retVal[0] = index('m');
            retVal[1] = index('z');
            break;
        case 4 :
            retVal[0] = index('m');
            retVal[1] = index('z');
            break;
        case 5 :
            retVal[0] = index('m');
            retVal[1] = index('z');
            break;
    }

    return retVal;
}