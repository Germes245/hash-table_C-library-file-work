#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    char **text;
    size_t length;
} char_pointer_array;

size_t get_score_of_null_symbols(char buffer[], size_t length){
    size_t score_of_null_symbols = 0;
    for(size_t i = 0; i < length; i++){
        if (buffer[i] == 0) {
            score_of_null_symbols++;
        }
    }
    return score_of_null_symbols;
}

char_pointer_array read_strings_from_file(char* name_of_file){
    // чтение файла в буффер
    FILE *file = fopen(name_of_file, "rb");
    if (file == NULL) {
        perror("Ошибка открытия");
        exit(1);
    }
    char buffer[60];
    fread(buffer, 1, sizeof(buffer), file);

    size_t score_of_null_symbols = get_score_of_null_symbols(buffer, sizeof(buffer)); // количество NULL символов
    char_pointer_array strings;

    size_t array_of_indexes[score_of_null_symbols];
    for (size_t i = 0, j = 0; i < sizeof(buffer); i++) {
        if (buffer[i] == 0) {
            // нахождение индексов NULL символов
            array_of_indexes[j] = i;
            j++;
        }
    }
    //putchar(buffer[sizeof(buffer)-1]);
    strings.length = score_of_null_symbols + 1 + (buffer[sizeof(buffer)-1] ? 1 : 0);
    strings.text = malloc(strings.length * sizeof(char*));
    printf("количество строк %d\n", strings.length);

    for (size_t i = 0; i < score_of_null_symbols; i++) {
        printf("%d ", array_of_indexes[i]);
    }
    putchar('\n');
    printf("memcpy: %d, %d\nand index: 0\n", 0, array_of_indexes[1]);

    strings.text[0] = malloc(array_of_indexes[1]);
    memcpy(strings.text[0], buffer, array_of_indexes[1]);

    for (size_t i = 1; i < score_of_null_symbols; i++) {
        printf("memcpy: %d, %d\nand index: %d\n", array_of_indexes[i-1], array_of_indexes[i], i);
        size_t length = array_of_indexes[i] - array_of_indexes[i-1];
        strings.text[i] = malloc(length);
        printf("%s\n", buffer + array_of_indexes[i-1] + 1);
        memcpy(strings.text[i], buffer + array_of_indexes[i-1] + 1, length);
    }
    printf("memcpy: %d, %d\nand index: %d\n", array_of_indexes[score_of_null_symbols-1], sizeof(buffer), score_of_null_symbols);

    //putchar('\n');
    printf("проверка:\n");

    for (size_t i = 0; i < score_of_null_symbols; i++) {
        printf("%s\n", strings.text[i]);
    }

    printf("%d\n", score_of_null_symbols);
    fclose(file);
    exit(1);
}

int main(){
    char_pointer_array text = read_strings_from_file("test.bin");
    return 0;
}
