//
// William Weng, Andrew Carmichael
// Enigma Machine interface
// 16/01/2017
//

#include <stdio.h>
#include <stdlib.h>
#include "enigma.h"

int main(int argc, char *argv[]) {
    // copies the message into an array to decrypt or encrypt later;
    char message[] = argv;
    int length;

    Setting e = newEnigma();
    for(int i = 0; i < length; i++) {
        printf("%c", scramble(message[i]), e);
    }
    printf("\n is the message");

    return EXIT_SUCCESS;
}