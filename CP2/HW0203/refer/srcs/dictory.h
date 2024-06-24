#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Vocabulary {
    char* word;
    long double freq;
} Vocabulary;

typedef struct Dictory {
    Vocabulary **vocabularies;
    uint64_t size;
} Dictory;


Dictory *get_dictory();
static long double *get_frequency_table();
static Dictory *get_vaild_dictory();
static uint64_t get_dict_size();
static Dictory* create_dictory(const uint64_t size);
static char *get_word();
static bool is_valid_word(const char* word);
Vocabulary *create_vocabulary(const char *word);
long double get_vocabulary_frequency(const char *word);