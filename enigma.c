//
// William Weng
// Enigma Machine blackbox
// 16/01/2017
//

#include "enigma.h"

#define WHEEL_SIZE 4*26;

typedef struct _setting {
    char plugBoard[26];
    int *wheel1;
    int *wheel2;
    int *wheel3;
} setting;


static int* createWheels(int num);

void newEnigma() {
    //create wheels

}

char scramble(char c) {
    char encrypt;
    return encrypt;
}

static int* createWheels(int num) {
    int wheel[] = malloc(WHEEL_SIZE);
    return wheel;
}