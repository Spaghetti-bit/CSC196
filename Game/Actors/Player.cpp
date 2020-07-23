#include "Player.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include "../Game.h"
//#include "Graphics/ParticleSystem.cpp"
#include <fstream>

bool Player::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		// load the base actor members
		Actor::Load(stream);

		// stream into thrust

		/*std::string line;
		std::getline(stream, line);*/
		stream >> m_thrust;
		// stream into rotation rate
		stream >> m_rotation_rate;

		stream.close();
	}

	return success;

}

void Player::Update(float dt)
{
	m_fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0.0f;

		Projectile* projectile = new Projectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		//projectile->SetThrust(50);
		m_scene->AddActor(projectile);

	}

	//position
	nc::Vector2 force{ 0, 0 };
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);
	m_velocity += (force * dt);
	m_velocity *= 0.99f;


	//nc::Vector2 direction = force;
	m_transform.position = m_transform.position + (m_velocity * dt);


	// rotate

	//input for rotation
	if (Core::Input::IsPressed('A')) { m_transform.angle -= (dt * nc::DegreesToRadians(m_rotation_rate)); };
	if (Core::Input::IsPressed('D')) { m_transform.angle += (dt * nc::DegreesToRadians(m_rotation_rate)); };


	//Wrap - x
	if (m_transform.position.x > 800.0f) m_transform.position.x = 0.0f;
	if (m_transform.position.x < 0.0f) m_transform.position.x = 800.0f;
	//Wrap - y
	if (m_transform.position.y > 600.0f) m_transform.position.y = 0.0f;
	if (m_transform.position.y < 0.0f) m_transform.position.y = 600.0f;

	if (force.LengthSqr() > 0)
	{
		g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::yellow, 1.0f, 100, 200);
	
	}

	m_transform.Update();
}

void Player::Draw(Core::Graphics& graphics)
{
	m_shape.Draw(graphics, m_transform);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetType() == nc::Actor::eType::ENEMY)
	{
		m_scene->GetGame()->SetState(Game::eState::GAME_OVER);

		//m_scene->RemoveActor(actor);
	}
}


