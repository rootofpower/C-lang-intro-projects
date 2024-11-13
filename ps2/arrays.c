#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float lift_a_car(const int stick_length, const int human_weight, const int car_weight);
float unit_price(const float pack_price, const int rolls_count, const int pieces_count);
int bank_notes(const int price);
int euler(const int n);
int find_missing_number(const int n, const int arr[]);
unsigned long long sum_squared(const int line);
int array_min(const int input_array[], const int array_size);
int array_max(const int input_array[], const int array_size);
int factorize_count(const int n);
void podium(const int n, int arr[]);



int main()
{
    return 0;
}

float lift_a_car(const int stick_length, const int human_weight, const int car_weight){
    return round(((float)stick_length * human_weight / (human_weight + car_weight))* 100) / 100;
}
float unit_price(const float pack_price, const int rolls_count, const int pieces_count){
    return round(pack_price / (((float)rolls_count * pieces_count)/100) * 100) / 100;
}
int bank_notes(const int price){
    int sum = price, ans = 0;
    if(sum % 10 != 0) return -1;
    else{
        while(sum >= 200){sum -= 200; ans++;}
        while(sum >= 100){sum -= 100; ans++;}
        while(sum >= 50){sum -= 50; ans++;}
        while(sum >= 20){sum -= 20; ans++;}
        while(sum >= 10){sum -= 10; ans++;}
        return ans;
    }
}
int euler(const int n){
    int flag = 1, number = n;
    for(int i = 2; i * i <= number; i++){
            int multiplier = 1;
            while(number % i == 0){
                multiplier *= i;
                number /= i;
            }
            if((multiplier/=i) >= 1){
                flag *= multiplier * (i - 1);
            }
    }
    return --number ? number * flag : flag;
}
int find_missing_number(const int n, const int arr[]){
    int array[n];
    for(int i = 0; i < n; i++) array[i] = arr[i];
    for(int i = 1; i < n; i++){
        for(int j = i; j > 0 && array[j-1] > array[j]; j--){
            int tmp = array[j-1];
            array[j-1] = array[j];
            array[j] = tmp;
        }
    }
    int check = 0;
    for (int i = 0; i < n; i++){
        if(array[i] != check) return check;
        else check++;
    }
    return check;
}
unsigned long long sum_squared(int n) {
    int i, j, coef;
    unsigned long long answer = 0;
    unsigned long long row[n + 1];
    for (i = 0; i <= n; i++) {
        coef = 1;
        for (j = 0; j <= i; j++) {
            if (i == n) {
                row[j] = coef;
            }
            coef = coef * (i - j) / (j + 1);
        }
    }
    for (int i = 0; i < n + 1; i++) {
        answer += row[i] * row[i];
    }
    return answer;
}
int array_min(const int input_array[], const int array_size){
    if(input_array == NULL) return -1; 
    int n = array_size;
    int arr[n];
    for (int i = 0; i < n; i++){
        arr[i] = input_array[i];
    }
    for (int i = 0; i < n; i++) {
        int min = i;
        for(int j = i + 1; j < n; j++){
            if(arr[j] < arr[min]) min = j;           
        }
        int temp;
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
    return arr[0];
}
int array_max(const int input_array[], const int array_size){
    if(input_array == NULL) return -1; 
    int n = array_size;
    int arr[n];
    for (int i = 0; i < n; i++){
        arr[i] = input_array[i];
    }
    for (int i = 0; i < n; i++) {
        int min = i;
        for(int j = i + 1; j < n; j++){
            if(arr[j] < arr[min]) min = j;           
        }
        int temp;
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
    return arr[n-1];
}
int factorize_count(const int n){
    int counter = 0;
    int sieve[n];
    int arr[n];
    for (int i = 0; i < n; i++){
        sieve[i] = 0;
    }
    for (int i = 2; i < n; i++){
        if(sieve[i] == 0)
            for (int k = i*i; k < n; k += i){
                sieve[k] = 1;
            }
    }
    for (int i = 2; i < n; i++){
        if(sieve[i] == 0){
            arr[counter] = i;
            counter++;
        }
    }
    int ans = 0;
    for (int i = 0; i < counter; i++){
        if (n % arr[i] == 0){
            ans++;
        }
    }
    return ans;
}
void podium(const int n, int arr[]){
    int material = n, temp = 0; 
    if(material % 3 == 0) {
        for (int i = 0; i < 3; i++){
            arr[i] = material / 3;
        }
    arr[1]++;
    arr[2]--;
    }
    else {
        temp = material % 3;
        for (int i = 0; i < 3; i++){
            arr[i] = material / 3;
        }
        arr[1] += temp;
        while(arr[0] + 1 != arr[1]){
            arr[0]++;
            arr[2]--;

        }
    }
    return ;
}
