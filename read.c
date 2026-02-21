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
    uint8_t size_for_array = sizeof(uint8_t)+sizeof(uint32_t);
    uint8_t *array = malloc(size_for_array);
    fread(array, size_for_array, 1, file);
    uint8_t size_of_block
    printf("%d, %d", *array, (uint32_t)*(array+1));
    fclose(file);
    return 0;
}