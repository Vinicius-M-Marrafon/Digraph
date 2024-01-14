#include <stdio.h>
#include <stdlib.h>
#include ".\headers\matrix.h"
#include ".\headers\bmp.h"

#define WINDOW_SIZE 2

void dumpMatrixToBMP(Matrix *m, char *path)
{
    INFO_HEADER info = {
        .bpp = 24,
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

    for (unsigned int i = 0; i < 256; i++) {
        for (unsigned int j = 0; j < 256; j++) {
            if (getValueAt(m, i, j) != 0) {
                RGB white = { .blue = 0xff, .green = 0xff, .red = 0xff };
                // RGB white = { .blue = 0x00, .green = 0xff, .red = 0x00 };
                fwrite(&white, sizeof (RGB), 1, outfile); 
            }
            else {
                RGB white = { .blue = 0x00, .green = 0x00, .red = 0x00 };
                fwrite(&white, sizeof (RGB), 1, outfile);
            }
        }
    }

    fclose(outfile);
    
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "[MAIN](Usage) %s -{infile}-\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "[MAIN - fileOpening] File %s not found!\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    Matrix *m = newMatrix(256, 256);
    byte pair[2];
    
    while (fread(&pair, sizeof (pair), 1, file)) {
        // printf("PAIR (%u, %u)\n", pair[0], pair[1]);
        setValueAt(m, pair[0], pair[1], 32);
        fseek(file, 1 - WINDOW_SIZE, SEEK_CUR);
    } 
    
    dumpMatrixToBMP(m, ".\\noises\\exe1.bmp");

    // dumpMatrix(m);
    deleteMatrix(m);

    fclose(file);

    return EXIT_SUCCESS;
}