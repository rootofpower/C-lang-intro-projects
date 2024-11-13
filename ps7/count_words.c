#include <stdio.h>

int main(int argc, char* argv[]){
    char check_frase[] = "ananas";
    if(argc != 2){
        printf("Wrong number of parameters.\n");
        return 1;
    }
    FILE* bananas = fopen(argv[1], "r");
    if(bananas == NULL){
        fputc(0, bananas);
        return 0;
    }
    char c;
    int count = 0, index = 0;
    while((c = fgetc(bananas)) != EOF){
        if(c == '\n' || c == ' ' || c == '\t')
            index = 0;
        if(c == check_frase[index]){
            index++;
            if(index == 6){
                count++;
                index = 0;
            }
      } 
      else if(c - 32 == check_frase[index] || c + 32 == check_frase[index]){
            index++;
            if(index == 6){
                count++;
                index = 0;
        }
      }
    }
    fclose(bananas);
    if(count > 10){
        int ans[5] = {0};
        ans[0] = count / 10;
        ans[1] = count % 10;
        bananas = fopen(argv[1], "w");
        fclose(bananas);
        bananas = fopen(argv[1], "a");
        fputc(ans[0] + 48, bananas);
        fputc(ans[1] + 48, bananas);
        fclose(bananas);
    }
    else{
        bananas = fopen(argv[1], "w");
        fclose(bananas);
        bananas = fopen(argv[1], "a");
        fputc(count + 48, bananas);
        fclose(bananas);
    }
    return 0;
}

