//
// William Weng, Andrew Carmichael
// Enigma Machine blackbox
// 16/01/2017
//

#include "enigma.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_NUM 30

typedef struct _setting {
    char plugBoard[ALPHABET_NUM];
    char rotors[5][ALPHABET_NUM];
    int rotorId[4];
    int rotorPos[4];
    int rotorOffset[4];
} setting;

static void addWheel(char choice, Setting e, int i);
static int rotorIndex(char letter);
static int findIndexInRotor(char *rotorArray, int cha);
static int* getNotchIndex(int rotor);

// create new enigma machine
Setting newEnigma() {
    //create a new enigma machine to use including settings
    Setting e = malloc(sizeof(struct _setting));
    int i;
    char choice, line[ALPHABET_NUM];

    // settings for the rotors
    for(i = 0; i < 12; i++) {
        if(i < 4) {
            printf("Choose the rotor for position %d:\n", i + 1);
        } else if(i < 8) {
            printf("Choose offset for rotor %d: \n", i - 3);
        } else {
            printf("Choose index for rotor %d:\n", i - 7);
        }

        if(fgets(line, sizeof(line), stdin) != NULL && sscanf(line, "%c", &choice)){
            if(i < 4) {
                e->rotorId[i] = choice;
                addWheel(choice, e, i);
            } else if(i < 8) {
                e->rotorOffset[i - 4] = choice - 'a';
            } else {
                e->rotorPos[i - 8] = choice - '0';
            }
        } else {
            printf("Invalid choice, please retry\n");
            i--;
        }
    }

    // settings for reflector
    printf("Choose the reflector:\n");
    if(fgets(line, sizeof(line), stdin) != NULL && sscanf(line, "%c", &choice)) {
       addWheel(choice, e, 4);
    }

    // settings for plugboard
    printf("Choose the number of switches:\n");
    int switchNum = -1;
    while(switchNum == -1) {
        if(fgets(line, sizeof(line), stdin) != NULL && sscanf(line, "%d", &switchNum) && switchNum <= 13) {
            strcpy(e->plugBoard, "abcdefghijklmnopqrstuvwxyz");
            char switch1, switch2;
            for(i = 0; i < switchNum; i++) {
                printf("Enter a pair of switches(%d):\n", i + 1);
                if(fgets(line, sizeof(line), stdin) != NULL && sscanf(line, "%c %c", &switch1, &switch2)) {
                    e->plugBoard[switch1 - 'a'] = switch2;
                    e->plugBoard[switch2 - 'a'] = switch1;
                } else {
                    printf("Didn't read properly, please re-enter\n");
                    i--;
                }
            }
            break;
        } else {
            switchNum = -1;
            printf("Please re-enter the number of switches.\n");
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
    char start = e->plugBoard[rotorIndex(c)];

    //Rotor 1
    char one = e->rotors[0][((rotorIndex(start) + rotOne)%26 + 26)%26];

    //Rotor 2
    char two = e->rotors[1][((rotorIndex(one) + rotTwo)%26 + 26)%26];

    //Rotor 3
    char three = e->rotors[2][((rotorIndex(two) + rotThree)%26 + 26)%26];

    //Reflector
    char reflect = e->rotors[3][rotorIndex(three)];

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
    int retVal = e->plugBoard[rotorIndex(rOne)];

    //Checking for notch incrementation on rotor 1
    int* id1 = getNotchIndex(e->rotorId[0]);
    if (e->rotorPos[0] == rotorIndex(id1[0]) || e->rotorPos[0] == rotorIndex(id1[1])){
        e->rotorPos[1]++;
    }
    free(id1);
    
    //Checking for notch incrementation on rotor 2
    int* id2 = getNotchIndex(e->rotorId[1]);
    if (e->rotorPos[1] == rotorIndex(id2[0]) || e->rotorPos[1] == rotorIndex(id2[1])){
        e->rotorPos[2]++;
    }
    free(id2);
    
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
    free(e);
}

// adds a preset wheel onto the enigma machine
static void addWheel(char choice, Setting e, int i) {
    switch(choice) {
        case 'a' :
            strcpy(e->rotors[i], "ejmzalyxvbwfcrquontspikhgd");
            break;
        case 'b' :
            strcpy(e->rotors[i], "yruhqsldpxngokmiebfzcwvjat");
            break;
        case 'c' :
            strcpy(e->rotors[i], "fvpjiaoyedrzxwgctkuqsbnmhl");
            break;
        case '0' :
            strcpy(e->rotors[i], "abcdefghijklmnopqrstuvwxyz");
            break;
        case '1' :
            strcpy(e->rotors[i], "ekmflgdqvzntowyhxuspaibrcj");
            break;
        case '2' :
            strcpy(e->rotors[i], "ajdksiruxblhwtmcqgznpyfvoe");
            break;
        case '3' :
            strcpy(e->rotors[i], "bdfhjlcprtxvznyeiwgakmusqo");
            break;
        case '4' :
            strcpy(e->rotors[i], "esovpzjayquirhxlnftgkdcmwb");
            break;
        case '5' :
            strcpy(e->rotors[i], "vzbrgityupsdnhlxawmjqofeck");
            break;
        case '6' :
            strcpy(e->rotors[i], "jpgvoumfyqbenhzrdkasxlictw");
            break;
        case '7' :
            strcpy(e->rotors[i], "nzjhgrcxmyswboufaivlpekqdt");
            break;
        case '8' :
            strcpy(e->rotors[i], "fkqhtlxocbjspdzramewniuygv");
            break;
        default:
            printf("invalid choice, using default\n");
            strcpy(e->rotors[i], "abcdefghijklmnopqrstuvwxyz");
            break;
    }
}

static int rotorIndex(char letter){
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
    int *retVal = malloc(sizeof(int)*2);

    switch(rotor){
        case 4 :
            retVal[0] = rotorIndex('j');
            retVal[1] = rotorIndex('j');
            break;  
        case 5 :
            retVal[0] = rotorIndex('z');
            retVal[1] = rotorIndex('z');
            break;
        case 6 :
            retVal[0] = rotorIndex('m');
            retVal[1] = rotorIndex('z');
            break;
        case 7 :
            retVal[0] = rotorIndex('m');
            retVal[1] = rotorIndex('z');
            break;
        case 8 :
            retVal[0] = rotorIndex('m');
            retVal[1] = rotorIndex('z');
            break;
    }

    return retVal;
}
