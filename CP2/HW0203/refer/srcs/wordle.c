#include "wordle.h"

static const int64_t VOCABULARY_LENGTH = 5;

int32_t get_vocabulary_size(Dictory *dictory) {
    int32_t size = 0;
    for (int i = 0; i < dictory->size; i++) {
        if (dictory->vocabularies[i]->freq != 0) {
            // printf("allow: %s\n", dictory->vocabularies[i]->word);
            size++;
        } else {
            // printf("not allow: %s\n", dictory->vocabularies[i]->word);
        }
    }
    return size;
}

Vocabulary *advice_vocabulary(Dictory *dictory) {
    Vocabulary *advice = NULL;

    for (int i = 0; i < dictory->size; i++) {
        if (can_update_advice(advice, dictory->vocabularies[i])) {
            advice = dictory->vocabularies[i];
        }
    }

    return advice;
}

bool can_update_advice(Vocabulary *advice, Vocabulary *vocabulary) {
    if (vocabulary->freq == 0) {
        return false;
    }
    if (advice == NULL) {
        return true;
    }
    if (advice->freq >= vocabulary->freq) {
        return false;
    }

    return true;
}

void remove_vocabulary(Dictory *dictory, Vocabulary *advice, char *feedback) {
    for (int i = 0; i < dictory->size; i++) {
        if (!allow_vocabulary(feedback, advice->word, dictory->vocabularies[i]->word)) {
            dictory->vocabularies[i]->freq = 0;
        }
    }
}

bool allow_vocabulary(char *feedback, char *advice_word, char *vocabulary_word) {
    char result[VOCABULARY_LENGTH + 1] = {0};
    for (int i = 0; i < VOCABULARY_LENGTH; i++) {
       if (advice_word[i] == vocabulary_word[i]) {
           result[i] = 'G';
       }
    }

    bool advice_use[VOCABULARY_LENGTH] = {false};
    bool vocabulary_use[VOCABULARY_LENGTH] = {false};
    for (int i = 0; i < VOCABULARY_LENGTH; i++) {
        if (result[i] == 'G') {
            advice_use[i] = true;
            vocabulary_use[i] = true;
        }
    }
    for (int i = 0; i < VOCABULARY_LENGTH; i++) {
        for (int j = 0; j < VOCABULARY_LENGTH; j++) {
            if (advice_use[i] == 0 && vocabulary_use[j] == 0 && advice_word[i] == vocabulary_word[j]) {
                result[i] = 'Y';
                advice_use[i] = true;
                vocabulary_use[j] = true;
            }
        }
    }

    for (int i = 0; i < VOCABULARY_LENGTH; i++) {
        if (result[i] == 0) {
            result[i] = 'B';
        }
    }

    return strcmp(result, feedback) == 0;
}