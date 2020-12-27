#include "mainstate.h"

void TestButtonHandler(GameState* state) {
    printf("Test handler!\n");
};


MainState::MainState(Renderer* renderer) {
    currentLevel_ = new Level(1000,1000);
    renderer_ = renderer;
    resourceManager_ = new ResourceManager(renderer_);
    playerSystem_ = new PlayerSystem();

    entityManger_ = new EntityManager();
    uiSystem_ = new UISystem(renderer_);
    eventManager_ = new EventManager();

    //Load resources
    resourceManager_->LoadTexture("tileset","assets/tiny_galaxy_world.png");
    resourceManager_->LoadTexture("characters","assets/tiny_galaxy_monsters.png");

    //Create render system
    renderSystem_ = new RenderSystem(renderer_, resourceManager_);
    //Create component managers
    entityManger_->AddComponentManager("AppearanceComponent", new ComponentManager<AppearanceComponent>());
    entityManger_->AddComponentManager("PositionComponent", new ComponentManager<PositionComponent>());
    entityManger_->AddComponentManager("PlayerComponent", new ComponentManager<PlayerComponent>());

    //Register component managers for render system
    renderSystem_->RegisterComponentManager("AppearanceComponent",entityManger_->GetComponentManager("AppearanceComponent"));
    renderSystem_->RegisterComponentManager("PositionComponent",entityManger_->GetComponentManager("PositionComponent"));


    //Register component managers for player system
    playerSystem_->RegisterComponentManager("PlayerComponent",entityManger_->GetComponentManager("PlayerComponent"));
    playerSystem_->RegisterComponentManager("PositionComponent",entityManger_->GetComponentManager("PositionComponent"));

    eventManager_->RegisterListener("InputEvent",playerSystem_);

    //Register component managers with the entity manager.
    ComponentManager<AppearanceComponent>* acm = (ComponentManager<AppearanceComponent>*) entityManger_->GetComponentManager("AppearanceComponent");
    ComponentManager<PositionComponent>* pcm = (ComponentManager<PositionComponent>*) entityManger_->GetComponentManager("PositionComponent");
    
    //Create an entity
    int entityID = entityManger_->CreateEntity();
    auto ac = std::make_shared<AppearanceComponent>();
    ac->SpriteX = 0;
    ac->SpriteY = 0;
    acm->AddComponentTo(entityID, ac);

    auto pc = std::make_shared<PositionComponent>();
    pc->X = 0;
    pc->Y = 0;
    pcm->AddComponentTo(entityID, pc);

    //UI
    Button* btn = new Button(60,0,50,50);
    btn->SetHandler(&TestButtonHandler);
    //uiSystem_->AddElement(btn);
}
void MainState::Draw() {
    // Draw the viewable area of the map.
    DrawView(0,0,SCREEN_WIDTH/renderSystem_->getTileSize(), SCREEN_HEIGHT/renderSystem_->getTileSize(),false);

    //Temp render system call
    renderSystem_->Update(); 
    // UI System
    uiSystem_->Draw();
};

//DrawView
void MainState::DrawView(int aX, int aY, int width, int height, bool centered) {
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

    int tileSize = renderSystem_->getTileSize();
    for (int x = left; x <= right; x++) {
        for (int y = up; y <= down; y++) {
            Tile tile = currentLevel_->GetTile(x,y);
            if (tile.type == -1) {
                renderer_->DrawSprite(x*tileSize, y*tileSize, tileSize, tileSize, 0, 0, 16, 16, resourceManager_->GetTexture("tileset"));
            } else if (tile.type == 1) {
                renderer_->DrawSprite(x*tileSize, y*tileSize, tileSize, tileSize, 160, 112, 16, 16, resourceManager_->GetTexture("tileset"));
            } else if (tile.type == 2) {
                renderer_->DrawSprite(x*tileSize, y*tileSize, tileSize, tileSize, 0, 32, 16, 16, resourceManager_->GetTexture("tileset"));
            } else {
                renderer_->DrawSprite(x*tileSize, y*tileSize, tileSize, tileSize, 0, 48, 16, 16, resourceManager_->GetTexture("tileset"));
            }
        }
    }
}

void MainState::Update() {
    // for (Entity* entity: entities_) {
    //     entity->Update(0);
    // }
    playerSystem_->Update(); 
};

void MainState::HandleInput(SDL_Event e) {
    if (e.type == SDL_KEYDOWN) {
        const Uint8 *state = SDL_GetKeyboardState(NULL); 
        
        // Zoom level
        if ( state[SDL_SCANCODE_1] ) {
            renderSystem_->ZoomLevel = 1;
        }
        if ( state[SDL_SCANCODE_2] ) {
            renderSystem_->ZoomLevel = 2;
        }
        if ( state[SDL_SCANCODE_3] ) {
            renderSystem_->ZoomLevel = 3;
        }

        
        //Create an event and put it into a shared  pointer so we keep it cleaned.
        InputEvent ie = InputEvent();
        ie.KeyBoardState = state;
        std::shared_ptr<Event> e = std::make_shared<InputEvent>(ie);
        printf("After pointer made: %s\n", e->GetType().c_str());

        eventManager_->SendEvent(e);
    }
    
    if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP) {
        //Forward the event to the ui system.
        uiSystem_->HandleInput(e,this);
    };
};