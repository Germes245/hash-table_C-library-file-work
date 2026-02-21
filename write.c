#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define size_of_block 70

int main() {
    char *text[] = {"om namah shivaya", "om mani padme hum"};
    FILE *file = fopen("test.bin", "wb");
    if (file == NULL) {
        perror("Ошибка открытия");
        return 1;
    }
    {
        uint8_t size_for_array = sizeof(size_t)*2;
        size_t *array = malloc(size_for_array);
        array[0] = size_of_block; //в первые байты записываем размер блока
        array[1] = sizeof(text)/sizeof(char*);
        fwrite(array, size_for_array, 1, file);
        //write(1, array, size_for_array);
    }
    char block[size_of_block] = {0};
    uint8_t current_size_of_strings = 0;
    for(size_t i = 0; i < sizeof(text)/sizeof(void*); i++){
        size_t size = strlen(text[i])+1;
        if(size <= size_of_block - current_size_of_strings){
            memcpy(block+current_size_of_strings, text[i], size);
        }
        else{
            fwrite(block, sizeof(char), size_of_block*sizeof(char), file);
            for(size_t i = 0; i < size_of_block; i++)
                block[i] = 0;
            memcpy(block+current_size_of_strings, text[i], size); // возможно переполнение...
        }
        current_size_of_strings += size;
    }
    write(1, block, size_of_block);
    fwrite(block, sizeof(char), size_of_block, file);
    //printf("%d", current_size_of_strings);
    fclose(file);
    return 0;
}