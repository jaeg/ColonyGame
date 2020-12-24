#include "game.h"

void Game::Draw() {
    int levelWidth = currentLevel_->GetWidth();
    int levelHeight = currentLevel_->GetHeight();

    for (int x = 0; x < levelWidth; x++){
        for (int y = 0; y < levelHeight; y++) {
            Tile tile = currentLevel_->GetTile(x,y);
            if (tile.type == -1) {
                renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 0, 16, 16, resourceManager_->GetTexture("tileset"));
            } else if (tile.type == 1) {
                renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 16, 16, 16, resourceManager_->GetTexture("tileset"));
            } else if (tile.type == 2) {
                renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 32, 16, 16, resourceManager_->GetTexture("tileset"));
            } else {
                renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 48, 16, 16, resourceManager_->GetTexture("tileset"));
            }
            
            Tile newTile;
            newTile.type = 2;
            currentLevel_->SetTile(x,y,newTile);
        }
    }
};


void Game::DrawView(int aX, int aY, int width, int height, bool centered) {
            int left = aX - width/2;
            int right = aX + width/2;
            int up = aY - height/2;
            int down = aY + height/2;

            if (centered == false) {
                left = aX;
                right = aX + width - 1;
                up = aY;
                down = aY + height;
            }

            for (int x = left; x <= right; x++) {
                for (int y = up; y <= down; y++) {
                    Tile tile = currentLevel_->GetTile(x,y);
                    if (tile.type == -1) {
                        renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 0, 16, 16, resourceManager_->GetTexture("tileset"));
                    } else if (tile.type == 1) {
                        renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 16, 16, 16, resourceManager_->GetTexture("tileset"));
                    } else if (tile.type == 2) {
                        renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 32, 16, 16, resourceManager_->GetTexture("tileset"));
                    } else {
                        renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 48, 16, 16, resourceManager_->GetTexture("tileset"));
                    }
                }
            }
        }