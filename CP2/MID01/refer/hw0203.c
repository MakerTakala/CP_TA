#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 


#include "dictory.h"
#include "wordle.h"

const static int64_t MAX_FEEDBACK_LENGTH = 1024;

bool vaild_feedback(const char *input);
int32_t play_wordle(Dictory *dictory);

int main() {
    Dictory *dictory = get_dictory();
    int32_t result = play_wordle(dictory);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

bool vaild_feedback(const char *input) {
    if (strlen(input) != 5) {
        return false;
    }
    for (int i = 0; i < strlen(input); i++) {
        if (!isalpha(input[i])) {
            return false;
        }
        if (input[i] != 'G' && input[i] != 'Y' && input[i] != 'B') {
            return false;
        }
    }
    return true;
}

int32_t play_wordle(Dictory *dictory) {
    Vocabulary *advice;
    char feedback[MAX_FEEDBACK_LENGTH];
    while(1) {
        advice = advice_vocabulary(dictory);

        if (advice == NULL) {
            printf("No advice\n");
            return -1;
        }

        printf("Advice:   %s\n", advice->word);
        printf("Feedback: ");
        scanf("%s", feedback);
        if (!vaild_feedback(feedback)) {
            printf("Invalid Feedback\n");
            return -1;
        }
        if (strcmp(feedback, "GGGGG") == 0) {
            break;
        }
        remove_vocabulary(dictory, advice, feedback);
    }
    printf("Congratulations!!\n");
    return 0;
}