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

char_pointer_array read_buffer(char buffer[], size_t length){
    size_t score_of_null_symbols = get_score_of_null_symbols(buffer, length); // количество NULL символов
    char_pointer_array strings;

    size_t array_of_indexes[score_of_null_symbols];
    for (size_t i = 0, j = 0; i < length; i++) {
        if (buffer[i] == 0) {
            // нахождение индексов NULL символов
            array_of_indexes[j] = i;
            j++;
        }
    }

    //strings.length = score_of_null_symbols + 1 + (buffer[length-1] ? 1 : 0);

    strings.length = score_of_null_symbols;
    //printf("%d\n", buffer[length-1]);
    if(buffer[length-1]){
        strings.length++;
        strings.text = malloc(strings.length * sizeof(char*));
        strings.text[strings.length - 1] = 0;
    }
    else {
        strings.text = malloc(strings.length * sizeof(char*));
    }

    //int fd = open("a.log", O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);

    strings.text[0] = malloc(array_of_indexes[1]);
    memcpy(strings.text[0], buffer, array_of_indexes[1]);
    //write(fd, buffer, array_of_indexes[1]);
    //write(fd, "\n", 1);

    for (size_t i = 1; i < score_of_null_symbols; i++) {
        size_t length = array_of_indexes[i] - array_of_indexes[i-1];
        strings.text[i] = malloc(length);
        memcpy(strings.text[i], buffer + array_of_indexes[i-1] + 1, length);
        //write(fd, buffer + array_of_indexes[i-1] + 1, length);
        //write(fd, "\n", 1);
    }
    //close(fd);

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
        printf("%d %s\n", array_of_strings.text[i], array_of_strings.text[i]);
    }

    //printf("%d\n", score_of_null_symbols);
    fclose(file);
    exit(1);
}

int main(){
    char_pointer_array text = read_strings_from_file("test.bin");
    return 0;
}
