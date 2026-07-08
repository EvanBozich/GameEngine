// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Engine.h"




int main()
{
    //Initialize
    static int width = 1280;
    static int height = 1024;
    nu::Renderer renderer;
    renderer.Initialize("Game engine", width, height);

    nu::Input input;
    input.Initialize();
    //I did it bro
   // fnEngine();

    nu::Vector2 vel{ 0.5f, 0.0f };
    std::vector<nu::Vector2> v;
    

    

    for (int i = 0; i < 300; i++) {
       nu::Vector2 vec{ nu::Randomfloat(width), nu::Randomfloat(height) };
       v.push_back(vec);
    }
    SDL_Event e;
    bool quit = false;

    // Define a rectangle
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

        input.Update();
        //std::cout << numKeys << std::endl;
       // if (keystate[SDL_SCANCODE_SPACE]) std::cout << "press\n";

        //nu::Vector2 mousePosition;
        //SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
        if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "down\n";
        if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "released\n";
        if (input.GetButtonPressed(nu::Input::MouseButton::LEFT)) std::cout << "button pressed\n";
        if (input.GetButtonDown(nu::Input::MouseButton::LEFT)) std::cout << "button down\n";
        if (input.GetButtonReleased(nu::Input::MouseButton::LEFT)) std::cout << "button released\n";
     


        //render
        renderer.SetColorInt(0,0,0);
        renderer.Clear();// Set render draw color to black

        for (int i = 0; i < v.size(); i++) {
            renderer.SetColorFloat(nu::Randomfloat(), nu::Randomfloat(), nu::Randomfloat());

            v[i] = v[i] + vel;
            renderer.DrawPoint(v[i].x, v[i].y);
        }

        for (int i = 0; i < 25; i++) {
            renderer.SetColorInt(nu::RandomInt(256), nu::RandomInt(256), nu::RandomInt(256)); // Set render draw color to green
            renderer.DrawFillRect(rand() % width, rand() % height, 20, 30);
        }

        for (int i = 0; i < 10; i++) {
            renderer.SetColorInt(nu::RandomInt(256), nu::RandomInt(256), nu::RandomInt(256));
            renderer.DrawLine(rand() % width, rand() % height, rand() % width, rand() % height);
        }

        renderer.SetColorFloat(nu::Randomfloat(), nu::Randomfloat(), nu::Randomfloat());
        renderer.DrawFillRect(input.GetMousePosition().x - 20, input.GetMousePosition().y - 20, 40, 40);

        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set render draw color to green
        //SDL_RenderDebugText(renderer, 10, 10, "Hello world!");
         // Render the screen
        renderer.Present();
    }

    //shutdown
    renderer.Shutdown();

    return 0;
}


