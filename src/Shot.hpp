#include<iostream>
#include "rsdl.hpp"
#include "Timer.hpp"
#include "Towers.hpp"
#include "defines.hpp"

#ifndef __Shot_CC__
#define __Shot_CC__

class Shot
{
public:
	Shot(int _x , int _y , Window* _window , Tower* _tower , int _index_of_tower) : x(_x) , y(_y) , window(_window) , tower(_tower) , num_of_try(0) , first_x(_x) 
	, first_y(_y) , index_of_tower(_index_of_tower) , frame(0) {}

	int get_x() { return x; }
	int get_y() { return y; }
	void set_x(int _x) { x = _x; }
	void set_y(int _y) { y = _y; }
	void draw(int , int , std::string sprite_mode = "non_collision");
	std::string get_shot_type() { return tower -> get_type(); }
	int get_index_of_tower() { return index_of_tower; }

private:
	void draw_collision();
	void try_to_collide(int _x , int _y);
	int x;
	int y;
	int first_x;
	int first_y;
	Window* window;
	Tower* tower;
	int index_of_tower;
	int frame;
	Timer timer;
	Timer timer1;
	int num_of_try;
};

#endif