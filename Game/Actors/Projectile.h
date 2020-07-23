#pragma once
#include "Object/Actor.h"

class Projectile : public nc::Actor
{
	public:

		virtual eType GetType() { return nc::Actor::eType::PROJECTILE; }


		virtual bool Load(const std::string& filename) override;

		virtual void Update(float dt) override;

		virtual void Draw(Core::Graphics& graphics) override;

		void SetThrust(float thrust) { m_thrust = thrust; }

		virtual void OnCollision(Actor* actor);


		
protected:
	float m_thrust{ 0.0f };
	float m_lifetime{ 3 };
};
