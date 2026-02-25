#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//#define size_of_block 70

int main() {
    char *text[] = {"om namah shivaya namah shivaya hara hara bole namah shivaya", "om mani padme hum"};
    uint32_t size_of_block = 0, number_of_strings_in_text = sizeof(text)/sizeof(char*);
    for(uint32_t i = 0; i < number_of_strings_in_text; i++){
        uint32_t len = strlen(text[i]);
        printf("len %d\n", len);
        if(len > size_of_block) size_of_block = len + 1;
    }
    printf("size_of_block %d\n", size_of_block);
    FILE *file = fopen("test.bin", "wb");
    if (file == NULL) {
        perror("Ошибка открытия");
        return 1;
    }
    {
        uint8_t size_for_array = sizeof(uint32_t)*2;
        uint32_t *array = malloc(size_for_array);
        array[0] = size_of_block; //в первые байты записываем размер блока
        array[1] = number_of_strings_in_text;
        fwrite(array, size_for_array, 1, file);
        //write(1, array, size_for_array);
    }
    char block[size_of_block];
    for(uint32_t i = 0; i < size_of_block; i++){
        block[i] = 0;
    }
    uint8_t current_size_of_strings = 0;
    for(size_t i = 0; i < sizeof(text)/sizeof(void*); i++){
        size_t size = strlen(text[i])+1;
        printf("shya\n");
        if(size <= size_of_block - current_size_of_strings){
            printf("shya1\n");
            memcpy(block+current_size_of_strings, text[i], size);
        }
        else{
            printf("shya2\n");
            fwrite(block, sizeof(char), size_of_block*sizeof(char), file);
            for(size_t i = 0; i < size_of_block; i++)
                block[i] = 0;
            memcpy(block, text[i], size); // возможно переполнение...
        }
        current_size_of_strings += size;
    }
    //write(1, block, size_of_block);
    fwrite(block, sizeof(char), size_of_block, file);
    //printf("%d", current_size_of_strings);
    fclose(file);
    return 0;
}