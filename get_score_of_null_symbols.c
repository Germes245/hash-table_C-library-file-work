#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct{
    char **text;
    size_t length;
} char_pointer_array;

#define counto(increment, up_value) for(size_t increment = 0; increment < up_value; increment++)

size_t get_score_of_null_symbols(char buffer[], size_t length){
    size_t score_of_null_symbols = 0;
    for(size_t i = 0; i < length; i++){
        if (buffer[i] == 0) {
            score_of_null_symbols++;
        }
    }
    return score_of_null_symbols;
}

void get_indexes(size_t indexes[], char buffer[], size_t length){
    for (size_t i = 0, j = 0; i < length; i++) {
        if (buffer[i] == 0) {
            // нахождение индексов NULL символов
            indexes[j] = i;
            j++;
        }
    }
}

char_pointer_array read_buffer(char buffer[], size_t length){
    // 1
    char_pointer_array strings;
    strings.length = get_score_of_null_symbols(buffer, length); // количество NULL символов
    size_t array_of_indexes[strings.length];
    get_indexes(array_of_indexes, buffer, length);

    counto(i, strings.length){
        printf("%d ", array_of_indexes[i]);
    }
    putchar('\n');

    //printf("shya\n");
    if(buffer[length-1]){
        strings.length++;
        strings.text = malloc(strings.length * sizeof(char*));
        strings.text[strings.length - 1] = 0;
    }
    else {
        strings.text = malloc(strings.length * sizeof(char*));
    }
    /*printf("shya1 %d\n", strings.length);
    strings.text[0] = malloc(array_of_indexes[1]);
    printf("shya2 and %d\n", array_of_indexes[1]);
    memcpy(strings.text[0], buffer, array_of_indexes[1]);
    printf("shya2 and %s\n", strings.text[0]);
    for (size_t i = 1; i < strings.length; i++) {
        size_t length = array_of_indexes[i] - array_of_indexes[i-1];
        strings.text[i] = malloc(length);
        memcpy(strings.text[i], buffer + array_of_indexes[i-1] + 1, length);
    }

    return strings;*/
}

int main(){
    char buffer[] = "ass\0sanga";
    char_pointer_array result = read_buffer(buffer, sizeof(buffer)-1);

    counto(i, result.length){
        printf("%s\n", result.text[i]);
    }
    return 0;
}