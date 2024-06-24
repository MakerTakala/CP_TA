#include "util.h"

void* allocate(const size_t count, const size_t size) {
    void *ptr = calloc(count, size);
    if (ptr == NULL) {
        printf("Error: Could not allocate memory!\n");
        exit(1);
    }
    return ptr;
}

void* reallocate(void* ptr, const size_t count, const size_t size) {
    void *new_ptr = realloc(ptr, count * size);
    if (new_ptr == NULL) {
        printf("Error: Could not reallocate memory!\n");
        exit(1);
    }
    return new_ptr;
}

FILE* open_file(const char* filename, const char* mode) {
    FILE* dict_file = fopen(filename, mode);
    if (dict_file == NULL) {
        printf("Error: Could not open dictionary file!\n");
        exit(1);
    }
    return dict_file;
}

void to_upper(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

void set_slash_end(char* str) {
    char *slash = strchr(str, '/');
    if (slash != NULL) {
        *slash = '\0';
    }
}
