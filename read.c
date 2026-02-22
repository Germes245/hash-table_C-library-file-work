#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    size_t* array_of_lengths;// длина включай нулевой терминатор
    size_t* array_of_indexes;
    size_t length;
} array_;

array_ length_of_strings(char array[], size_t length, size_t score){ // 1. блок 2. размер блока 3. количество строк
    array_ result;
    result.array_of_lengths = malloc(score*sizeof(size_t));
    result.array_of_indexes = malloc(score*sizeof(size_t));
    result.length = score;
    for(size_t i = 0, j = 0; i < length; j++){
        size_t length = strlen(array+i)+1;
        if(array[i] == 0) break;
        result.array_of_lengths[j] = length;
        result.array_of_indexes[j] = i;
        i += length;
    }
    return result;
}

int main(){
    FILE *file = fopen("test.bin", "rb");
    if (file == NULL) {
        perror("Ошибка открытия");
        return 1;
    }
    // узнаём размер блока и количество строк
    size_t size_of_block, score_of_strings;
    {
        size_t array[2];
        fread(array, sizeof(size_t), 2, file);
        size_of_block = array[0];
        score_of_strings = array[1];
    }
    char *text[score_of_strings];
    char block[size_of_block];
    register size_t i = 0;
    while(fread(block, sizeof(char), size_of_block, file) != 0){
        array_ result = length_of_strings(block, size_of_block, score_of_strings);
        //printf("lengths: ");
        //for(size_t i = 0; i < result.length; i++)
        //    printf("%d ", result.array_of_lengths[i]);
        //putchar('\n');
        //printf("indexes: ");
        //printf("result.length = %d\n", result.length);
        for(size_t i = 0; i < result.length; i++){
            //printf("index: %d\n", result.array_of_indexes[i]);
            write(1, block + result.array_of_indexes[i], result.array_of_lengths[i]);
        }
    }
    fclose(file);
    return 0;
}