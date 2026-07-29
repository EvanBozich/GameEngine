#include "Player.h"
#include "Bullet.h"
#include "Assets.h"
#include "Renderer.h"
#include "Engine.h"
#include "Random.h"


void Player::Update(float dt)
{
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    //SetVelocity(GetVelocity() + (force * dt));
    float roatate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) roatate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) roatate = +180.0f;

    SetRoation(m_transform.rotation + roatate * dt);

    nu::Vector2 forward{ 1, 0 }; //->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    nu::Particle particle;
    particle.position = m_transform.position;
    particle.color = { 1.0f, 1.0f, 1.0f };
    particle.lifespan = nu::Randomfloat(0.5f, 1.5f);
    particle.velocity = { nu::Randomfloat(-200.0f, 200.0f), nu::Randomfloat(-200.0f, 200.0f) };

    nu::Engine::Get().GetPS().AddParticle(particle);


    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
    {
        BulletDesc desc;
        desc.name = "Bullet";
        desc.tag = "Bullet";
        desc.model = Assets::bulletModel;
        desc.transform = m_transform;
        desc.speed = 800.0f;
        desc.damping = 1.0f;
        desc.lifespan = 2.0f;

        Bullet* bullet = new Bullet{ desc };
        m_scene->AddActor(bullet);
    }


    Actor::Update(dt);
}

void Player::Draw(const nu::Renderer& renderer) const
{
	Actor::Draw(renderer);
}

void Player::OnCollision(Actor* other)
{

}

