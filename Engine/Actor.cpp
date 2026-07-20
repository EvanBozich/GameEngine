#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtil.h"

namespace nu {

    void Actor::Update(float dt)
    {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.997f;

        m_transform.position.x = nu::math::Wrap((float)0, 1280.0f, m_transform.position.x);
        m_transform.position.y = nu::math::Wrap(float(0), 1024.0f, m_transform.position.y);
    }

    void Actor::Draw(const Renderer& renderer) const
    {
        renderer.DrawModel(m_model, m_transform);

    }
}