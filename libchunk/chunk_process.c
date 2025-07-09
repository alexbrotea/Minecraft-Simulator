#include "chunk.h"
#include <stdlib.h>

#define NUM_3D 6

char*** chunk_shell(
    char*** chunk, int width, int height, int depth,
    char target_block, char shell_block) {
    char*** new_chunk = malloc(width * sizeof(char**));
    for (int x = 0; x < width; x++) {
        new_chunk[x] = malloc(height * sizeof(char*));
        for (int y = 0; y < height; y++) {
            new_chunk[x][y] = malloc(depth * sizeof(char));
            memcpy(new_chunk[x][y], chunk[x][y], depth * sizeof(char));
        }
    }
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < depth; z++) {
                if (chunk[x][y][z] == target_block) {
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            for (int dz = -1; dz <= 1; dz++) {
                                if (dx == 0 && dy == 0 && dz == 0)
                                    continue;
                                int nx = x + dx;
                                int ny = y + dy;
                                int nz = z + dz;
                                if (nx >= 0 && nx < width &&
                                    ny >= 0 && ny < height &&
                                    nz >= 0 && nz < depth) {
                                    if (chunk[nx][ny][nz] != target_block) {
                                        int sum = abs(dx) + abs(dy) + abs(dz);
                                        if (sum == 1 || sum == 2) {
                                            new_chunk[nx][ny][nz] = shell_block;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            free(chunk[x][y]);
        }
        free(chunk[x]);
    }
    free(chunk);
    return new_chunk;
}

char*** chunk_fill_xz(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        char BB = chunk[x][y][z];
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
        return chunk;
    }
    if (chunk[x][y][z] != BB) {
        return chunk;
    }
    int max_stack_size = width * depth;
    int* stack_x = malloc(max_stack_size * sizeof(int));
    int* stack_z = malloc(max_stack_size * sizeof(int));
    if (!stack_x || !stack_z) {
        free(stack_x);
        free(stack_z);
        exit(EXIT_FAILURE);
    }
    int stack_top = 0;
    stack_x[stack_top] = x;
    stack_z[stack_top] = z;
    stack_top++;
    chunk[x][y][z] = block;
    int directions[4][2] = {
        {-1,  0},
        { 1,  0},
        { 0, -1},
        { 0,  1}
    };
    while (stack_top > 0) {
        stack_top--;
        int current_x = stack_x[stack_top];
        int current_z = stack_z[stack_top];
        for (int i = 0; i < 4; i++) {
            int nx = current_x + directions[i][0];
            int nz = current_z + directions[i][1];
            if (nx >= 0 && nx < width && nz >= 0 && nz < depth) {
                if (chunk[nx][y][nz] == BB) {
                    chunk[nx][y][nz] = block;
                    stack_x[stack_top] = nx;
                    stack_z[stack_top] = nz;
                    stack_top++;
                    if (stack_top >= max_stack_size) {
                        max_stack_size *= 2;
                        stack_x = realloc(stack_x, max_stack_size * sizeof(int));
                        stack_z = realloc(stack_z, max_stack_size * sizeof(int));
                        if (!stack_x || !stack_z) {
                            free(stack_x);
                            free(stack_z);
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
        }
    }
    free(stack_x);
    free(stack_z);
    return chunk;
}

char*** chunk_fill(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        char BB = chunk[x][y][z];
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
        return chunk;
    }
    if (chunk[x][y][z] != BB) {
        return chunk;
    }
    int max_stack_size = width * height * depth;
    int* stack_x = malloc(max_stack_size * sizeof(int));
    int* stack_y = malloc(max_stack_size * sizeof(int));
    int* stack_z = malloc(max_stack_size * sizeof(int));
    if (!stack_x || !stack_y || !stack_z) {
        free(stack_x);
        free(stack_y);
        free(stack_z);
        exit(EXIT_FAILURE);
    }
    int stack_top = 0;
    stack_x[stack_top] = x;
    stack_y[stack_top] = y;
    stack_z[stack_top] = z;
    stack_top++;
    chunk[x][y][z] = block;
    int directions[NUM_3D][3] = {
        {-1,  0,  0},
        { 1,  0,  0},
        { 0, -1,  0},
        { 0,  1,  0},
        { 0,  0, -1},
        { 0,  0,  1}
    };
    while (stack_top > 0) {
        stack_top--;
        int current_x = stack_x[stack_top];
        int current_y = stack_y[stack_top];
        int current_z = stack_z[stack_top];
        for (int i = 0; i < NUM_3D; i++) {
            int nx = current_x + directions[i][0];
            int ny = current_y + directions[i][1];
            int nz = current_z + directions[i][2];
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && nz >= 0 && nz < depth) {
                if (chunk[nx][ny][nz] == BB) {
                    chunk[nx][ny][nz] = block;
                    stack_x[stack_top] = nx;
                    stack_y[stack_top] = ny;
                    stack_z[stack_top] = nz;
                    stack_top++;
                    if (stack_top >= max_stack_size) {
                        max_stack_size *= 2;
                        stack_x = realloc(stack_x, max_stack_size * sizeof(int));
                        stack_y = realloc(stack_y, max_stack_size * sizeof(int));
                        stack_z = realloc(stack_z, max_stack_size * sizeof(int));
                        if (!stack_x || !stack_y || !stack_z) {
                            free(stack_x);
                            free(stack_y);
                            free(stack_z);
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
        }
    }
    free(stack_x);
    free(stack_y);
    free(stack_z);
    return chunk;
}
