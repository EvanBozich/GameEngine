// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Engine.h"
#include "Player.h"

using namespace nu;


int main()
{
    //Initialize
   
  
    engine.Initialize();
    //I did it bro
   // fnEngine();
    nu::Mesh mesh{ { {-2, 2}, {2, 3 }, {0,0} }, {1.0f, 1.0f, 1.0f} };
    Player player{2000.0f, nu::Transform{ nu::Vector2{640.0f, 512.0f}, 0.0f, 50.0f }, std::vector<nu::Mesh>{ mesh } };

    //draw
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



        engine.Update();
        player.SetRoation(player.GetTransform().rotation + (90.0f * engine.GetTime().GetDeltaTime()));
        player.Update(engine.GetTime().GetDeltaTime());

        


        //if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        //if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "down\n";
        //if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "released\n";
        //if (input.GetButtonPressed(nu::Input::MouseButton::LEFT)) std::cout << "button pressed\n";
        //if (input.GetButtonDown(nu::Input::MouseButton::LEFT)) std::cout << "button down\n";
        //if (input.GetButtonReleased(nu::Input::MouseButton::LEFT)) std::cout << "button released\n";
     
        //if (input.GetButtonPressed(nu::Input::MouseButton::LEFT))
        //{
        //    points.push_back(input.GetMousePosition());
        //}
        if (engine.GetInput().GetButtonDown(nu::Input::MouseButton::LEFT))
        {
            if (points.empty())
            {
                points.push_back(engine.GetInput().GetMousePosition());
            }
            else {

                nu::Vector2 v = points.back() - engine.GetInput().GetMousePosition();

                if (v.Length() > 10.0f)
                {
                    points.push_back(engine.GetInput().GetMousePosition());
                }
            }
        }

        if (engine.GetInput().GetButtonPressed(nu::Input::MouseButton::RIGHT))
        {
            if (!points.empty()) points.pop_back();
        }
        
       

        //velocity += (force * time.GetDeltaTime());
        //position += (velocity * time.GetDeltaTime());

        //position.x = nu::math::Wrap((float)0, width, position.x);
        //position.y = nu::math::Wrap(float(0), height, position.y);

        engine.GetRenderer().SetColorInt(0, 0, 0);
        engine.GetRenderer().Clear();

        //for (int i = 0; i < (int)points.size() -1 ; i++) 
        //{
        //    renderer.SetColorFloat(nu::Randomfloat(), nu::Randomfloat(), nu::Randomfloat());
        //    renderer.DrawLine(points[i].x, points[i].y, (points[i + 1].x - 1),(points[i + 1].y - 1));
        //}

        player.Draw(engine.GetRenderer());

        //renderer.SetColorFloat(1.0f, 1.0f, 1.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 20, 20);

        engine.GetRenderer().Present();
    }

    //shutdown

    return 0;
}


