// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>
#include "Assets.h"
using namespace nu;


int main()
{
    //Initialize
    FMOD::System* audio;
    FMOD::System_Create(&audio);
    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
   
    Engine::Get().Initialize();
    //Mesh mesh{ { {20, 2}, {19, 3 }, {0,0} }, {0.8f, 0.8f, 0.8f} };
    Mesh mesh1{ { Vector2{6,0}, Vector2{-3,-5}, Vector2{0,3}, Vector2{-3,0 }, Vector2{0,-3} }, Color{1.0f, 1.0f, 1.0f} };
    Mesh mesh2{ { Vector2{6,0}, Vector2{-3,-5}, Vector2{-2,0}, Vector2{6,0}, Vector2{-3,5}, Vector2{-2,0} }, Color{0.5f, 0.52f, 1.58f} };
    //Mesh mesh3{ { Vector2{5,0}, Vector2{0,3} }, Color{0.5f, 0.52f, 1.58f} };
    Mesh mesh4{ { Vector2{-2,0}, Vector2{-5,-2}, Vector2{-4,0}, Vector2{-5,2}, Vector2{-2,0} }, Color{2.07f, 0.05f, 0.02f} };
    //Mesh mesh5{ { Vector2{-3,0}, Vector2{0,-3} }, Color{2.07f, 0.05f, 0.02f} };
    Model model = std::vector<Mesh>{ mesh2, mesh4,};
    Scene scene;

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

    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt", "Hello, World!", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }
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


        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_G))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_F))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_R))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_E))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_T))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }

        audio->update();
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

        nu::Engine::Get().GetRenderer().Present();
    }

    //shutdown

    return 0;
}


