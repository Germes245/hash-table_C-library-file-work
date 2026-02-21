#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define size_of_block 70

int main() {
    char *text[] = {"om namah shivaya", "om mani padme hum"};
    FILE *file = fopen("test.bin", "wb");
    if (file == NULL) {
        perror("Ошибка открытия");
        return 1;
    }
    {
        uint8_t size = size_of_block;
        fwrite(&size, sizeof(uint8_t), sizeof(uint8_t), file);
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
    fwrite(block, sizeof(char), size_of_block, file);
    //printf("%d", current_size_of_strings);
    fclose(file);
    return 0;
}