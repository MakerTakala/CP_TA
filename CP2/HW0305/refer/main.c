#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "config.h"
#include "hist.h"

int main (int argc, char *argv[]) {

    Config *config = parse_args(argc, argv);

    if (config == NULL) {
        return -1;
    }

    Bmp_file *src_bmp_file = read_bmp(config->input);
    if (src_bmp_file == NULL) {
        free_config(config);
        return -1;
    }

    Bmp_file *dest_bmp_file = create_bmp_file(sizeof(Bitmap_info_header), config->width, config->height, 24, 0, 9449, 9449, 0, 0);
    if (dest_bmp_file == NULL) {
        free_config(config);
        free_bmp_file(src_bmp_file);
        return -1;
    }


    if (draw_hist(src_bmp_file, dest_bmp_file, config->line_width) != 0) {
        free_config(config);
        free_bmp_file(src_bmp_file);
        free_bmp_file(dest_bmp_file);
        return -1;
    }

    if (write_bmp(config->output, dest_bmp_file) != 0) {
        free_config(config);
        free_bmp_file(src_bmp_file);
        free_bmp_file(dest_bmp_file);
        return -1;
    }

    free_config(config);
    free_bmp_file(src_bmp_file);
    free_bmp_file(dest_bmp_file);



    return 0;
}