// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "core.h"
#include "Math\Math.h"
#include "Math\Random.h"
//#include "Math\Vector2.h"
// Vector2 is included with Transform
#include "Math\Color.h"
#include <iostream>
#include <vector>
#include <string>
#include "Math\Vector2.cpp"
#include "Graphics\Shape.h"
#include "Graphics\Shape.cpp"
#include "Math\Transform.h"
#include "Math\Transform.cpp"
#include "Object/Actor.h"
#include "Object/Actor.cpp"


float speed = 300.0f;
const size_t NUM_POINTS = 40;


std::vector<nc::Vector2> d_ship = { { 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 } };
std::vector<nc::Vector2> d_box = { { 3, 3 }, { 3, -3 }, { -3, -3 }, { -3, 3 }, { 3, 3 } };
std::vector<nc::Vector2> d_trapezoid = { { 6, 3 }, { 3, -3 }, { -3, -3 }, { -6, 3 }, { 6, 3 } };

nc::Color color{ 0, 1, 1 };

nc::Actor player;
nc::Actor enemy;

//nc::Shape ship{ d_trapezoid, color };
nc::Shape ship;


nc::Transform transform{ { 400, 300}, 4, 0 };

//nc::Vector2 position{ 400.0f, 300.0f };
//float scale = 4.0f;
//float angle = 0.0f;


float frametime;
float roundTime{ 0 };
bool gameOver{ false };
float roundLimit{ 5.0f };


DWORD prevTime;
DWORD deltaTime;



bool Update(float dt) // delta time (60fps) | 1/60 (0.016) | 0.016 * 60 (1)
{
	// Time
	DWORD time = GetTickCount(); // Ticks = Computer runtime

	deltaTime = time - prevTime; // current frame time - previous frame time

	prevTime = time;
	// End of Time


	frametime = dt;
	roundTime += dt; // adds dt each frame



	if (roundTime >= roundLimit) gameOver = true; // 5 second rounds by default, check roundLimit


	if (gameOver)
	{
		dt = 0.0f;  // Stops all movement.
	}



	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

		

	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2{0, -1} *speed; }
	nc::Vector2 direction = force * dt;
	direction = nc::Vector2::Rotate(direction, player.GetTransform().angle);
	player.GetTransform().position = direction + player.GetTransform().position;


	// rotate
	if (Core::Input::IsPressed('A')) { player.GetTransform().angle -= (dt * 3.0f); };
	if (Core::Input::IsPressed('D')) { player.GetTransform().angle += (dt * 3.0f); };
	
	
	return quit;
}


void Draw(Core::Graphics& graphics)
{

	graphics.DrawString(10, 10, std::to_string(frametime).c_str()); // 1 / dt ( 60 fps -> 0.016 )
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str()); // fps ( ex. 60 fps )
	//rgb (0-1.0) float

	// Time
	graphics.DrawString(10, 30, std::to_string( deltaTime / 1000.0f ).c_str()); // Run time

	if (gameOver)
	{
		graphics.DrawString( 400, 300, "Game Over" );
	}
	//graphics.SetColor(color.Pack888());
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
	graphics.SetColor(color);
	//ship.SetColor(color);
	
	player.Draw(graphics);
	enemy.Draw(graphics);

}

int main()
{

	

	/*nc::Vector2 point;
	point.x = 4;
	point.y = 5;

	float x = nc::PI * 4;*/

	//for (size_t i = 0; i < NUM_POINTS; i++)
	//{
	//	points.push_back(nc::Vector2{ nc::random(0.0f,800.0f),nc::random(0.0f,600.0f) });
	//	//points.push_back({ nc::random(0.0f,800.0f),nc::random(0.0f,600.0f) });
	//}

	DWORD ticks = GetTickCount(); // how many ticks in a second
	std::cout << ticks /1000 / 60/60<< std::endl;

	prevTime = GetTickCount();

	
	//ship.Load("ship.txt");
	//ship.SetColor(color);

	player.Load("player.txt");
	enemy.Load("enemy.txt");

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
