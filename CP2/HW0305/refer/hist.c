#include "hist.h"

#define MAX_COLOR_SIZE 256
#define max(a, b) ((a) > (b) ? (a) : (b))

int draw_hist(Bmp_file *src_bmp_file, Bmp_file *dest_bmp_file, uint32_t radius) {
    if (src_bmp_file == NULL || dest_bmp_file == NULL || radius <= 0) {
        return -1;
    }

    uint64_t red_amount[MAX_COLOR_SIZE] = {0}, green_amount[MAX_COLOR_SIZE] = {0}, blue_amount[MAX_COLOR_SIZE] = {0};
    get_color_amount(src_bmp_file, red_amount, green_amount, blue_amount);

    const int64_t max_element = find_max_element(red_amount, green_amount, blue_amount);

    Pos red_pos[MAX_COLOR_SIZE] = {0}, green_pos[MAX_COLOR_SIZE] = {0}, blue_pos[MAX_COLOR_SIZE] = {0};

    tranform(red_amount, red_pos, dest_bmp_file->header, max_element, dest_bmp_file->header->height < 0);
    tranform(green_amount, green_pos, dest_bmp_file->header, max_element, dest_bmp_file->header->height < 0);
    tranform(blue_amount, blue_pos, dest_bmp_file->header, max_element, dest_bmp_file->header->height < 0);
    
    for (int i = 0; i < MAX_COLOR_SIZE - 1; i++) {
        draw_line(dest_bmp_file, red_pos[i], red_pos[i + 1], radius, (Pixel){255, 0, 0});
        draw_line(dest_bmp_file, green_pos[i], green_pos[i + 1], radius, (Pixel){0, 255, 0});
        draw_line(dest_bmp_file, blue_pos[i], blue_pos[i + 1], radius, (Pixel){0, 0, 255});
    }

    return 0;
}

static void get_color_amount(Bmp_file *bmp_file, uint64_t red_amount[], uint64_t green_amount[], uint64_t blue_amount[]) {
    const int32_t height = abs(bmp_file->header->height), width = bmp_file->header->width, row_size = bmp_file->row_size;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            const uint32_t index = (i * row_size + j * 3);
            red_amount[bmp_file->data[index + 0]]++;
            green_amount[bmp_file->data[index + 1]]++;
            blue_amount[bmp_file->data[index + 2]]++;
        }
    }
}

static int64_t find_max_element(const uint64_t red_amount[], const uint64_t green_amount[], const uint64_t blue_amount[]) {
    int64_t max_ele = 0;
    for (int i = 0; i < MAX_COLOR_SIZE; i++) {
        max_ele = max(max_ele, max(red_amount[i], max(green_amount[i], blue_amount[i])));
    }
    return max_ele;
}

static void tranform(const uint64_t amount[], Pos dest[], Bitmap_info_header *header, uint64_t max_element, bool reverse) {
    for (int i = 0; i < MAX_COLOR_SIZE; i++) {
        dest[i].x = (long double)i * (long double)header->width /  (long double)MAX_COLOR_SIZE;
        if (reverse) {
            dest[i].y = (long double)abs(header->height) - (long double)amount[i] * (long double)abs(header->height) / (long double)max_element;
        } else {
            dest[i].y = (long double)amount[i] * (long double)abs(header->height) / (long double)max_element;
        }
    }
}

static void draw_line(Bmp_file *dest_bmp_file, Pos start, Pos end, uint32_t radius, Pixel color) {
    const long double p = (end.y - start.y) / (end.x - start.x);

    long double curr_y = start.y;
    for (long double x = start.x; x < end.x; x++) {
        long double next_x = x + 1;
        long double next_y = curr_y + p;
        if (p >= 0) {
            for (long double y = curr_y; y <= next_y; y++) {
                Pos pos = {y < (next_y + curr_y) / 2 ? x : next_x, y};
                draw_circle(dest_bmp_file, pos, radius, color);
            }
        } else {
            for (long double y = curr_y; y >= next_y; y--) {
                Pos pos = {y > (next_y + curr_y) / 2 ? x : next_x, y};
                draw_circle(dest_bmp_file, pos, radius, color);
            }
        }
        curr_y = next_y;
    }

    return;
}

static void draw_circle(Bmp_file *dest_bmp_file, Pos center, uint64_t radius, Pixel color) {
    const int32_t height = abs(dest_bmp_file->header->height), width = dest_bmp_file->header->width, row_size = dest_bmp_file->row_size;
    for (int i = radius - 1; i >= 0; i--) {
        for (int j = 0; j < 360; j++) {
            const uint32_t x = center.x + (long double)i * (long double)cos(j);
            const uint32_t y = center.y + (long double)i * (long double)sin(j);
            if (!is_safe(width, height, x, y)) continue;

            const uint32_t index = (y * row_size + x * 3);
            const double scale = 1.0 - (double)i / (double)radius;
            dest_bmp_file->data[index + 0] |= (uint8_t)(color.b * scale);
            dest_bmp_file->data[index + 1] |= (uint8_t)(color.g * scale);
            dest_bmp_file->data[index + 2] |= (uint8_t)(color.r * scale);
        }
    }
}

static bool is_safe(int32_t width, int32_t height, int32_t x, int32_t y) {
    if (x < width && y < height) {
        return true;
    }
    return false;
}