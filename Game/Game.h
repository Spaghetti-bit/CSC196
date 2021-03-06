#pragma once
#include "core.h"
#include "Object/Scene.h"



class Game
{
public:
	enum class eState
	{
		INIT,
		TITLE,
		START_GAME,
		GAME,
		GAME_OVER
	};
public:
	void Startup();
	void Shutdown();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

	void AddScore(int score) { m_score += score; }
	void SetState(eState state) { m_state = state; }

protected:
	eState m_state{ eState::TITLE };

	int m_lives{ 3 };
	int m_score{ 0 };

	nc::Scene m_scene;

	float m_frametime;
	float m_spawnTimer{ 0.0f };


	float m_roundTime{ 0.0f };
	bool m_gameOver{ false };
	float m_roundLimit{ 5.0f };

};

