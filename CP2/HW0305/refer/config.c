#include "config.h"

static const char *short_option = "i:o:w:h:l:H";
static const struct option long_options[] = {  
    {"input", 1, NULL, 'i'},
    {"output", 1, NULL, 'o'},
    {"width", 1, NULL, 'w'},
    {"height", 1, NULL, 'h'},
    {"line", 1, NULL, 'l'},
    {"help", 0, NULL, 'H'},
    {0, 0, 0, 0},  
};  

Config* parse_args(int argc, char *argv[]) {
    Config *config = create_config();
    if (config == NULL) {
        free_config(config);
        return NULL;
    }

    int c = 0;
    int index = 0;
    while ((c = getopt_long(argc, argv, short_option, long_options, &index)) != -1) {
        switch (c) {
            case 'i':
                strcpy(config->input, optarg);
                break;
            case 'o':
                strcpy(config->output, optarg);
                break;
            case 'w':
                if (atoll(optarg) < 0) {
                    printf("width should be positive\n");
                    free_config(config);
                    return NULL;
                }
                config->width = atoll(optarg);
                break;
            case 'h':
                config->height = atoll(optarg);
                break;
            case 'l':
                if (atoll(optarg) < 0) {
                    printf("line width should be positive\n");
                    free_config(config);
                    return NULL;
                }
                config->line_width = atoll(optarg);
                break;
            case 'H':
                print_usage();
                break;
            case '?':
                printf("Unknow argument\n");
                print_usage();
                return NULL;
            default:
                free_config(config);
                return NULL;
        }
    }

    return config;
}

Config* create_config() {
    Config *config = (Config*)calloc(1, sizeof(Config));
    if (config == NULL) {
        return NULL;
    }

    config->input = (char*)calloc(256, sizeof(char));
    if (config->input == NULL) {
        free_config(config);
        return NULL;
    }

    config->output = (char*)calloc(256, sizeof(char));
    if (config->output == NULL) {
        free_config(config);
        return NULL;
    }

    return config;
}

void free_config(Config *config) {
    if (config == NULL) {
        return;
    }

    if (config->input) {
        free(config->input);
    }
    if (config->output) {
        free(config->output);
    }
    free(config);
    
    return;
}

static void print_usage() {
    printf("Usage: \n");
    printf("  -i, --input: input file\n");
    printf("  -o, --output: output file\n");
    printf("  -w, --width: width\n");
    printf("  -h, --height: height\n");
    printf("  -l, --line_width: line width\n");
    printf("  -H, --help: print usage\n");
    return;
}