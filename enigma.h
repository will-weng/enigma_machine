//
// William Weng, Andrew Carmichael
// Enigma Machine interface
// 16/01/2017
//

typedef struct _setting *Setting;

// creates an enigma machine with settings
Setting newEnigma();

// given the current settings
char scramble(char c, Setting e);

// updates the current setting including rotor and pairs
// void updateSetting(Setting e);

// free's up all mallocs
void deleteEnigma(Setting e);