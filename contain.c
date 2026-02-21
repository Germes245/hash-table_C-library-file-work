#include <stddef.h>
#include <stdio.h>

size_t contain(char array[], size_t bytes, char byte){
    for(size_t i = 0; i < bytes; i++){
        if(array[i] == byte){
            return ++i; // если найдено значение, то индекс + 1
        }
    }
    return 0; // если не найдено, то ноль
}

int main(){
    char chars[] = {110, 97, 0};
    printf("%d\n", contain(chars, sizeof(chars), 0));
    
    return 0;
}