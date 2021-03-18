#include<iostream>
#include<vector>
#include "stdin.hpp"
#include "rsdl.hpp"
#include "defines.hpp"
#include "FieldRunners.hpp"
#include "Player.hpp"
#include "Towers.hpp"
#include "Timer.hpp"

using namespace std;

int main(int argc , char* argv[])
{	
	vector<string> stdin =  get_std_input();

	Window* window = new Window(WIDTH , HEIGHT , GAME_TITLE);
	Player* player = new Player(FIRST_MONEY , FIRST_HEART , window);

	FieldRunners field_runners(window , player , stdin);
	field_runners.play();

	delete player;
	delete window;
}

