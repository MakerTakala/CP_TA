#include "util.h"
#include "dictory.h"


static const char *DICT_FILENAME = "./data/en_US.dic";
const char *FREQUNCY_FILENAME = "./data/letter_frequency.txt";
static const int64_t MAX_VOCABULARY_LENGTH = 100;
static const int64_t ALLOW_VOCABULARY_LENGTH = 5;
static const int64_t VOCABULARY_LENGTH = 5;

static FILE *dictory_file;;
static long double *letter_frequency;

Dictory *get_dictory() {
    letter_frequency = get_frequency_table();
    dictory_file = open_file(DICT_FILENAME, "r");
    Dictory *dictory = get_vaild_dictory();
    fclose(dictory_file);

    return dictory;
}

static long double *get_frequency_table() {
    FILE *frequency_file = open_file(FREQUNCY_FILENAME, "r");
    long double *frequncy_table = (long double*)allocate(26, sizeof(long double));

    for (int i = 0; i < 26; i++) {
        fscanf(frequency_file, "%Lf", &frequncy_table[i]);
        frequncy_table[i] /= 100;
    }
    fclose(frequency_file);

    return frequncy_table;
}

static Dictory *get_vaild_dictory() {
    uint64_t dict_size = get_dict_size();
    Dictory *dictory = create_dictory(dict_size);

    for (int i = 0; i < dict_size; i++) {
        char *word = get_word();
        if (word == NULL){
            continue;
        }
        dictory->vocabularies[dictory->size] = create_vocabulary(word);
        dictory->size++;
    }
    dictory->vocabularies = reallocate(dictory->vocabularies, dictory->size, sizeof(Vocabulary));

    return dictory;
}

static uint64_t get_dict_size() {
    uint64_t dict_size;

    fscanf(dictory_file, "%llu", &dict_size);

    return dict_size;
}

static Dictory* create_dictory(const uint64_t size) {
    Dictory *dict = (Dictory*)allocate(1, sizeof(Dictory));

    dict->vocabularies = (Vocabulary**)allocate(size, sizeof(Vocabulary*));

    return dict;
}

static char *get_word() {
    char *word_buffer = (char*)allocate(MAX_VOCABULARY_LENGTH, sizeof(char));

    fscanf(dictory_file, "%s", word_buffer);
    to_upper(word_buffer);
    set_slash_end(word_buffer);
    if (!is_valid_word(word_buffer)) {
        free(word_buffer);
        return NULL;
    }

    return reallocate(word_buffer, VOCABULARY_LENGTH + 1, sizeof(char));
}

static bool is_valid_word(const char* word) {
    const uint64_t length = strlen(word);

    for (int i = 0; i < length; i++) {
        if (!isalpha(word[i])) {
            return false;
        }
    }
    if (strlen(word) != ALLOW_VOCABULARY_LENGTH) {
        return false;
    }

    return true;
}

Vocabulary *create_vocabulary(const char *word) {
    Vocabulary *vocabulary = (Vocabulary*)allocate(1, sizeof(Vocabulary));
    
    vocabulary->word = (char*)allocate(VOCABULARY_LENGTH + 1, sizeof(char));
    strcpy(vocabulary->word, word);
    vocabulary->freq = get_vocabulary_frequency(word);
    return vocabulary;
}

long double get_vocabulary_frequency(const char *word) {
    long double freq = 0;

    for (int i = 0; i < VOCABULARY_LENGTH; i++) {
        freq += letter_frequency[word[i] - 'A'];
    }

    return freq;
}