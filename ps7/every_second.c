#include <stdio.h>
#include <stdlib.h>

#define bool _Bool

bool is_word(char ch);
bool is_start(char* start_word, char ch, int index);
bool is_end(char* end_word, char ch, int index);
int main(int argc, char* argv[]){
    char* start_word = "START";
    char* end_word = "STOP";
    char finalString[1000] = {0};
    if(argc != 3){
        return 1;
    }
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    if(input == NULL){
        fputc(0, output);
        fclose(input);
        fclose(output);
        return 0;
    }
    char ch, flag = 0, flag2 = 0, flag3 = 0;
    int index = 0, count = 0, word = 0, i = 0;
    while(count == 0 && (ch = fgetc(input)) != EOF){
        if(!is_word(ch))
            index = 0;
        if(is_end(end_word, ch, index)){
            index++;
            if(index == 4){
                index = 0;
                count = 0;
                break;
            }
        }
        if(is_start(start_word, ch, index)){
            index++;
            if(index == 5){
                index = 0;
                count = 1;
            }
        }
    }
    ch = fgetc(input);

    bool is_first_word = 1;

    if(count == 1){
        while(ch != EOF){
            if(!is_word(ch)){
                index = 0;
                printf("WORD !%d!\n", word);
                word++;
                flag = 0;
                flag2 = 0;
                flag3 = 0;
            }
            if(is_end(end_word, ch, index)){
                if(index == 0){    
                    flag = ch;
                    printf("FLAG !%c!\n", flag);
                }
                else if(index == 1){
                    flag2 = ch;
                    printf("FLAG2 !%c!\n", flag2);
                }
                else if(index == 2){
                    flag3 = ch;
                    printf("FLAG3 !%c!\n", flag3);
                }
                index++;
                if(index == 4){
                    index = 0;
                    count = 0;
                    break;
                }
            }
            else if(word % 2 == 0 && !(is_first_word && ch == ' ')){
                if(flag && word % 2 == 0){
                    printf("FLAGINIF !%c!\n", flag);
                    *(finalString + i) = flag;
                    i++;
                    flag = 0;
                }
                if(flag2 && word % 2 == 0){
                    printf("FLAG2INIF !%c!\n", flag2);
                    *(finalString + i) = flag2;
                    i++;
                    flag2 = 0;
                }
                if(flag3 && word % 2 == 0){
                    printf("FLAG3INIF !%c!\n", flag3);
                    *(finalString + i) = flag3;
                    i++;
                    flag3 = 0;
                }
                *(finalString + i) = ch;
                printf("CHAR !%c!\n", ch);
                i++;
                if(is_first_word && ch != ' ') {
                    is_first_word = 0;
                }
            }
                    
            ch = fgetc(input);
        }
    }
    while(finalString[i - 1] == ' '){
        finalString[i - 1] = 0;
        i--;
    }
    for (i = 0; *(finalString + i); i++){
        fputc(*(finalString + i), output);
    }
    fclose(input);
    fclose(output);
    return 0;
}

bool is_word(char ch){
    if(ch == '\n' || ch == ' ' || ch == '\t')
        return 0;
    return 1;
}

bool is_start(char* start_word, char ch, int index){
    if(ch == start_word[index]){
        return 1;
    }
    return 0;
}

bool is_end(char* end_word, char ch, int index){
    if(ch == end_word[index]){
        return 1;
    }
    return 0;
}