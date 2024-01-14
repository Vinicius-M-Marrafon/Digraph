#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix *newMatrix(size_t lines, size_t columns)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (matrix == NULL) {
        fprintf(stderr, "[MATRIX - newMatrix]: Object \"Matrix\" Allocation Failure\n");
        return NULL;
    }

    matrix->matrix = (uint32_t *)calloc((lines * columns), sizeof(uint32_t));
    if (matrix->matrix == NULL) {
        fprintf(stderr, "[MATRIX - newMatrix]: \"Matrix->matrix\" Allocation Failure\n");
        return NULL;
    }

    matrix->lines = lines;
    matrix->columns = columns;

    return matrix;
}

void setValueAt(Matrix *m, size_t line, size_t column, uint32_t value)
{
    if (m != NULL) {
        if (line > m->lines - 1) {
            fprintf(stderr, "[MATRIX - insertAt]: line out of bound!");
            return;
        } 

        if (column > m->columns - 1) {
            fprintf(stderr, "[MATRIX - insertAt]: column out of bound!");
            return;
        } 

        // m[5][5] -> m[25]
        // m[3][2] = 1
        // 5 * 3 + 2 -> 17;
        // [01][02][03][04][05]
        // [06][07][08][09][10]
        // [11][12][13][14][15]
        // [16][17]...

        m->matrix[(m->lines * line) + column] = value;
    }
    else {
        fprintf(stderr, "[MATRIX - setValueAt](ERROR): Matrix Object == NULL!\n");
    }
}

uint32_t getValueAt(Matrix *m, size_t line, size_t column)
{
    if (m != NULL) {
        if (line > m->lines - 1) {
            fprintf(stderr, "[MATRIX - getValueAt]: line out of bound!");
            return 0;
        } 

        if (column > m->columns - 1) {
            fprintf(stderr, "[MATRIX - getValueAt]: column out of bound!");
            return 0;
        }

        return m->matrix[(m->lines * line) + column];
    }
    else {
        fprintf(stderr, "[MATRIX - getValueAt](ERROR): Matrix Object == NULL!\n");
        return 0;
    }
}

void deleteMatrix(Matrix *m)
{
    if (m != NULL) {
        if (m->matrix != NULL) free(m->matrix);
        else fprintf(stderr, "[MATRIX - deleteMatrix](WARNING): Matrix->matrix == NULL!\n");

        free(m);
    }
    else {
        fprintf(stderr, "[MATRIX - deleteMatrix](ERROR): Matrix Object == NULL!\n");
    }
}

void dumpMatrix(Matrix *m)
{
    if (m != NULL) {
        for (unsigned int i = 0; i < m->lines; i++) {
            for (unsigned int j = 0; j < m->columns; j++) {
                printf("%u ", m->matrix[(i * m->lines) + j]);
            }
            printf("\n");
        }
    }
    else {
        fprintf(stderr, "[MATRIX - dumpMatrix](ERROR): Matrix Object == NULL!\n");
    }
}

uint32_t getMaxValue(Matrix *m)
{
    uint32_t max = 0;
    for (uint32_t i = 0; i < m->lines; i++) {
        for (uint32_t j = 0; j < m->columns; j++) {
            if (getValueAt(m, i, j) > max) max = getValueAt(m, i, j);
        }
    }

    return max;
}

void incrementValueAt(Matrix *m, size_t line, size_t column)
{
    if (m != NULL) {
        if (line > m->lines - 1) {
            fprintf(stderr, "[MATRIX - incrementValueAt]: line out of bound!\n");
        } 

        if (column > m->columns - 1) {
            fprintf(stderr, "[MATRIX - incrementValueAt]: column out of bound!\n");
        }

        m->matrix[(m->lines * line) + column]++;
    }
    else {
        fprintf(stderr, "[MATRIX - incrementValueAt](ERROR): Matrix Object == NULL!\n");
    }
}