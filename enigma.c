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
    char rotorId[4];
    int rotorPos[4];
    char rotorOffset[4];
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
                e->rotorOffset[i - 4] = choice - 1;
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

    // Plugboard
    char letter = e->plugBoard[rotorIndex(c)];
    
    // Forward run
    for(int i = 0; i < 4; i++) 
        letter = e->rotors[i][(rotorIndex(letter) + e->rotorPos[i] +
                            rotorIndex(e->rotorOffset[i])) % 26];

    // Reflector
    letter = e->rotors[4][rotorIndex(letter)];

    // Reverse run
    int indexNum;
    for(int i = 4; i > 0; i--) {
        indexNum = findIndexInRotor(e->rotors[2], letter);
        letter = alphabet[((indexNum - e->rotorPos[2])%26+26)%26];
    }

    //Reverse Plugboard
    int retVal = e->plugBoard[rotorIndex(letter)];

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
    for(int i = 0; i < 3; i++)
        (e->rotorPos[i] == 26) ? e->rotorPos[i] = 1 : e->rotorPos[i]++;

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

// prints the current settings for enigma
void showEnigma(Setting e) {
    printf("plugboard settings is: %s\n", e->plugBoard);
    for(int i = 0; i < 4; i++) {
        printf("rotor %d settings is: %s\n", i + 1, e->rotors[i]);
        printf("id is: %c\n", e->rotorId[i]);
        printf("position is: %d\n", e->rotorPos[i]);
        printf("offset is: %c\n", e->rotorOffset[i]);
    }
    printf("reflector setting is: %s\n", e->rotors[4]);
}