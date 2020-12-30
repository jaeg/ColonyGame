#ifndef LEVEL_H
#define LEVEL_H
#include "tile.h"
#include "../perlin/PerlinNoise.h"

class Level {
    public:
        Level(int width, int height);
        Tile GetTile(int x, int y);
        void SetTile(int x, int y, TileType tileType, int Variation = 0);

        int GetWidth() {
            return width_; 
        }
        int GetHeight() {
            return height_; 
        }

        void GenerateOverworld(int sX, int sY, int width, int height);
        void CreateSquareOfBlocks(int sX, int sY, int width, int height, TileType wall, TileType floor);
        void CreateCluster(int x, int y, int size, TileType type);

    private:
        int width_;
        int height_;
        Tile* tiles_;  
};

#endif