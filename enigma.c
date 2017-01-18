//
// William Weng
// Enigma Machine blackbox
// 16/01/2017
//

#include "enigma.h"
#include "string.h"

#define ALPHABET_NUM 26;
#define SWITCH_NUM 10;

typedef struct _setting {
    char plugBoard[ALPHABET_NUM] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
                                    'n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char **rotors[4];
    int rotorId[3]
    int rotorPos[3];
} setting;

static char* createWheel(int num);

setting newEnigma() {
    //create a new enigma machine to use including settings
    Setting e = malloc(sizeof(struct _setting));
    
    int choice, ;

    for(int i = 0; i < 6; i++) {
        if(i < 3) {
            printf("Choose the rotor for position %d:\n", i + 1);
        } else {
            printf("Choose index for rotor %d:\n", i - 2);

        }
        scanf("%d", &choice);
        if(i < 3) {
            e->rotorId[i] = choice;
            e->rotors[i] = createWheel(choice);
        } else {
            e->rotorPos[i - 3] = choice;
        }
    }
    printf("Choose the reflector:\n");
    scanf("%d", &choice);   
    e->rotors[4] = createWheel(choice);

    char switch1, switch2;
    for(int i = 0; i < SWITCH_NUM; i++) {
        printf("Enter the pair of switches(%d):\n", i);
        scanf("%c %c", &switch1, &switch2);
        e->plugBoard[switch1 - 'a'] = switch2;
        e->plugBoard[switch2 - 'a'] = switch1;
    }

    return e;
}

char scramble(char c, Setting e) {
    char encrypt;
    return encrypt;
}

static char* createWheel(int num) {
    char *wheel = malloc(ALPHABET_NUM*sizeof(char));
    switch(num) {
        case '1' :
            char copy[27] = "ejmzalyxvbwfcrquontspikhgd";
            break;
        case '2' :
            char copy[27] = "yruhqsldpxngokmiebfzcwvjat";
            break;
        case '4' :
            char copy[27] = "esovpzjayquirhxlnftgkdcmwb";
            break;
        case '5' :
            char copy[27] = "vzbrgityupsdnhlxawmjqofeck";
            break;
        case '6' :
            char copy[27] = "jpgvoumfyqbenhzrdkasxlictw";
            break;
        case '7' :
            char copy[27] = "nzjhgrcxmyswboufaivlpekqdt";
            break;
        case '8' :
            char copy[27] = "fkqhtlxocbjspdzramewniuygv";
            break;
    }

    strcpy(wheel, copy, ALPHABET_NUM);
    return wheel;
}