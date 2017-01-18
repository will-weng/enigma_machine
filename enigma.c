//
// William Weng, Andrew Carmichael
// Enigma Machine blackbox
// 16/01/2017
//

#include "enigma.h"
#include <string.h>
#include <stdio.h>

#define ALPHABET_NUM 26
#define SWITCH_NUM 10

typedef struct _setting {
    char plugBoard[ALPHABET_NUM];
    char **rotors[4];
    int rotorId[3];
    int rotorPos[3];
} setting;

static char* createWheel(int num);

Setting newEnigma() {
    //create a new enigma machine to use including settings
    Setting e = malloc(sizeof(struct _setting));
    
    int choice, i;

    for(i = 0; i < 6; i++) {
        if(i < 3) {
            printf("Choose the rotor for position %d:\n", i + 1);
        } else {
            printf("Choose index for rotor %d:\n", i - 2);

        }
        if(scanf("%d", &choice) == 1){
            if(i < 3) {
                e->rotorId[i] = choice;
                *e->rotors[i] = createWheel(choice);
                printf("TESTING\n");
            } else {
                e->rotorPos[i - 3] = choice;
            }
        }
    }
    printf("Choose the reflector:\n");
    if(scanf("%d", &choice) == 1) {
       *e->rotors[4] = createWheel(choice);
    }

    strcpy(e->plugBoard, "abcdefghijklmnopqrstuvwxy"); e->plugBoard[ALPHABET_NUM - 1] = 'z';
    char switch1, switch2;
    for(i = 0; i < SWITCH_NUM; i++) {
        printf("Enter the pair of switches(%d):\n", i);
        if(scanf("%c %c", &switch1, &switch2) == 1) {
            e->plugBoard[switch1 - 'a'] = switch2;
            e->plugBoard[switch2 - 'a'] = switch1;
        }
    }

    return e;
}

char scramble(char c, Setting e) {
    char encrypt = c;
    return encrypt;
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