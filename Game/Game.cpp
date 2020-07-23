#include "Game.h"
#include "Math\Math.h"
#include "Math\Random.h"
//#include "Math\Vector2.h"
// Vector2 is included with Transform
#include "Math\Color.h"
#include "Math\Vector2.cpp"
#include "Graphics\Shape.h"
#include "Graphics\Shape.cpp"
#include "Math\Transform.h"
#include "Math\Transform.cpp"
#include "Object/Actor.h"
#include "Object/Actor.cpp"
#include "Actors/Enemy.h"
#include "Actors/Player.h"

#include "Graphics/ParticleSystem.h"
#include "Graphics/ParticleSystem.cpp"

#include "Object/Scene.cpp"

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <vector>

void Game::Startup()
{
	g_particleSystem.Startup();
	m_scene.StartUp();
	m_scene.SetGame(this);
	
	
	
}

void Game::Shutdown()
{
	m_scene.Shutdown();
	g_particleSystem.Shutdown();
}

bool Game::Update(float dt)
{

	m_frametime = dt;
	m_roundTime += dt; // adds dt each frame

	g_particleSystem.Update(dt);



	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE)) m_state = eState::START_GAME;
		break;
	case Game::eState::START_GAME:
	{
		Player* player = new Player;

		player->Load("player.txt");
		m_scene.AddActor(player);

		for (size_t i = 0; i < 10; i++)
		{
			nc::Actor* enemy = new Enemy;



			enemy->Load("enemy.txt");
			dynamic_cast<Enemy*>(enemy)->SetTarget(player);


			enemy->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };


			dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 100));

			m_scene.AddActor(enemy);

		}

		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
		m_scene.Update(dt);

		m_spawnTimer += dt;
		if (m_spawnTimer >= 3.0f)
		{
			m_spawnTimer = 0.0f;
			Enemy* enemy = new Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<Player>());
			enemy->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
			enemy->SetThrust(nc::random(50, 100));
			m_scene.AddActor(enemy);
		}
		break;
	case Game::eState::GAME_OVER:

		break;
	default:
		break;
	}


	if (m_roundTime >= m_roundLimit) m_gameOver = true; // 5 second rounds by default, check roundLimit


	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	
	



	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::white, nc::Color::blue, nc::Color::yellow };

		nc::Color color = colors[rand() % 3]; // 0, 1, 2

		g_particleSystem.Create({ x,y }, 0, 180, 30, color, 1.0f, 100, 200);

	}


	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{



	graphics.SetColor(nc::Color{ 0,1,0 });

	graphics.DrawString(10, 10, std::to_string(m_frametime).c_str()); // 1 / dt ( 60 fps -> 0.016 )
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frametime).c_str()); // fps ( ex. 60 fps )


	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "Vector 2 - The Update Function");
		break;
	case Game::eState::START_GAME:

		break;
	case Game::eState::GAME:
		m_scene.Draw(graphics);
		g_particleSystem.Draw(graphics);


		graphics.SetColor(nc::Color::white);
		graphics.DrawString(700, 10, std::to_string(m_score).c_str());
		break;
	case Game::eState::GAME_OVER:
		graphics.SetColor(nc::Color::red);
		graphics.DrawString(400, 300, "Game Over!");

		break;
	default:
		break;
	}
}
