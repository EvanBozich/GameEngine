// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Engine.h"

struct Transform
{
    nu::Vector2 position;
    float rotation;
    float scale;
};

class Actor
{
public:
    Actor() = default;
    Actor(const Transform& transform) : m_transform{ transform } {}

    void Update(float dt) 
    {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.997f;

        m_transform.position.x = nu::math::Wrap((float)0, 1280.0f, m_transform.position.x);
        m_transform.position.y = nu::math::Wrap(float(0), 1024.0f, m_transform.position.y);
    }

    void Draw(const nu::Renderer& renderer) const
    {
        renderer.SetColorFloat(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }

    const Transform& GetTransform() const { return m_transform;}
    void SetPosition(const nu::Vector2& position) { m_transform.position = position; }
    void SetRoation(float rotation) { m_transform.rotation = rotation; }
    void SetScale(float scale) { m_transform.scale = scale; }

    nu::Vector2 GetVelocity() { return m_velocity; }
    void SetVelocity(const nu::Vector2& velocity) { m_velocity = velocity; }
protected:
    Transform m_transform;
    nu::Vector2 m_velocity{ 0,0 };
};

int main()
{
    //Initialize
    static float width = 1280.0f;
    static float height = 1024.0f;
    nu::Renderer renderer;
    renderer.Initialize("Game engine", width, height);
    float speed = 400.0f;

    nu::Input input;
    input.Initialize();
    //I did it bro
   // fnEngine();
    nu::Time time;
    Actor player{ Transform{ nu::Vector2{640.0f, 512.0f}, 0.0f, 50.0f } };


    nu::Vector2 position{ 640.0f, 512.0f };
    nu::Vector2 velocity{ 0.0f, 0.0f };
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
     
        //if (input.GetButtonPressed(nu::Input::MouseButton::LEFT))
        //{
        //    points.push_back(input.GetMousePosition());
        //}
        if (input.GetButtonDown(nu::Input::MouseButton::LEFT))
        {
            if (points.empty())
            {
                points.push_back(input.GetMousePosition());
            }
            else {

                nu::Vector2 v = points.back() - input.GetMousePosition();

                if (v.Length() > 30.0f)
                {
                    points.push_back(input.GetMousePosition());
                }
            }
        }

        if (input.GetButtonPressed(nu::Input::MouseButton::RIGHT))
        {
            if (!points.empty()) points.pop_back();
        }
        
        nu::Vector2 force{ 0.0f, 0.0f };
        
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        //velocity += (force * time.GetDeltaTime());
        //position += (velocity * time.GetDeltaTime());

        //position.x = nu::math::Wrap((float)0, width, position.x);
        //position.y = nu::math::Wrap(float(0), height, position.y);

        renderer.SetColorInt(0,0,0);
        renderer.Clear();

        for (int i = 0; i < points.size(); i++) 
        {
            renderer.SetColorFloat(nu::Randomfloat(), nu::Randomfloat(), nu::Randomfloat());
            renderer.DrawLine(points[i].x, points[i].y, (points[i + 1].x - 1),(points[i + 1].y - 1));
        }

        player.Draw(renderer);

        //renderer.SetColorFloat(1.0f, 1.0f, 1.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 20, 20);

        renderer.Present();
    }

    //shutdown
    renderer.Shutdown();

    return 0;
}


