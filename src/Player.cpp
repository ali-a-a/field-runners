#include "rsdl.hpp"
#include "Player.hpp"
#include "defines.hpp"
#include<iostream>

using namespace std;

Player::Player(double _money , double _heart , Window* _window)
{
	money = _money;
	heart = _heart;
	window = _window;
}

void Player::show_money_heart()
{
	window -> draw_img(HEART_PATH , Rectangle(HEART_X , HEART_Y , 70 , 70));
	window -> show_text(to_string(heart) , Point(HEART_X + 75 , HEART_Y + 8) , RED , TTF_MONEY_PATH , 40);
	window -> draw_img(MONEY_PATH , Rectangle(MONEY_X , MONEY_Y , 70 , 70));
	window -> show_text(to_string(money) , Point(MONEY_X + 70 , MONEY_Y +8) , GREEN , TTF_MONEY_PATH , 40);
}

