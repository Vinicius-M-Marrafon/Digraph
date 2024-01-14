#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

typedef unsigned char byte;

typedef struct Matrix {
    byte *matrix;
    size_t lines, columns;
}
Matrix;

Matrix *newMatrix(size_t lines, size_t columns);
void setValueAt(Matrix *m, size_t line, size_t column, byte value);
byte getValueAt(Matrix *m, size_t line, size_t column);
void deleteMatrix(Matrix *m);
void dumpMatrix(Matrix *m);

// Add another functions in the future

#endif // MATRIX_H