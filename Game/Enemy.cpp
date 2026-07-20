#include "Enemy.h"
#include "Renderer.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
    float thrust = 0.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    //SetVelocity(GetVelocity() + (force * dt));
    float roatate = 0.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) roatate = -180.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) roatate = +180.0f;

    SetRoation(m_transform.rotation + roatate * dt);

    nu::Vector2 forward{ 1, 0 }; //->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DegToRad) * thrust;
    AddVelocity(velocity * dt);


    Actor::Update(dt);
}

void Enemy::Draw(const nu::Renderer& renderer) const
{
    Actor::Draw(renderer);
}
