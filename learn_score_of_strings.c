#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    size_t* array;
    size_t length;
} array_;

array_ length_of_strings(char array[], size_t length, size_t score){ // 1. блок 2. размер блока 3. количество строк
    array_ result;
    result.array = malloc(score*sizeof(size_t));
    result.length = score;
    for(size_t i = 0, j = 0; i < length; j++){
        size_t length = strlen(array+i)+1;
        if(array[i] == 0) break;
        result.array[j] = length;
        i += length;
    }
    return result;
}

int main(){
    FILE *file = fopen("block.bin", "rb");
    if (file == NULL) {
        perror("Ошибка открытия");
        return 1;
    }
    char block[70];
    fread(block, sizeof(char), 70, file);
    fclose(file);
    /*for(size_t i = 0; i < 70;){
        size_t length = strlen(block+i)+1;
        if(block[i] == 0) break;
        printf("%d ", length);
        i += length;
    }*/
    array_ result = length_of_strings(block, 70, 2);
    for(size_t i = 0; i < result.length; i++){
        printf("%d ", result.array[i]);
    }
    //write(1, block+strlen(block), 10);
    return 0;
}