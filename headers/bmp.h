#pragma pack(push, 1)

/*
 *  unsigned short = 2 BYTES
 *  unsigned       = 4 BYTES
 *  unsigned char  = 1 BYTE
 *
 */

typedef struct FILE_HEADER
{
    unsigned short signature;       // BM
    unsigned file_size;             
    unsigned short reserved1;       // 0
    unsigned short reserved2;       // 0
    unsigned metadata_size;         // 54
}
FILE_HEADER;

typedef struct INFO_HEADER
{
    unsigned int info_size;         // 40
    unsigned int width;             
    int height;                     
    unsigned short color_plane;     // 1
    unsigned short bpp;             // Bit per pixels
    unsigned int compressed;        // 0
    unsigned int image_size;        
    unsigned int resolution_x;      // 2834
    unsigned int resolution_y;      // 2834
    unsigned int color_table;       // 0
    unsigned int color_counter;     // 0
}
INFO_HEADER;

// Pixel
typedef struct RGB
{
    unsigned char blue;     // b
    unsigned char green;    // g
    unsigned char red;      // r
}
RGB;

#pragma pack(pop)