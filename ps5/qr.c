#include<stdio.h>
#include<stdbool.h>
#include<string.h>

void encode_char(const char character, bool bits[8]); // solved
char decode_byte(const bool bits[8]); // solved
void encode_string(const char string[], bool bytes[strlen(string)+1][8]); // solved
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]); // solved
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]); // solved
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]); // solved

int main(int argc, char *argv[]){
    return 0;
}

//task 1
void encode_char(const char character, bool bits[8]){
    unsigned char mask = 128;
    for(int i = 0; i < 8; i++){
        bits[i] = ((mask & character) ? 1 : 0);
        mask >>= 1;
    }
}
//task 2
char decode_byte(const bool bits[8]){
    char c = 0;
    unsigned char mask = 128;
    for(int i = 0; i < 8; i++){
        c |= (bits[i] ? mask : 0);
        mask >>= 1;
    }
    return c;
}
//task 3
void encode_string(const char string[], bool bytes[strlen(string)+1][8]){
    int i = 0;
    while(string[i] != '\0'){
        encode_char(string[i], bytes[i]);
        ++i;
    }
    encode_char('\0', bytes[i]);
}
//task 4
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]){
    for(int i = 0; i < rows; i++){
        string[i] = decode_byte(bytes[i]);
    }
    string[rows] = '\0';
}
//task 5
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int flag = 0;
    for(int i = 0; i < offset; i++){
        for(int j = 0; j < cols; j++){
            for(int k = 0; k < 8; k++){
                blocks[i*8+k][j] = bytes[flag][k];
                if(flag >= rows){
                    blocks[i*8+k][j] = false;
                }   
            }
            flag++;
        }
    }
}
//task 6
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int flag = 0;
    for(int i = 0; i < offset; i++){
        for(int j = 0; j < cols; j++){
            for(int k = 0; k < 8; k++){
                bytes[flag][k] = blocks[i*8+k][j];
                if(flag >= rows){
                    bytes[flag][k] = false;
                }   
            }
            flag++;
        }
    }
}

