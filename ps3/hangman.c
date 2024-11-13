#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <string.h>
#include <ctype.h>

void get_display_word(const char secret[], const char letters_guessed[], char guessed_word[]);
int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]){
    int counter = 0;
    int size_of_secret = strlen(secret), size_of_letters_guessed = strlen(letters_guessed);
    for (int i = 0; i < size_of_secret; i++){
        for (int j = 0; j < size_of_letters_guessed; j++){
            if (secret[i] == letters_guessed[j]){
                counter++;
            }
            else{
                continue;
            }
        }
    }
    if (counter == size_of_secret){
        return 1;
    }
    else {
        return 0;
    }
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    int size_of_secret = strlen(secret) + 1;
    int size_of_let_guessed = strlen(letters_guessed) + 1;
    char temp[size_of_secret];
    for (int i = 0; i < size_of_secret; i++){
        guessed_word[i] = '_';
        temp[i] = guessed_word[i];
    }
    

    for (int i = 0; i < size_of_secret; i++){
        for(int j = 0; j < size_of_let_guessed; j++){
            if(secret[i] == letters_guessed[j]) temp[i] = letters_guessed[j];
            else continue;
        }
        guessed_word[i] = temp[i];
    }
    
}
void get_available_letters(const char letters_guessed[], char available_letters[]){
    const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int size_of_alp = strlen(alphabet) + 1;

    strcpy(available_letters, alphabet);

    for (int i = 0; i < size_of_alp; i++){
        if(strchr(letters_guessed, alphabet[i]) != NULL){
            char* pos = strchr(available_letters, alphabet[i]);
            if (pos != NULL) {
                int index = pos - available_letters;
                memmove(&available_letters[index], &available_letters[index + 1], strlen(available_letters) - index);
            }
        }
    }
}
void hangman(const char secret[]) {
    int size = strlen(secret) + 1;
    char input_letters[size], available_letters[27],
        letters_guessed[size], guessed_word[size], guessed_w_o_r_d[(size * 2) - 1], flag_error_el[size];
    int attempts = 8;

    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %d letters long.\n", size - 1);

    memset(letters_guessed, 0, sizeof(letters_guessed));
    memset(guessed_w_o_r_d, 0, sizeof(guessed_w_o_r_d));
    memset(flag_error_el, 0, sizeof(flag_error_el));
    strcpy(available_letters, "abcdefghijklmnopqrstuvwxyz");

    while (attempts > 0) {
        printf("-------------\n");
        printf("You have %d guesses left.\n", attempts);
        printf("Available letters: %s\n", available_letters);
        printf("Please guess a letter: ");

        fgets(input_letters, sizeof(input_letters), stdin);
        input_letters[strcspn(input_letters, "\n")] = 0;

        if (strlen(input_letters) == 1) {
            char letter = tolower(input_letters[0]);
            if (!isalpha(letter)) {
                get_guessed_word(secret, letters_guessed, guessed_word);
                char display_word[2*strlen(secret) + 1];
                get_display_word(secret, letters_guessed, display_word);
                printf("Oops! '%c' is not a valid letter: %s\n", letter, display_word);
                continue;
            }
            if (strchr(letters_guessed, letter)) {
                get_guessed_word(secret, letters_guessed, guessed_word);
                char display_word[2*strlen(secret) + 1];
                get_display_word(secret, letters_guessed, display_word);
                printf("Oops! You've already guessed that letter: %s\n", display_word);
            }
            else {
                char letter_str[2] = {letter, '\0'};
                strcat(letters_guessed, letter_str);
                if (strchr(secret, letter)) {
                    get_guessed_word(secret, letters_guessed, guessed_word);
                    char display_word[2*strlen(secret) + 1];
                    get_display_word(secret, letters_guessed, display_word);
                    printf("Good guess: %s\n", display_word);
                } else {
                    attempts--;
                    char display_word[2*strlen(secret) + 1];
                    get_display_word(secret, letters_guessed, display_word);
                    printf("Oops! That letter is not in my word: %s\n", display_word);
                }
                get_available_letters(letters_guessed, available_letters);
            }
        }
        else {
            if (strcmp(input_letters, secret) == 0) {
                printf("Congratulations, you won!\n");
                return;
            }
            else if(strcmp(input_letters, secret)){
                printf("-------------\n");
                printf("Sorry, bad guess. The word was %s.\n", secret);
                return;
            }

            else {
                attempts--;
                if (attempts == 0) {
                    printf("-------------\n");
                    printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
                    return;
                }
            }
        }

        if (is_word_guessed(secret, letters_guessed)) {
            printf("-------------\n");
            printf("Congratulations, you won!\n");
            return;
        }
    }
    printf("-------------\n");
    printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
}
void get_display_word(const char* secret, const char* letters_guessed, char* display_word) {
    int len = strlen(secret);
    for (int i = 0; i < len; i++) {
        if (strchr(letters_guessed, secret[i])) {
            display_word[2*i] = secret[i];
            display_word[2*i + 1] = ' ';
        } else {
            display_word[2*i] = '_';
            display_word[2*i + 1] = ' ';
        }
    }
    display_word[(2*len) - 1] = '\0';
}





