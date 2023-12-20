#include <stdio.h>

#pragma pack(2)

#define IMG_WIDTH 256
#define IMG_HEIGHT 256

typedef struct {
    char signature[2];
    int file_size;
    short reserved1;
    short reserved2;
    int offset;
    int dib_header_size;
    int width;
    int height;
    short color_planes;
    short bits_per_pixel;
    int compression;
    int image_size;
    int x_pixels_per_meter;
    int y_pixels_per_meter;
    int colors_used;
    int important_colors;
} BMPHeader_t;

void draw_image(unsigned char *img);

int main(void) {
    unsigned char image_data[IMG_HEIGHT * IMG_WIDTH * 3];
    draw_image(image_data);

    BMPHeader_t bmp_header = {
        .signature = {'B', 'M'},
        .file_size = sizeof(bmp_header) + sizeof(image_data),
        .reserved1 = 0,
        .reserved2 = 0,
        .offset = sizeof(BMPHeader_t),
        .dib_header_size = sizeof(BMPHeader_t) - 14,
        .width = IMG_WIDTH,
        .height = IMG_HEIGHT,
        .color_planes = 1,
        .bits_per_pixel = 24,
        .compression = 0,
        .image_size = 0,
        .x_pixels_per_meter = 0,
        .y_pixels_per_meter = 0,
        .colors_used = 0,
        .important_colors = 0,
    };

    FILE *img = fopen("output.bmp", "wb");
    if (!img) {
        perror("fopen");
        return 1;
    }

    fwrite(&bmp_header, sizeof(BMPHeader_t), 1, img);
    fwrite(image_data, sizeof(image_data), 1, img);

    if (fclose(img) != 0) {
        perror("fclose");
        return 1;
    }

    return 0;
}

void draw_image(unsigned char *img) {
    for (int y = 0; y < 256; y++) {
        for (int x = 0; x < 256; x++) {
            img[2] = x;  // Red.
            img[1] = 0;  // Green.
            img[0] = y;  // Blue.
            img += 3;
        }
    }
}

