#include "chunk.h"

#define MIN 1000000
#define MAX -1000000

char*** chunk_place_block(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
    if (x >= 0 && x < width
    && y >= 0 && y < height
    && z >= 0 && z < depth)
        chunk[x][y][z] = block;
    return chunk;
}

char*** chunk_fill_cuboid(
    char*** chunk, int width, int height, int depth,
    int x0, int y0, int z0, int x1, int y1, int z1, char block) {
    int min_x = MIN, max_x = MAX, min_y = MIN, max_y = MAX, min_z = MIN, max_z = MAX;
    if (x0 < x1) {
        min_x = x0;
        max_x = x1;
    } else {
        min_x = x1;
        max_x = x0;
    }
    if (y0 < y1) {
        min_y = y0;
        max_y = y1;
    } else {
        min_y = y1;
        max_y = y0;
    }
    if (z0 < z1) {
        min_z = z0;
        max_z = z1;
    } else {
        min_z = z1;
        max_z = z0;
    }
    if (min_x < 0) {
        min_x = 0;
    }
    if (max_x >= width) {
        max_x = width - 1;
    }
    if (min_y < 0) {
        min_y = 0;
    }
    if (max_y >= height) {
        max_y = height - 1;
    }
    if (min_z < 0) {
        min_z = 0;
    }
    if (max_z >= depth) {
        max_z = depth - 1;
    }
    for (int x = min_x; x <= max_x; x++) {
        for (int y = min_y; y <= max_y; y++) {
            for (int z = min_z; z <= max_z; z++) {
                chunk[x][y][z] = block;
            }
        }
    }
    return chunk;
}

char*** chunk_fill_sphere(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, double radius, char block) {
    double radius_sq = radius * radius;
    int min_x = (int)(x - radius);
    int max_x = (int)(x + radius);
    int min_y = (int)(y - radius);
    int max_y = (int)(y + radius);
    int min_z = (int)(z - radius);
    int max_z = (int)(z + radius);
    if (min_x < x - radius) {
        min_x--;
    }
    if (max_x > x + radius) {
        max_x++;
    }
    if (min_y < y - radius) {
        min_y--;
    }
    if (max_y > y + radius) {
        max_y++;
    }
    if (min_z < z - radius) {
        min_z--;
    }
    if (max_z > z + radius) {
        max_z++;
    }
    if (min_x < 0) {
        min_x = 0;
    }
    if (max_x >= width) {
        max_x = width - 1;
    }
    if (min_y < 0) {
        min_y = 0;
    }
    if (max_y >= height) {
        max_y = height - 1;
    }
    if (min_z < 0) {
        min_z = 0;
    }
    if (max_z >= depth) {
        max_z = depth - 1;
    }
    for (int i = min_x; i <= max_x; i++) {
        for (int j = min_y; j <= max_y; j++) {
            for (int k = min_z; k <= max_z; k++) {
                double dx = (double)(i - x);
                double dy = (double)(j - y);
                double dz = (double)(k - z);
                double distance_sq = dx * dx + dy * dy + dz * dz;
                if (distance_sq < radius_sq) {
                    chunk[i][j][k] = block;
                }
            }
        }
    }
    return chunk;
}
