#include "level.h"

Level::Level(int width, int height) {
    width_ = width;
    height_ = height;

    tiles_ = new Tile[width_ * height_];
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            Tile newTile;
            newTile.type = 1;
            SetTile(x,y,newTile);
        }
    }
}


Tile Level::GetTile(int x, int y) {
    Tile nullTile;
    nullTile.type = -1;

    if (width_ < x || x < 0) {
        return nullTile;
    }

    if (height_ < y || y < 0) {
        return nullTile;
    }

    int i = x + width_-1 * y;

    return tiles_[i];
}

void Level::SetTile(int x, int y, Tile tile) {
    if (width_ < x || x < 0) {
        return;
    }

    if (height_ < y || y < 0) {
        return;
    }

    int i = x + width_ - 1 * y;

    tiles_[i] = tile;
}