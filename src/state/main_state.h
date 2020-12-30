#ifndef MAINSTATE_H
#define MAINSTATE_H
#include <list>
#include <SDL2/SDL.h>
#include "game_state.h"
#include "../component/components.h"
#include "../renderer.h"
#include "../world/level.h"
#include "../resource_manager.h"
#include "../entity/entity_manager.h"
#include "../system/render_system.h"
#include "../system/player_system.h"
#include "../system/simple_ai_system.h"
#include "../event/event_manager.h"
#include "../config.h"

#include "../ui/ui_system.h"
#include "../ui/button.h"

#define TILE_SIZE 32

extern void TestButtonHandler(GameState* state);

class MainState: public GameState {
    public:
        MainState(Renderer* renderer);
        void Draw();
        void DrawView(int aX, int aY, int width, int height, bool centered);
        void Update();
        void HandleInput(SDL_Event e);
    private:
        RenderSystem* renderSystem_;
        PlayerSystem* playerSystem_;
        SimpleAISystem* simpleAISystem_;
        ResourceManager* resourceManager_;
        EntityManager* entityManger_;
        EventManager* eventManager_;
        UISystem* uiSystem_;
        Renderer* renderer_;
        Level* currentLevel_;
};

#endif