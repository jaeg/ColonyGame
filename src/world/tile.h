#ifndef TILE_H
#define TILE_H

enum class TileType : int { EMPTY, GRASS, WALL, WATER, SAND};

struct Tile {
    TileType Type;
    int Variation;
};

#endif