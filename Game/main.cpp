// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "core.h"
#include "Game.h"
//#include "Game.cpp"


Game game;

bool Update(float dt) // delta time (60fps) | 1/60 (0.016) | 0.016 * 60 (1)
{


	//update game
	bool quit = game.Update(dt);
	
	return quit;
}


void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);

}

int main()
{
	game.Startup();
	



	char name[] = "CSC196";
	Core::Init(name, 800, 600, 90);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
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
