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
    for(size_t i = 0; i < sizeof(buffer); i++){
        if (buffer[i] == 0) {
            score_of_null_symbols++;
        }
    }
    return score_of_null_symbols;
}

char_pointer_array read_strings_from_file(char* name_of_file){
    FILE *file = fopen(name_of_file, "rb");
    if (file == NULL) {
        perror("Ошибка открытия");
        exit(1);
    }
    char buffer[60];
    fread(buffer, 1, sizeof(buffer), file);
    //write(1, buffer, sizeof(buffer));
    size_t score_of_null_symbols = 0;
    for(size_t i = 0; i < sizeof(buffer); i++){
        if (buffer[i] == 0) {
            score_of_null_symbols++;
        }
    }
    char_pointer_array strings;
    //strings.length=score_of_null_symbols + 1;
    //strings.text = malloc(sizeof(char*) * (strings.length));
    size_t array_of_indexes[score_of_null_symbols];

    for (size_t i = 0, j = 0; i < sizeof(buffer); i++) {
        if (buffer[i] == 0) {
            array_of_indexes[j] = i;
            j++;
        }
    }
    for (size_t i = 0; i < score_of_null_symbols; i++) {
        printf("%d ", array_of_indexes[i]);
    }
    putchar('\n');
    printf("memcpy: %d, %d\n", 0, array_of_indexes[1]);

    for (size_t i = 1; i < score_of_null_symbols; i++) {
        printf("memcpy: %d, %d\n", array_of_indexes[i-1], array_of_indexes[i]);
    }
    printf("memcpy: %d, %d\n", array_of_indexes[score_of_null_symbols-1], sizeof(buffer));
    putchar('\n');

    printf("%d\n", score_of_null_symbols);
    strings.length = score_of_null_symbols + 1;
    strings.text = malloc(sizeof(char*) * (strings.length));
    //memcpy(void *, const void *, __size_t)
    //strings.text[0]
    fclose(file);
    exit(1);
}

int main(){
    char_pointer_array text = read_strings_from_file("test.bin");
    return 0;
}
