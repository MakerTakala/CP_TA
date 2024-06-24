#pragma once

#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>


typedef struct {
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    int32_t	    width;
    int32_t	    height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    int32_t	    hres;
    int32_t	    vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__)) Bitmap_info_header;

typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} Pixel;

typedef struct {
    Bitmap_info_header *header;
    uint32_t row_size;
    uint8_t *data;
} Bmp_file;


Bmp_file *create_bmp_file(uint32_t offset, int32_t width, int32_t height, uint16_t bpp, uint32_t compression, int32_t hres, int32_t vres, uint32_t used, uint32_t important);
void free_bmp_file(Bmp_file *bmp_file);
Bmp_file *read_bmp (const char *filename);
int write_bmp(const char *filename, const Bmp_file *bmp_file);
void print_bmp_header (const Bitmap_info_header *pHeader);