#ifndef TILE_H
#define TILE_H

#include <stdio.h>

struct TileDef {
    int TextureIndex;
    bool Solid;
    bool Water;
    bool Stairs;
    int Variations;
};

enum class TileType : int { EMPTY, GRASS, WALL, WATER, SAND, FLOOR};
//https://stackoverflow.com/questions/15181579/c-most-efficient-way-to-compare-a-variable-to-multiple-values
static const unsigned SolidTiles = (1 << (int)TileType::WALL);
static const unsigned WaterTiles = (1 << (int)TileType::WATER);
static const unsigned LandTiles = (1 << (int)TileType::SAND) | (1 << (int)TileType::GRASS);

struct Tile {
    TileType Type;
    int Variation;
};

class TileLibrary {
    public:
    static TileDef GetTileTypeDef(TileType type) {
        TileDef tileDef;

        if (type == TileType::EMPTY) {
            tileDef.TextureIndex = 0;
        } else if (type == TileType::GRASS) {
            tileDef.TextureIndex = 120;
            tileDef.Variations = 3;
        } else if (type == TileType::SAND) {
            tileDef.TextureIndex = 104;
            tileDef.Variations = 3;
        } else if (type == TileType::WALL) {
            tileDef.TextureIndex = 0;
            tileDef.Variations = 3;
        } else if (type == TileType::FLOOR) {
            tileDef.TextureIndex = 160;
            tileDef.Variations = 4;
        } else if (type == TileType::WATER) {
            tileDef.TextureIndex = 180;
        } else {
            tileDef.TextureIndex = 96;
        }        

        return tileDef;
    };

    static int CoordsToIndex(int x, int y, int width) {
        return x + ((width - 1) * y);
    }
    static int IndexToCoordsX(int i, int width) {
        return i % width;
    }

    static int IndexToCoordsY(int i, int width) {
        return  i / width; 

    }
};

#endif