//
// William Weng, Andrew Carmichael
// Enigma Machine interface
// 16/01/2017
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma.h"

int main(int argc, char *argv[]) {
    // copies the message into an array to decrypt or encrypt later;
    if(argc < 2) {
        printf("Incorrect number of arguments\nUsage: ./enigmaMachine message\n");
        return EXIT_FAILURE;
    } else {
        int length = strlen(argv[1]);
        char message[length + 1];
        if(!sscanf(argv[1], "%s", message)) {
            printf("Invalid input\n");
            return EXIT_FAILURE;
        }
        
        Setting e = newEnigma();
        showEnigma(e);

        int i;
        printf("The encrypted/decrypted message is:\n");
        for(i = 0; i < length; i++) {
            printf("%c", scramble(message[i], e));
        }
        printf("\n");
        deleteEnigma(e);
    }    
    return EXIT_SUCCESS;
}