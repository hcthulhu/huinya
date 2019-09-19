#include <stdio.h>
#include <string.h>

const int MAXSMB = 200;

const char let[] = " abcdefghigklmnopqrstuvwxyz";

const char alph[][5] = {"|\0",    // ' '
                        "._\0",   // A
                        "_...\0", // B
                        "_._.\0", // C
                        "_..\0",  // D
                        ".\0",    // E
                        ".._.\0", // F
                        "__.\0",  // G
                        "....\0", // H
                        "..\0",   // I
                        ".___\0", // J
                        "_._\0",  // K
                        "._..\0", // L
                        "__\0",   // M
                        "_.\0",   // N
                        "___\0",  // O
                        ".__.\0", // P
                        "__._\0", // Q
                        "._.\0",  // R
                        "...\0",  // S
                        "_\0",    // T
                        ".._\0",  // U
                        "..._\0", // V
                        ".__\0",  // W
                        "_.._\0", // X
                        "_.__\0", // Y
                        "__..\0", // Z
};

void eng_to_morse(char* morse, char* eng) {
    for (int i = 0; eng[i] != '\0'; i++) {
        for (int j = 0; j < 27; j++) {
            if (eng[i] == let[j]) {
                strcat(morse, alph[j]);
                strcat(morse, " ");
                break;
            }
        }
    }
}

int main() {
    // for ( int i = 0; i < 26; i++) {
    //     printf ("%c %s\n", let[i], alph[i]);
    // }
    char word[] = "hello world";
    char morse[MAXSMB] = {};

    eng_to_morse(morse, word);

    printf("%s\n", morse);
    return 0;
}
