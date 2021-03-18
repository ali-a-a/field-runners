#include<iostream>
#include "rsdl.hpp"

#ifndef __Player_CC__
#define __Player_CC__

class Player
{	
public:
	Player(double _money , double _heart , Window* _window);
	void show_money_heart();
	int get_money() { return money; }
	bool is_lose() { return heart <= 0; }
	void reduce_money(int _money) { money -= _money; }
	void inc_money(int _money) { money += _money; }
	void new_heart(int _heart) { heart -= _heart; }

private:
	int money;
	int heart;
	Window* window;
};

#endif