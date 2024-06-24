#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bmp.h"

typedef struct {
    long double x, y;
} Pos;

int draw_hist(Bmp_file *src_bmp_file, Bmp_file *dest_bmp_file, uint32_t radius);
static void get_color_amount(Bmp_file *bmp_file, uint64_t red_amount[], uint64_t green_amount[], uint64_t blue_amount[]);
static int64_t find_max_element(const uint64_t red_amount[], const uint64_t green_amount[], const uint64_t blue_amount[]);
static void tranform(const uint64_t amount[], Pos dest[], Bitmap_info_header *header, uint64_t max_element, bool reverse);
static void draw_line(Bmp_file *dest_bmp_file, Pos start, Pos end, uint32_t radius, Pixel color);
static void draw_circle(Bmp_file *dest_bmp_file, Pos center, uint64_t radius, Pixel color);
static bool is_safe(int32_t width, int32_t height, int32_t x, int32_t y);