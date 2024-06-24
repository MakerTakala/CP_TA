#include "bmp.h"

Bmp_file *create_bmp_file(uint32_t offset, int32_t width, int32_t height, uint16_t bpp, uint32_t compression, int32_t hres, int32_t vres, uint32_t used, uint32_t important) {
    Bmp_file *bmp_file = (Bmp_file*)calloc(1, sizeof(Bmp_file));
    if (bmp_file == NULL) {
        return NULL;
    }

    bmp_file->header = (Bitmap_info_header*)calloc(1, sizeof(Bitmap_info_header));
    if (bmp_file->header == NULL) {
        free_bmp_file(bmp_file);
        return NULL;
    }

    bmp_file->row_size = ((bpp * width + 31) / 32) * 4;

    bmp_file->header->bm[0] = 'B';
    bmp_file->header->bm[1] = 'M';
    bmp_file->header->size = sizeof(Bitmap_info_header) + bmp_file->row_size * abs(height);
    bmp_file->header->reserve = 0;
    bmp_file->header->offset = offset;
    bmp_file->header->header_size = 40;
    bmp_file->header->width = width;
    bmp_file->header->height = height;
    bmp_file->header->planes = 1;
    bmp_file->header->bpp = bpp;
    bmp_file->header->compression = compression;
    bmp_file->header->bitmap_size = bmp_file->row_size * abs(height);
    bmp_file->header->hres = hres;
    bmp_file->header->vres = vres;
    bmp_file->header->used = used;
    bmp_file->header->important = important;

    bmp_file->data = (uint8_t*)calloc(1, bmp_file->header->bitmap_size);
    if (bmp_file->data == NULL) {
        free_bmp_file(bmp_file);
        return NULL;
    }

    return bmp_file;
}

void free_bmp_file(Bmp_file *bmp_file) {
    if (bmp_file == NULL) {
        return;
    }

    if (bmp_file->header) {
        free(bmp_file->header);
    }
    if (bmp_file->data) {
        free(bmp_file->data);
    }
    free(bmp_file);

    return;
}

Bmp_file *read_bmp (const char *filename) {
    if (filename == NULL) {
        return NULL;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL;
    }

    Bitmap_info_header header;

    const int header_count = fread(&header, sizeof(Bitmap_info_header), 1, fp);
    if(strncmp( header.bm, "BM", 2 ) || header_count != 1) {
        fclose(fp);
        return NULL;
    }

    Bmp_file *bmp_file = create_bmp_file(header.offset, header.width, header.height, header.bpp, header.compression, header.hres, header.vres, header.used, header.important);
    if (bmp_file == NULL) {
        fclose(fp);
        return NULL;
    }

    const int data_count = fread(bmp_file->data, bmp_file->header->bitmap_size, 1, fp);
    if (data_count != 1) {
        fclose(fp);
        free_bmp_file(bmp_file);
        return NULL;
    }

    fclose(fp);

    return bmp_file;
}

int write_bmp(const char *filename, const Bmp_file *bmp_file) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }

    const int header_count = fwrite(bmp_file->header, sizeof(Bitmap_info_header), 1, fp);
    if (header_count != 1) {
        fclose(fp);
        return -1;
    }

    const int data_count = fwrite(bmp_file->data, bmp_file->header->bitmap_size, 1, fp);
    if (data_count != 1) {
        fclose(fp);
        return -1;
    }

    fclose(fp);

    return 0;
}


void print_bmp_header (const Bitmap_info_header *pHeader) {
    printf("bm: %c%c\n", pHeader->bm[0], pHeader->bm[1]);
    printf("size: %d\n", pHeader->size);
    printf("reserve: %d\n", pHeader->reserve);
    printf("offset: %d\n", pHeader->offset);
    printf("header_size: %d\n", pHeader->header_size);
    printf("width: %d\n", pHeader->width);
    printf("height: %d\n", pHeader->height);
    printf("planes: %d\n", pHeader->planes);
    printf("bpp: %d\n", pHeader->bpp);
    printf("compression: %d\n", pHeader->compression);
    printf("bitmap_size: %d\n", pHeader->bitmap_size);
    printf("hres: %d\n", pHeader->hres);
    printf("vres: %d\n", pHeader->vres);
    printf("used: %d\n", pHeader->used);
    printf("important: %d\n", pHeader->important);
}
