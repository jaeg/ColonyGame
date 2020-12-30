#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
    public: 
    virtual ~GameState(){};
    virtual void Draw() = 0;
    virtual void Update() = 0;
    
    //SDL Input events get forward to this function as they happen.
    virtual void HandleInput(SDL_Event e) = 0;
};

#endif