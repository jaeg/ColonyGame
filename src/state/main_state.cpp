#include "main_state.h"

void TestButtonHandler(GameState* state) {
    printf("Test handler!\n");
};


MainState::MainState(Renderer* renderer) {
    currentLevel_ = new Level(1000,1000);
    currentLevel_->GenerateOverworld(0,0,100,100);
    currentLevel_->CreateSquareOfBlocks(12,1,10,10, TileType::WALL, TileType::GRASS);

    currentLevel_->CreateCluster(20,20,100,TileType::WALL);

    renderer_ = renderer;
    resourceManager_ = new ResourceManager(renderer_);
    playerSystem_ = new PlayerSystem();
    simpleAISystem_ = new SimpleAISystem(currentLevel_);

    entityManger_ = new EntityManager();
    uiSystem_ = new UISystem(renderer_);
    eventManager_ = new EventManager();

    GameConfig config = GameConfig::LoadConfig("configfile");
    //Load resources
    for (auto c : config.Textures)
    {
        std::string name = c.first;
        std::string path = c.second;
        resourceManager_->LoadTexture(name,path);
    }

    //Create render system
    renderSystem_ = new RenderSystem(renderer_, resourceManager_);

    //Create component managers
    entityManger_->AddComponentManager("AppearanceComponent", new ComponentManager<AppearanceComponent>());
    entityManger_->AddComponentManager("PositionComponent", new ComponentManager<PositionComponent>());
    entityManger_->AddComponentManager("PlayerComponent", new ComponentManager<PlayerComponent>());
    entityManger_->AddComponentManager("WanderAIComponent", new ComponentManager<WanderAIComponent>());

    //Register component managers for render system
    renderSystem_->RegisterComponentManager("AppearanceComponent",entityManger_->GetComponentManager("AppearanceComponent"));
    renderSystem_->RegisterComponentManager("PositionComponent",entityManger_->GetComponentManager("PositionComponent"));

    //Register component managers for player system
    playerSystem_->RegisterComponentManager("PlayerComponent",entityManger_->GetComponentManager("PlayerComponent"));
    playerSystem_->RegisterComponentManager("PositionComponent",entityManger_->GetComponentManager("PositionComponent"));

    //Register component managers for simple ai system
    simpleAISystem_->RegisterComponentManager("WanderAIComponent",entityManger_->GetComponentManager("WanderAIComponent"));
    simpleAISystem_->RegisterComponentManager("PositionComponent",entityManger_->GetComponentManager("PositionComponent"));


    //Register event listeners
    eventManager_->RegisterListener("InputEvent",playerSystem_);
    eventManager_->RegisterListener("InputEvent",renderSystem_);

    //Create an entity
    int entityID = entityManger_->CreateEntity();
    auto ac = std::make_shared<AppearanceComponent>();
    ac->SpriteX = 0;
    ac->SpriteY = 0;
    entityManger_->GetComponentManagerAs<ComponentManager<AppearanceComponent>>("AppearanceComponent")->AddComponentTo(entityID, ac);

    auto pc = std::make_shared<PositionComponent>();
    pc->X = 0;
    pc->Y = 0;
    entityManger_->GetComponentManagerAs<ComponentManager<PositionComponent>>("PositionComponent")->AddComponentTo(entityID, pc);
    entityManger_->GetComponentManagerAs<ComponentManager<PlayerComponent>>("PlayerComponent")->AddComponentTo(entityID, std::make_shared<PlayerComponent>());

    //Create an wandering entity
    entityID = entityManger_->CreateEntity();
    ac = std::make_shared<AppearanceComponent>();
    ac->SpriteX = 0;
    ac->SpriteY = 64;
    entityManger_->GetComponentManagerAs<ComponentManager<AppearanceComponent>>("AppearanceComponent")->AddComponentTo(entityID, ac);

    pc = std::make_shared<PositionComponent>();
    pc->X = 1;
    pc->Y = 1;
    entityManger_->GetComponentManagerAs<ComponentManager<PositionComponent>>("PositionComponent")->AddComponentTo(entityID, pc);
    entityManger_->GetComponentManagerAs<ComponentManager<WanderAIComponent>>("WanderAIComponent")->AddComponentTo(entityID, std::make_shared<WanderAIComponent>());

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
            TileDef tileDef = TileLibrary::GetTileTypeDef(tile.Type);
            int sX = TileLibrary::IndexToCoordsX(tileDef.TextureIndex, 16) * 16;
            int sY = TileLibrary::IndexToCoordsY(tileDef.TextureIndex, 16) * 16;
            renderer_->DrawSprite(x*tileSize, y*tileSize, tileSize, tileSize, sX + (tile.Variation * 16), sY, 16, 16, resourceManager_->GetTexture("tileset"));
        }
    }
}

void MainState::Update() {
    // for (Entity* entity: entities_) {
    //     entity->Update(0);
    // }
    playerSystem_->Update(); 
    simpleAISystem_->Update();
};

void MainState::HandleInput(SDL_Event e) {
    if (e.type == SDL_KEYDOWN) {
        const Uint8 *state = SDL_GetKeyboardState(NULL); 
        
        //Create an event and put it into a shared  pointer so we keep it cleaned.
        InputEvent ie = InputEvent();
        ie.KeyBoardState = state;
        std::shared_ptr<Event> e = std::make_shared<InputEvent>(ie);
        eventManager_->SendEvent(e);
    }
    
    if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP) {
        //Forward the event to the ui system.
        uiSystem_->HandleInput(e,this);
    };
};