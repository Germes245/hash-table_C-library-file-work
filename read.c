#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

int main(){
    FILE *file = fopen("test.bin", "rb");
    if (file == NULL) {
        perror("Ошибка открытия");
        return 1;
    }
    uint8_t size;
    fread(&size, 1, 1, file);
    //printf("%d", size);
    char block[size];
    for(uint8_t i = 0; i < size; i++){
        block[i] = 0;
    }
    uint8_t size2;
    while((size2 = fread(block, 1, size, file)) != 0){
        
    }
    fclose(file);
    return 0;
}