#include "level.h"
#include <stdio.h>
#include <cmath>

Level::Level(int width, int height) {
    width_ = width;
    height_ = height;

    tiles_ = new Tile[width_ * height_];
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            SetTile(x,y,TileType::GRASS, rand() % 3);
        }
    }
}


Tile Level::GetTile(int x, int y) {
    Tile nullTile;
    nullTile.Type = TileType::EMPTY;
    if (width_ < x || x < 0) {
        return nullTile;
    }

    if (height_ < y || y < 0) {
        return nullTile;
    }

    int i = x + ((width_ - 1) * y);

    return tiles_[i];
}

void Level::SetTile(int x, int y, TileType tileType, int Variation) {
    if (width_ < x || x < 0) {
        return;
    }

    if (height_ < y || y < 0) {
        return;
    }

    int i = x + ((width_ - 1) * y);
    tiles_[i].Type = tileType;
    tiles_[i].Variation = Variation;
}

void Level::GenerateOverworld(int sX, int sY, int width, int height) {
    PerlinNoise pn;

    // Generate 
    for (int x = sX; x < width + sX; x++) {
        for (int y = sY; y < height + sY; y++) {
            double nx = (double)x/((double)width);
 			double ny = (double)y/((double)height);

            double s = 10;
            double n = pn.noise(nx * s,ny * s, .8);
            if (n < .5) {
                SetTile(x, y, TileType::WATER);
            } else if (n >= .5 && n < 0.55) {
                SetTile(x, y, TileType::SAND, rand() % 5);
            }
        }
    }
}

void Level::CreateSquareOfBlocks(int sX, int sY, int width, int height, TileType wall, TileType floor) {
    for (int x = sX; x < width + sX; x++) {
        for (int y = sY; y < height + sY; y++) {
            if (x == sX || x == width + sX - 1) {
                SetTile(x, y, wall);
            } else if (y == sY || y == height + sY - 1) {
                SetTile(x, y, wall);
            } else {
                SetTile(x, y, floor);
            }
        }
    }
}