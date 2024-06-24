#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void* allocate(const size_t count, const size_t size);
void* reallocate(void* ptr, const size_t count, const size_t size);
FILE* open_file(const char* filename, const char* mode);
void to_upper(char* str);
void set_slash_end(char* str);