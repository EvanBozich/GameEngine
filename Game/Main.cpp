// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>
#include "Audio.h"
#include "Assets.h"
#include "SpaceGame.h"
using namespace nu;


int main()
{
    SetWorkingDirectory("assets");
    //Initialize
   
    Engine::Get().Initialize();
 

    //Mesh mesh{ { {20, 2}, {19, 3 }, {0,0} }, {0.8f, 0.8f, 0.8f} };
    Mesh mesh1{ { Vector2{6,0}, Vector2{-3,-5}, Vector2{0,3}, Vector2{-3,0 }, Vector2{0,-3} }, Color{1.0f, 1.0f, 1.0f} };

    SpaceGame game;
    game.Initialize();
  
 
    SDL_Event e;
    bool quit = false;


    //main loop
    while (!quit) 
    {

        //update
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            Engine::Get().GetAudio().PlaySound("alert");
        }


        nu::Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();

      
        nu::Engine::Get().GetRenderer().SetColorInt(0, 0, 0);
        nu::Engine::Get().GetRenderer().Clear();
        
        game.Update(dt);

        game.Draw(nu::Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());


        nu::Engine::Get().GetRenderer().Present();
    }

    //shutdown
    Engine::Get().Shutdown();

    return 0;
}


