#ifndef LEVEL_H
#define LEVEL_H
#include "tile.h"

class Level {
    public:
        Level(int width, int height);
        Tile GetTile(int x, int y);
        void SetTile(int x, int y, Tile tile);
        int GetWidth() {
            return width_; 
        }
        int GetHeight() {
            return height_; 
        }
    private:
        int width_;
        int height_;
        Tile* tiles_;  
};

#endif