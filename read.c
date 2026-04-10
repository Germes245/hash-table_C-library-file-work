#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    uint32_t* array_of_lengths;// длина включая нулевой терминатор
    uint32_t* array_of_indexes;
    uint32_t length;
} array_;

array_ length_of_strings(char array[], uint32_t length){ // 1. блок 2. размер блока 3. количество строк
    array_ result;
    result.length = 0;
    //write(1, array, length);
    for(uint32_t i = 0; i < length; i++){
        if(array[i] == 0){
            //printf("%d\n", i);
            result.length++;
            if((i + 1 == length) || (array[i + 1] == 0)){
                //printf("%d\n", i);
                break;
            }
        }
        //printf("%d, %d\n", array[i], array[i+1]);
    }
    //printf("%d\n", result.length);
    //exit(1);
    result.array_of_indexes = malloc(result.length * sizeof(uint32_t));
    result.array_of_lengths = malloc(result.length * sizeof(uint32_t));
    for(uint32_t index = 0, j = 0, length = 0; j < result.length; index++){
        if(array[index] == 0){
            result.array_of_indexes[j] = index;
            j++;
            result.array_of_indexes[j] = length;
            length = 0;
        }
        if(index + 1 == length && array[index + 1] == 0){
            break;
        }
        length++;
    }
    //write(1, result.array_of_indexes, result.length * sizeof(uint32_t));
    //for(int i = 0; i < result.length; i++) printf("%d ", result.array_of_indexes[i]);
    //write(1, array, length);
    //printf("%d", result.length);
    return result;
}

typedef struct{
    char **text;
    size_t length;
} char_pointer_array;

char_pointer_array read_strings_from_file(char* name_of_file){
    FILE *file = fopen(name_of_file, "rb");
    if (file == NULL) {
        perror("Ошибка открытия");
        exit(1);
    }
    char_pointer_array strings;
    uint32_t size_of_block;
    {
        uint32_t array[2];
        fread(array, sizeof(uint32_t), 2, file);
        size_of_block = array[0];
        strings.length = array[1];
    }
    strings.text = malloc(strings.length*sizeof(char*));
    char block[size_of_block];
    register size_t i = 0;
    while(fread(block, sizeof(char), size_of_block, file) != 0){
        array_ result = length_of_strings(block, size_of_block);
        //write(1, block, size_of_block);
        //printf("длина массива: %d\n", result.length);
        //("индексы: ");
        for(int i = 0; i < result.length; i++) printf("%d ", result.array_of_indexes[i]);
        putchar('\n');
        //printf("длины: ");
        //for(int i = 0; i < result.length; i++) printf("%d ", result.array_of_lengths[i]);
        //for(int i = 0; i < result.length; i++) printf("%s\n", block + result.array_of_indexes[i]);
        //putchar('\n');
        //exit(1);
    }
    //printf("%d\n", strings.length);
    fclose(file);
    return strings;
}

int main(){
    char_pointer_array text = read_strings_from_file("test.bin");
    /*for(size_t i = 0; i < text.length; i++){
        printf("%s\n", text.text[i]);
    }*/
    return 0;
}
