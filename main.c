#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include ".\headers\matrix.h"
#include ".\headers\bmp.h"

#define PI 3.14159265
#define MATRIX_SIZE 256
#define WINDOW_SIZE 2

void dumpMatrixToBMP(Matrix *m, const char *path)
{
    INFO_HEADER info = {
        .bpp = 24,                  // RGB
        .color_counter = 0,
        .color_plane = 0,
        .color_table = 1,
        .compressed = 0,
        .height = 256,
        .width = 256,
        .image_size = 256 * 256,
        .resolution_x = 2842,
        .resolution_y = 2842,
        .info_size = 40,
    };

    FILE_HEADER file = {
        .file_size = (256 * 256) + 54,
        .metadata_size = 54,
        .reserved1 = 0,
        .reserved2 = 0,
        .signature = 0x4d42
    };

    FILE *outfile = fopen(path, "wb");
    
    fwrite(&file, sizeof (FILE_HEADER), 1, outfile);
    fwrite(&info, sizeof (INFO_HEADER), 1, outfile);

    // Logarithmic scale
    float max = logf(getMaxValue(m));
    printf("M - MAX VALUE = %f\n", max);

    for (unsigned int i = 0; i < MATRIX_SIZE; i++) {
        for (unsigned int j = 0; j < MATRIX_SIZE; j++) {
            float brightness = logf(getValueAt(m, i, j))/ max;
            RGB white = { 
                .blue = 0x00, 
                .green = brightness * 0xFF,
                .red = 0x00
            };

            // RGB white = { .blue = 0x00, .green = 0xff, .red = 0x00 };
            fwrite(&white, sizeof (RGB), 1, outfile); 
        }
    }

    fclose(outfile);
    
}

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "[MAIN](Usage) %s -{infile}- -{outfile}\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "[MAIN - fileOpening] File %s not found!\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    Matrix *m = newMatrix(MATRIX_SIZE, MATRIX_SIZE);
    unsigned char pair[2];
    
    while (fread(&pair, sizeof (pair), 1, file)) {
        // printf("PAIR (%u, %u)\n", pair[0], pair[1]);
        // setValueAt(m, pair[0], pair[1], 32);
        
        // Frequency matrix

        // Cartesion coordinates
        // incrementValueAt(m, pair[0], pair[1]);

        // Polar coordinates
        float r = (pair[0] - 127);
        float theta = ((1.4 * pair[1]) * PI/ 180.0);

        // printf("R=%.2f; 0=%.2f", r, theta);

        int x = 128 - (int)(r * cosf(theta));
        int y = 128 - (int)(r * sinf(theta));

        // printf(" | X=%d; Y=%d\n", x, y);

        incrementValueAt(m, y, x);

        fseek(file, 1 - WINDOW_SIZE, SEEK_CUR);
    } 
    
    dumpMatrixToBMP(m, argv[2]);

    // dumpMatrix(m);
    deleteMatrix(m);

    fclose(file);

    return EXIT_SUCCESS;
}