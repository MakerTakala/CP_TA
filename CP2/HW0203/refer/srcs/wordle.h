#pragma once

#include <stdio.h>

#include "dictory.h"
#include "util.h"

Vocabulary *advice_vocabulary(Dictory *dictory);
bool can_update_advice(Vocabulary *advice, Vocabulary *vocabulary);
void remove_vocabulary(Dictory *dictory, Vocabulary *vocabulary, char *result);
bool allow_vocabulary(char *feedback, char *advice_word, char *vocabulary_word);