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
    float speed = 400.0f;

    nu::Input input;
    input.Initialize();
    //I did it bro
   // fnEngine();
    nu::Time time = nu::Time();
    nu::Vector2 position{ 640.0f, 512.0f };
    std::vector<nu::Vector2> points;
 
    

    //for (int i = 0; i < 300; i++) {
    //   nu::Vector2 vec{ nu::Randomfloat(width), nu::Randomfloat(height) };
    //   points.push_back(vec);
    //}
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
        time.Tick();
        

        


        //if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        //if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "down\n";
        //if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "released\n";
        //if (input.GetButtonPressed(nu::Input::MouseButton::LEFT)) std::cout << "button pressed\n";
        //if (input.GetButtonDown(nu::Input::MouseButton::LEFT)) std::cout << "button down\n";
        //if (input.GetButtonReleased(nu::Input::MouseButton::LEFT)) std::cout << "button released\n";
     
        if (input.GetButtonPressed(nu::Input::MouseButton::LEFT))
        {
            points.push_back(input.GetMousePosition());
        }

        nu::Vector2 velocity{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) velocity.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) velocity.x = speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) velocity.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) velocity.y = speed;
        position += (velocity * time.GetDeltaTime());


        renderer.SetColorInt(0,0,0);
        renderer.Clear();

        for (int i = 0; i < points.size(); i++) {
            renderer.SetColorFloat(nu::Randomfloat(), nu::Randomfloat(), nu::Randomfloat());
            renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        renderer.SetColorFloat(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(position.x - 20, position.y - 20, 20, 20);

        renderer.Present();
    }

    //shutdown
    renderer.Shutdown();

    return 0;
}


