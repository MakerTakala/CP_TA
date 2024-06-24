#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

typedef struct {
    char *input;
    char *output;
    int width;
    int height;
    int line_width;
} Config;

Config* parse_args(int argc, char *argv[]);
Config* create_config();
void free_config(Config *config);
static void print_usage();