#ifndef GAME_H
#define GAME_H

#include <stack>
#include "world/level.h"
#include "renderer.h"
#include "resource_manager.h"
#include "state/game_state.h"
#include "state/main_state.h"

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
