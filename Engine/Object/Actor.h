#pragma once
#include "Math/Transform.h"
#include "..\Graphics\Shape.h"


namespace nc
{
	class Scene;

	class Actor
	{
	public:
		enum class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE
		};

	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {} // make sure to initialize m_transform and m_shape
		~Actor() {}

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);
		
		virtual eType GetType() = 0;

		virtual void Update(float dt);

		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

		float GetRadius();

		void SetScene(Scene* scene) { m_scene = scene; }; // Set the scene for the actor
		Shape& GetShape() { return m_shape; }; // return the shape
		Transform& GetTransform() { return m_transform; }; // return the transform

		void SetDestroy(bool destroy = true) { m_destroy = destroy; }
		bool IsDestroy() { return m_destroy; }



	protected:
		bool m_destroy{ false };
		Scene* m_scene{ nullptr };
		Shape m_shape;
		Transform m_transform;
	};
}
