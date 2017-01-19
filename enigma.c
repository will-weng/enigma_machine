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
    char **rotors[4];
    int rotorId[3];
    int rotorPos[3];
} setting;

static char* createWheel(int num);
static int index(char letter);
static int findIndexInRotor(char *rotorArray, int cha);
static int* getNotchIndex(int rotor);

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
                *e->rotors[i] = createWheel(choice);
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
       *e->rotors[4] = createWheel(choice);
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

char scramble(char c, setting *e){

    char[] alphabet = "abcdefghijklmnopqrstuvwxyz";


    //Read in the rotor settings
    int rotOne = setting->rotorPos[0];
    int rotTwo = setting->rotorPos[1];
    int rotThree = setting->rotorPos[2];

    //Plugboard
    char start = setting->plugBoard[index(c)];

    //Rotor 1
    char one = setting->rotors[0][((index(start) + rotOne)%26 + 26)%26];

    //Rotor 2
    char two = setting->rotors[1][((index(one) + rotTwo)%26 + 26)%26];

    //Rotor 3
    char three = setting->rotors[2][((index(two) + rotThree)%26 + 26)%26];

    //Reflector
    char reflect = setting->rotors[3][index(three)];

    //Reverse 3
    int indexThree = findIndexInRotor(setting->rotors[2],reflect);
    char rThree = alphabet[((index-setting->rotorPos[2])%26+26)%26];

    //Reverse 2
    int indexTwo = findIndexInRotor(setting->rotors[1],rThree);
    char rTwo = alphabet[((index-setting->rotorPos[1])%26+26)%26];

    //Reverse 1
    int indexOne = findIndexInRotor(setting->rotors[0],rTwo);
    char rOne = alphabet[((index-setting->rotorPos[0])%26+26)%26];

    //Reverse Plugboard
    int retVal = setting->plugBoard[index(rOne)];

    //Checking for notch incrementation on rotor 1
    if (rotorPos[0] == getNotchIndex(setting->rotorId[0])[0] || rotorPos[0] == getNotchIndex(setting->rotorId[0])[1]){
        rotorPos[1]++;
    }

    //Checking for notch incrementation on rotor 2
    if (rotorPos[1] == index(getNotchIndex(setting->rotorId[1])[0]) || rotorPos[1] == index(getNotchIndex(setting->rotorId[1])[1])){
        rotorPos[2]++;
    }

    //Increment rotors
    setting->rotorPos[0]++;
    setting->rotorPos[1]++;
    setting->rotorPos[2]++;


    //Limit rotor positions 
    if(setting->rotorPos[0] == 26){
        setting->rotorPos[0] = 0;
    }
    else if (setting->rotorPos[0] == 27){
        setting->rotorPos[0] = 1;
    }

    if(setting->rotorPos[1] == 26){
        setting->rotorPos[1] = 0;
    }
    else if (setting->rotorPos[1] == 27){
        setting->rotorPos[1] = 1;
    }

    if(setting->rotorPos[2] == 26){
        setting->rotorPos[2] = 0;
    }
    else if (setting->rotorPos[2] == 27){
        setting->rotorPos[2] = 1;
    }

    //Return value
    return retVal;
}


void deleteEnigma(Setting e) {
    int i;
    for(i = 0; i < 4; i++) free(e->rotors[i]);
    free(e);
}

static char* createWheel(int num) {
    char *wheel = malloc(ALPHABET_NUM * sizeof(char));
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
    return wheel;
}

static int index(char letter){
    return letter - 'a';
}

//Because why the hell not include another library for a single function -.-
static int findIndexInRotor(char *rotorArray, int cha) {
    char *loc;
    int index;
    pos = strchr(rotorArray, cha);
    index = (int)(pos - rotorArray);
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