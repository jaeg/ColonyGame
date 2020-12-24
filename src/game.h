#ifndef GAME_H
#define GAME_H

#include <stack>
#include "world/level.h"
#include "renderer.h"
#include "resourcemanager.h"
#include "gamestate.h"
#include "mainstate.h"

class GameState;
class MainState;

class Game {
    public:
        Game(Renderer* renderer);
        void Update();
        void Draw();
        void DrawView(int aX, int aY, int width, int height, bool centered);

        bool Escape = false;
        void PollEvents();
    private:
        Renderer* renderer_;
        
        std::stack<GameState*> states_;
        
        void pushState(GameState* state);
        void popState();
        void changeState(GameState* state);
        GameState* peekState();
};

#endif
