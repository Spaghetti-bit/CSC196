#pragma once
#include "Object/Actor.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Math/Math.h"


class Player : public nc::Actor
{
public:
	Player() = default;
	
	virtual eType GetType() { return nc::Actor::eType::PLAYER; }


	virtual bool Load(const std::string& filename) override;

	virtual void Update(float dt) override;

	virtual void Draw(Core::Graphics& graphics) override;

	virtual void OnCollision(Actor* actor);


protected:
	nc::Vector2 m_velocity;
	float m_thrust{ 0.0f };
	float m_rotation_rate{ 360.0f };
	float m_fireRate{ 0.5f };
	float m_fireTimer{ 0.0f };
};