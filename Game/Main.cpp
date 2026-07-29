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
    Engine::Get().GetAudio().AddSound("alert", "alert.mp3");

    //Mesh mesh{ { {20, 2}, {19, 3 }, {0,0} }, {0.8f, 0.8f, 0.8f} };
    Mesh mesh1{ { Vector2{6,0}, Vector2{-3,-5}, Vector2{0,3}, Vector2{-3,0 }, Vector2{0,-3} }, Color{1.0f, 1.0f, 1.0f} };
    Scene scene;

    SpaceGame game;
    game.Initialize();

    Font* font = new Font();
    font->Load("Fonts/ArcadeClassic.ttf", 20);

    Text* text = new Text(font);
    text->Create(Engine::Get().GetRenderer(), "Hello World", Color { 1.0f, 1.0f, 1.0f });

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = Assets::playerModel;
    playerDesc.transform = nu::Transform{ nu::Vector2{640.0f, 512.0f}, 0.0f, 15.0f };
    playerDesc.speed = 800.0f;
    playerDesc.damping = 1.0f;
    Player* player = new Player{ playerDesc };

    scene.AddActor(player);

    for (int i = 0; i < 20; i++)
    {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        Enemy* enemy = new Enemy{ 400.0f, nu::Transform{ nu::Vector2{nu::Randomfloat(1280), nu::Randomfloat(1024)}, 90.0f, 10.0f}, Model{{mesh1}}};
        scene.AddActor(enemy);
    }
  
 
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

        //player.SetRoation(player.GetTransform().rotation + (90.0f * nu::Engine::Get().GetTime().GetDeltaTime()));
        //player.Update(nu::Engine::Get().GetTime().GetDeltaTime());
        //enemy.Update(dt);

        scene.Update(dt);

     
        
      
        nu::Engine::Get().GetRenderer().SetColorInt(0, 0, 0);
        nu::Engine::Get().GetRenderer().Clear();
        


        //player.Draw(nu::Engine::Get().GetRenderer());
        //enemy.Draw(nu::Engine::Get().GetRenderer());

        scene.Draw(nu::Engine::Get().GetRenderer());
        text->Draw(Engine::Get().GetRenderer(), 40.0f, 40.0f);

        nu::Engine::Get().GetRenderer().Present();
    }

    //shutdown
    Engine::Get().Shutdown();

    return 0;
}


