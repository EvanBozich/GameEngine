// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Engine.h"
#include "SDL3/SDL.h"


int main()
{
    static int width = 1024;
    static int height = 1024;
    nu::Renderer renderer;
    renderer.Initialize("Game engine", width, height);
    //I did it bro
   // fnEngine();

    SDL_Event e;
    bool quit = false;

    // Define a rectangle

    while (!quit) 
    {
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        renderer.SetColor(0, 0, 0);
        renderer.Clear();// Set render draw color to black

        for (int i = 0; i < 1000; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawPoint(rand() % width, rand() % height);
        }

        for (int i = 0; i < 25; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256); // Set render draw color to green
            renderer.DrawFillRect(rand() % width, rand() % height, 20, 30);
        }

        for (int i = 0; i < 10; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawLine(rand() % width, rand() % height, rand() % width, rand() % height);
        }

        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set render draw color to green
        //SDL_RenderDebugText(renderer, 10, 10, "Hello world!");
         // Render the screen
        renderer.Present();
    }

    
    renderer.Shutdown();

    return 0;
}


