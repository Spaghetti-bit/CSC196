#include "Enemy.h"
#include "Math/Math.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include "../Game.h"
#include <fstream>

bool Enemy::Load(const std::string& filename)
{
    bool success = false;

    std::ifstream stream(filename);
    if (stream.is_open())
    {
        success = true;

        // load the base actor members
        Actor::Load(stream);

        // stream into thrust
        stream >> m_thrust;

        stream.close();
    }

    return success;

}

void Enemy::Update(float dt)
{
    nc::Vector2 e_direction = m_target->GetTransform().position - m_transform.position;
    nc::Vector2 e_velocity = e_direction.Normalized() * 0; // m_thrust;
    m_transform.position = m_transform.position + (e_velocity * dt);

    m_transform.angle = std::atan2(e_direction.y, e_direction.x) + nc::DegreesToRadians(90.0f);

    m_transform.Update();
}

void Enemy::OnCollision(Actor* actor)
{
    if (actor->GetType() == nc::Actor::eType::PROJECTILE)
    {
        m_destroy = true;

        //set game score
        m_scene->GetGame()->AddScore(100);

        nc::Color colors[] = { nc::Color::white, nc::Color::blue, nc::Color::yellow };

        nc::Color color = colors[rand() % 3]; // 0, 1, 2

        g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1.0f, 100, 200);


        //m_scene->RemoveActor(actor);
    }
}

void Enemy::Draw(Core::Graphics& graphics)
{
    m_shape.Draw(graphics, m_transform);
}
