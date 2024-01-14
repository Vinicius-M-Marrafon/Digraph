#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdint.h>

typedef struct Matrix {
    uint32_t *matrix;
    size_t lines, columns;
}
Matrix;

Matrix *newMatrix(size_t lines, size_t columns);
void setValueAt(Matrix *m, size_t line, size_t column, uint32_t value);
uint32_t getValueAt(Matrix *m, size_t line, size_t column);
void deleteMatrix(Matrix *m);
void dumpMatrix(Matrix *m);
uint32_t getMaxValue(Matrix *m);
void incrementValueAt(Matrix *m, size_t line, size_t column);

// Add another functions in the future

#endif // MATRIX_H