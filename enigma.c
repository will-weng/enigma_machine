//
// William Weng
// Enigma Machine blackbox
// 16/01/2017
//

#include "enigma.h"

#define ALPHABET_NUM 26;

typedef struct _setting {
    char plugBoard[26];
    int **rotors[3];
} setting;

static int* createWheel(int num);

setting newEnigma() {
    //create a new enigma machine to use including settings
    Setting e = malloc(sizeof(struct _setting));
    int holder;

    for(int i = 0; i < 3; i++) {
        scanf("%d", &holder);
        e->rotors[i] = createWheel(holder);
    }

    return e;
}

char scramble(char c) {
    char encrypt;
    return encrypt;
}

static int* createWheel(int num) {
    int wheel[] = malloc(ALPHABET_NUM*sizeof(char));

    return wheel;
}