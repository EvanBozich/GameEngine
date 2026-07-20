// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>

using namespace nu;


int main()
{
    //Initialize
    FMOD::System* audio;
    FMOD::System_Create(&audio);
    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
   
    nu::engine.Initialize();
    //Mesh mesh{ { {20, 2}, {19, 3 }, {0,0} }, {0.8f, 0.8f, 0.8f} };
    Mesh mesh1{ { Vector2{0,-3}, Vector2{5,0}, Vector2{0,3}, Vector2{-3,0 }, Vector2{0,-3} }, Color{1.0f, 1.0f, 1.0f} };
    Model model = std::vector<Mesh>{ mesh1 };

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = model;
    playerDesc.transform = nu::Transform{ nu::Vector2{640.0f, 512.0f}, 0.0f, 15.0f };
    playerDesc.speed = 400.0f;
    Player* player = new Player{ playerDesc };

    scene.AddActor(player);

    for (int i = 0; i < 20; i++)
    {
        Enemy* enemy = new Enemy{ 400.0f, nu::Transform{ nu::Vector2{nu::Randomfloat(), nu::Randomfloat()}, 90.0f, 10.0f}, Model{{mesh1}}};
        scene.AddActor(enemy);
    }
  
 
    SDL_Event e;
    bool quit = false;

    std::vector<FMOD::Sound*> sounds;
    FMOD::Sound* sound = nullptr;

    audio->createSound("whistle.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("oof.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("error.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("hee-hee.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("scream.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    audio->createSound("alert.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);


    audio->playSound(sounds[5], nullptr, false, nullptr);
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


        if (nu::engine.GetInput().GetKeyPressed(SDL_SCANCODE_G))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (nu::engine.GetInput().GetKeyPressed(SDL_SCANCODE_F))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }
        if (nu::engine.GetInput().GetKeyPressed(SDL_SCANCODE_R))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }
        if (nu::engine.GetInput().GetKeyPressed(SDL_SCANCODE_E))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }
        if (nu::engine.GetInput().GetKeyPressed(SDL_SCANCODE_T))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }

        audio->update();
        nu::engine.Update();
        float dt = engine.GetTime().GetDeltaTime();

        //player.SetRoation(player.GetTransform().rotation + (90.0f * nu::engine.GetTime().GetDeltaTime()));
        //player.Update(nu::engine.GetTime().GetDeltaTime());
        //enemy.Update(dt);

        scene.Update(dt);

     
        
      
        nu::engine.GetRenderer().SetColorInt(0, 0, 0);
        nu::engine.GetRenderer().Clear();


        //player.Draw(nu::engine.GetRenderer());
        //enemy.Draw(nu::engine.GetRenderer());

        scene.Draw(nu::engine.GetRenderer());

        nu::engine.GetRenderer().Present();
    }

    //shutdown

    return 0;
}


