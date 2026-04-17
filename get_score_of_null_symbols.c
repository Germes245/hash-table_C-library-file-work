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
    printf("length of buffer: %ld\n", length);
    // 1
    char_pointer_array strings;
    size_t score_of_null_symbols = get_score_of_null_symbols(buffer, length); // количество NULL символов

    size_t array_of_indexes[score_of_null_symbols];
    get_indexes(array_of_indexes, buffer, length);
    printf("indexes of null symbols: ");
    counto(i, score_of_null_symbols){
        printf("%d ", array_of_indexes[i]);
    }
    putchar('\n');

    // 2
    if(buffer[length-1]){
        strings.length = score_of_null_symbols + 1;
        strings.text = malloc(strings.length * sizeof(char*));

        // копирование первой строки
        printf("(0, %ld)\n", array_of_indexes[0]);
        size_t length_of_array = array_of_indexes[0]+1;
        strings.text[0] = malloc(length_of_array);
        memcpy(strings.text[0], buffer, length_of_array);

        if(strings.length > 2){
            for(size_t i = 1; i < strings.length - 1; i++){
                /*length_of_array = array_of_indexes[i]+1;
                strings.text[i] = malloc(length_of_array);
                memcpy(strings.text[i], buffer, length_of_array);*/
                printf("(%ld, %ld)\n", array_of_indexes[i-1]+1, array_of_indexes[i]);
                length_of_array = array_of_indexes[i] - array_of_indexes[i-1];
                printf("length_of_array: %ld\n", length_of_array);
                strings.text[i] = malloc(length_of_array);
                memcpy(strings.text[i], buffer + array_of_indexes[i-1] + 1, length_of_array);
            }
        }

        // копирование последней строки
        printf("(%ld, %ld)\n", array_of_indexes[score_of_null_symbols-1]+1, length-1);
        length_of_array = length - array_of_indexes[score_of_null_symbols-1];
        strings.text[strings.length-1] = malloc(length_of_array);
        printf("farthest border: %d\n", array_of_indexes[score_of_null_symbols-1]+1+length_of_array);
        memcpy(strings.text[strings.length-1], buffer + array_of_indexes[score_of_null_symbols-1]+1, length_of_array);
    
        printf("strings:\n");
        counto(i, strings.length){
            printf("index %ld, and string %s\n", i, strings.text[i]);
        }
        //printf("%s\n", strings.text[0]);
    }
    else {
        // "первый случай"
        //printf("shya\n");
        strings.length = score_of_null_symbols;
        strings.text = malloc(strings.length * sizeof(char*));

        // индексы границ у строк, которые будут скопированы в массив указателей
        printf("(0, %d)\n", array_of_indexes[0]);
        size_t length = array_of_indexes[0]+1;
        strings.text[0] = malloc(length);
        memcpy(strings.text[0], buffer, length);
        counto(i, strings.length-1){
            //printf("index of string: %d\n", i+1);
            printf("(%d, %d)\n", array_of_indexes[i]+1, array_of_indexes[i+1]);
            length = array_of_indexes[i+1] - array_of_indexes[i]+1;
            strings.text[i+1] = malloc(length);
            memcpy(strings.text[i+1], buffer + array_of_indexes[i]+1, length);
        }
        counto(i, strings.length){
            printf("%s\n", strings.text[i]);
        }
    }
    //printf("length: %d\n", strings.length);
    exit(1);
}

int main(){
    char buffer[] = "ass\0sanga\0tampoi";
    //putchar(buffer[9]);
    char_pointer_array result = read_buffer(buffer, sizeof(buffer)-2);

    counto(i, result.length){
        printf("%s\n", result.text[i]);
    }
    return 0;
}