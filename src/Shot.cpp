#include "rsdl.hpp"
#include "Shot.hpp"
#include "Timer.hpp"
#include "Towers.hpp"
#include "defines.hpp"
#include <iostream>

using namespace std;

void Shot::draw(int _x , int _y , string sprite_type)
{
	if(!(x > first_x - (SIZE_OF_SQUARE / 2) && x < first_x + (SIZE_OF_SQUARE / 2) && y > first_y - (SIZE_OF_SQUARE / 2) && y < first_y + (SIZE_OF_SQUARE / 2)))
	{
		if(sprite_type == "non_collision")
			window -> draw_img(tower -> get_type() + PNG , Rectangle(x , y , 20 , 20));

		if(sprite_type == "collision")
		{
			draw_collision();
			return;
		}
	}

	try_to_collide(_x , _y);
}

void Shot::try_to_collide(int _x , int _y)
{
	if(!timer.is_started())
		timer.start();

	if(timer.get_ticks() > SHOT_DELAY)
	{
		x += (_x - x) / 2;
		y += (_y - y) / 2;
		if(num_of_try < MAX_TRY)
			num_of_try++;
		if(num_of_try == MAX_TRY)
		{
			x = _x;
			y = _y;
		}
		timer.start();
	}
}

void Shot::draw_collision()
{
	window -> draw_img(tower -> get_type() + to_string(frame) + PNG , Rectangle(x - 25 , y - 25 , 50 , 50));
	if(!timer1.is_started())
		timer1.start();

	if(timer1.get_ticks() > COLLISION_DELAY)
	{
		if(frame != MAX_COLLISION_FRAME)
			frame++;
		timer1.stop();
	}
}