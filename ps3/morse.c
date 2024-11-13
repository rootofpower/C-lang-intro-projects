#include<stdio.h>
#include "morse.h"
#include <string.h>

void morse_to_text(const char morse[], char output[]){
    const char *morse_table[37] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--..",
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "\0"};

    const char *alphabet[37] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
                   "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
                   "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "\0"};
    output[0] = '\0';
    char temp[strlen(morse) + 1];
    for (int i = 0; i < strlen(morse) + 1; i++){
        temp[i] = morse[i];
    }
    
    char *token = strtok(temp, " ");
    while(token != NULL){
        for(int i = 0; i < 36; i++){
            if(strcmp(token, morse_table[i]) == 0){
                sprintf(output + strlen(output), "%s", alphabet[i]);
            }
        }
        token = strtok(NULL, " ");
    }
    
}

void text_to_morse(const char text[], char output[]){
    char *morse[37] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--..",
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
    };

    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
    int size = strlen(text);
    output[0] = '\0';
    for (int i = 0; i < size; i++){
        for (int j = 0; j < strlen(alphabet); j++){
            if (text[i] == alphabet[j]){
                sprintf(output + strlen(output), "%s ", morse[j]);
            }
        }
    }
    size = strlen(output);
    int i = size;
    while(output[i - 1] == ' '){
        output[i - 1] = 0;
        --i;
    }
}

int is_morse_code_valid(const char morse[]){
    const char *morse_table[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--..",
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
    };
    
    char temp[strlen(morse) + 1];
    for (int i = 0; i < strlen(morse) + 1; i++){
        temp[i] = morse[i];
    }
    char *token = strtok(temp, " ");
    while(token != NULL){
        for(int i = 0; i < 36; i++){
            if(strcmp(token, morse_table[i]) == 0){
                break;
            }
            else{
                if(i == 35 && token != morse_table[i]) return 0;
                else continue;
            }
            
        }
        token = strtok(NULL, " ");
    }
    return 1;
}

