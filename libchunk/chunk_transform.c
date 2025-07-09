#include "chunk.h"

char*** chunk_rotate_y(
    char*** chunk, int width, int height, int depth) {
    char*** new_chunk = malloc(depth * sizeof(char**));
    for (int i = 0; i < depth; i++) {
        new_chunk[i] = malloc(height * sizeof(char*));
        for (int j = 0; j < height; j++) {
            new_chunk[i][j] = malloc(width * sizeof(char));
            for (int k = 0; k < width; k++) {
                new_chunk[i][j][k] = 0;
            }
        }
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < depth; z++) {
                new_chunk[depth - 1 - z][y][x] = chunk[x][y][z];
            }
        }
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            free(chunk[i][j]);
        }
        free(chunk[i]);
    }
    free(chunk);
    return new_chunk;
}

char*** chunk_apply_gravity(
    char*** chunk, int width, int height, int depth, int* new_height) {
}
