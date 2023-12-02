#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define WORDS_NUMBER 245366
#define MAX_WORD_LENGTH 100
#define TRIES 50

void toUpperStr(char *str);

void printFormattedWord(unsigned char wordSize);

int main(void) {
    srand((unsigned int)time(0)); // Set the seed

    FILE *fptr;

    // Open the file
    if ((fptr = fopen("words.txt", "r")) == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return EXIT_FAILURE;
    }

    char word[MAX_WORD_LENGTH];

    unsigned randomIndex = rand() % WORDS_NUMBER;
    unsigned currentIndex = 0;

    while (fgets(word, MAX_WORD_LENGTH, fptr) != NULL) {
        if (currentIndex == randomIndex) {
            break;
        }
        currentIndex++;
    }

    // Close the file
    fclose(fptr);

    toUpperStr(word);

    unsigned char wordSize = strlen(word) - 1;

    printf("\033[1;31m\e[1mA palavra possui %d letras.\e[m\033[0m\n\n", wordSize);
    printFormattedWord(wordSize);

    for (unsigned trie = 0; trie < TRIES; trie++) {
        char guess[MAX_WORD_LENGTH];
        printf("\e[1mTentativa %d\e[m\n\n", trie + 1);
        scanf("%s", guess);
        printf("\n\n");

        toUpperStr(guess);

        bool won = true;
        for (unsigned i = 0; i < wordSize; i++) {
            if (word[i] == guess[i]) {
                printf("O");
            } else if (strchr(word, guess[i]) != NULL) {
                printf("#");
                won = false;
            } else {
                printf("X");
                won = false;
            }
        }
        printf("\n\n\n");

        if (won) {
            printf("\e[1mGANHOU!!!!!!!!!\n\n\e[m");
            return EXIT_SUCCESS;
        }
    }

    printf("\033[1;31m\e[1mA palavra é %s.\e[m\033[0m\n\n", word);

    return EXIT_FAILURE;
}

void toUpperStr(char *str) {
    for (size_t i = 0; str[i] != '\0'; i++)
        str[i] = toupper((unsigned char)str[i]);
}

void printFormattedWord(unsigned char wordSize) {
    for (unsigned char i = 0; i < wordSize; i++)
        printf("_");
    printf("\n\n\n");
}
