#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
        
    }
    fclose(file);
    return 0;
}