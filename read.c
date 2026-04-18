#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
    size_t score_of_null_symbols = get_score_of_null_symbols(buffer, length); // количество NULL символов

    size_t array_of_indexes[score_of_null_symbols];
    get_indexes(array_of_indexes, buffer, length);

    // 2
    if(buffer[length-1]){
        strings.length = score_of_null_symbols + 1;
        strings.text = malloc((strings.length + 1) * sizeof(char*));
        strings.text[strings.length] = 0;

        // копирование первой строки
        size_t length_of_array = array_of_indexes[0]+1;
        strings.text[0] = malloc(length_of_array);
        memcpy(strings.text[0], buffer, length_of_array);

        size_t i = 1;
        if(strings.length > 2){
            for(; i < strings.length - 1; i++){
                length_of_array = array_of_indexes[i] - array_of_indexes[i-1];
                strings.text[i] = malloc(length_of_array);
                memcpy(strings.text[i], buffer + array_of_indexes[i-1] + 1, length_of_array);
            }
        }

        // копирование последней строки
        length_of_array = (length-1) - (array_of_indexes[score_of_null_symbols-1]+1);
        strings.text[i] = malloc(length_of_array);
        memcpy(strings.text[i], buffer + array_of_indexes[score_of_null_symbols-1]+1, length_of_array);
        strings.text[i][length_of_array]=0;

        strings.length++;
    }
    else {
        // "первый случай"
        strings.length = score_of_null_symbols;
        strings.text = malloc(strings.length * sizeof(char*));

        // индексы границ у строк, которые будут скопированы в массив указателей
        size_t length = array_of_indexes[0]+1;
        strings.text[0] = malloc(length);
        memcpy(strings.text[0], buffer, length);
        counto(i, strings.length-1){
            length = array_of_indexes[i+1] - array_of_indexes[i]+1;
            strings.text[i+1] = malloc(length);
            memcpy(strings.text[i+1], buffer + array_of_indexes[i]+1, length);
        }
    }
    return strings;
}

char_pointer_array read_strings_from_file(char* name_of_file){
    // чтение файла в буффер
    FILE *file = fopen(name_of_file, "rb");
    if (file == NULL) {
        perror("Ошибка открытия");
        exit(1);
    }
    char buffer[0x31];
    size_t length = fread(buffer, 1, sizeof(buffer), file);
    char_pointer_array array_of_strings = read_buffer(buffer, length);
    counto(i, array_of_strings.length){
        printf("%s\n", array_of_strings.text[i]);
    }
    putchar('\n');
    length = fread(buffer, 1, sizeof(buffer), file);
    putchar(buffer[0]);
    putchar('\n');
    char_pointer_array array_of_strings2 = read_buffer(buffer, length);
    if(array_of_strings.text[array_of_strings.length-1]){
        size_t index = array_of_strings.length;
        array_of_strings.length += array_of_strings2.length;
        array_of_strings.text = realloc(array_of_strings.text, array_of_strings.length * sizeof(char*));
        counto(i, array_of_strings.length){
            printf("%d\n", array_of_strings.text[i]);
        }
        putchar('\n');
        for(size_t j = 0; index < array_of_strings.length; index++){
            array_of_strings.text[index] = array_of_strings2.text[j];
            j++;
        }
        counto(i, array_of_strings.length){
            printf("%s\n", array_of_strings.text[i]);
        }
    }
    else {
        printf("strings:\n");
        counto(i, array_of_strings2.length){
            printf("%s\n", array_of_strings2.text[i]);
        }
        putchar('\n');
        array_of_strings.text[array_of_strings.length-2] = realloc(array_of_strings.text[array_of_strings.length-2], strlen(array_of_strings.text[array_of_strings.length-2]) + strlen(array_of_strings2.text[0]) + 1);
        strcat(array_of_strings.text[array_of_strings.length-2], array_of_strings2.text[0]);

        counto(i, array_of_strings.length){
            printf("%s\n", array_of_strings.text[i]);
        }
        
        /*size_t index = array_of_strings.length-1;
        printf("длина первого: %d, длина второго: %d\n", array_of_strings.length, array_of_strings2.length);
        array_of_strings.length += array_of_strings2.length - 1;
        array_of_strings.text = realloc(array_of_strings.text, array_of_strings.length * sizeof(char*));
        for(size_t j = 0; index < array_of_strings.length; index++){
            array_of_strings.text[index] = array_of_strings2.text[j];
            j++;
        }
        printf("новая длина: %d\n", array_of_strings.length);
        counto(i, array_of_strings.length){
            printf("%s\n", array_of_strings.text[i]);
        }*/
    }
    fclose(file);
    exit(1);
}

int main(){
    char_pointer_array text = read_strings_from_file("test.bin");
    return 0;
}
