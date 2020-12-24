#include "game.h"
Game::Game(Renderer* renderer) 
{
    renderer_ = renderer;

    //Create the initial state.
    MainState* mainState = new MainState(renderer);
    this->states_.push(mainState);
};

void Game::Update() {
    if(peekState() == nullptr) return;
    peekState()->Update();
}

void Game::Draw() {
    if(peekState() == nullptr) return;

    renderer_->StartDraw();
    peekState()->Draw();
    renderer_->Draw();
    
};

void Game::pushState(GameState* state)
{
    this->states_.push(state);
 
    return;
}
 
void Game::popState()
{
    delete this->states_.top();
    this->states_.pop();
 
    return;
}
 
void Game::changeState(GameState* state)
{
    if(!this->states_.empty())
        popState();
    pushState(state);
 
    return;
}
 
GameState* Game::peekState()
{
    if(this->states_.empty()) return nullptr;
    return this->states_.top();
}

void Game::PollEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT){
            Escape = true;
        }
        if (e.type == SDL_KEYDOWN){
            const Uint8 *state = SDL_GetKeyboardState(NULL); 
            
            if ( state[SDL_SCANCODE_ESCAPE] ) {
                Escape = true;
            }
        }

        //Forward the event to current state.
        if(peekState() == nullptr) continue;
        peekState()->HandleInput(e);
    }
}