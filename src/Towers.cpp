#include "Towers.hpp"
#include "rsdl.hpp"
#include "defines.hpp"
#include "Timer.hpp"
#include<iostream>
#include<vector>

using namespace std;

Tower::Tower(int _x , int _y , vector<string> _pic_path , Window* _window)
{
	x = _x;
	y = _y;
	window = _window;
	pic_path = _pic_path;
	level = 0;
}

Gatling::Gatling(int _x , int _y , vector<string> _pic_path , Window* _window)
	: Tower(_x , _y , _pic_path , _window)
{
	width = 105;
	height = 120;
	pic_x = x - width / 2 + 15;
	pic_y = y - height / 2;
	make_damage = 35;
	delay = 1000;
	cost = 55;
	update_cost = 40;
	delta_damage = 35;
	clips = init_clips();
}

Missile::Missile(int _x , int _y , vector<string> _pic_path , Window* _window)
	: Tower(_x , _y , _pic_path , _window)
{
	width = 92;
	height = 94;
	pic_x = x - width / 2 + 15;
	pic_y = y - height / 2;
	make_damage = 75;
	delay = 3000;
	cost = 70;
	update_cost = 60;
	delta_damage = 75;
	clips = init_clips();

}

Tesla::Tesla(int _x , int _y , vector<string> _pic_path , Window* _window)
	: Tower(_x , _y , _pic_path , _window)
{
	width = 80;
	height = 121;
	pic_x = x - width / 2;
	pic_y = y - height / 2;
	make_damage = 700;
	delay = 1500;
	cost = 120;
	update_cost = 100;
	delta_damage = 1000;
	clips = init_clips();

}

Glue::Glue(int _x , int _y , vector<string> _pic_path , Window* _window)
	: Tower(_x , _y , _pic_path , _window)
{
	width = 100;
	height = 130;
	pic_x = x - width / 2;
	pic_y = y - height / 2;
	make_damage = 40;
	delay = 2000;
	glue_influence_time = 2500;
	cost = 60;
	update_cost = 45;
	delta_damage = 10;
	delta_glue_influence_time = 500;
	clips = init_clips();
}

void Tower::draw(string mode , double angle , int index_of_attack)
{
	int index_of_mode = generate_index_of_mode(mode);

	if(index_of_mode < ENEMY_IN)
		window -> draw_img(pic_path[0] , Rectangle(pic_x , pic_y , width , height) , clips[level][index_of_mode]);

	if(index_of_mode >= ENEMY_IN)
		draw_enemy_in(angle , index_of_attack);

}

int Tower::generate_index_of_mode(string mode)
{
	if(mode == "new_tower")
		return NEW_TOWER;

	if(mode == "mouse_in")
		return MOUSE_IN;

	if(mode == "enemy_in")
		return ENEMY_IN;

	else
		return -1;
}

bool Tower::is_mouse_in_tower(Point mouse_point)
{
	if(mouse_point.x > x - SIZE_OF_SQUARE / 2 && mouse_point.x < x + SIZE_OF_SQUARE / 2 && mouse_point.y > y - SIZE_OF_SQUARE / 2 && mouse_point.y < y + SIZE_OF_SQUARE / 2)
		return true;

	return false;
}

void Tower::level_up()
{
	if(level < MAX_LEVEL) 
	{
		make_damage += delta_damage;
		level++;
	}
}

void Glue::level_up()
{
	if(level < MAX_LEVEL)
	{
		make_damage += delta_damage;
		glue_influence_time += delta_glue_influence_time;
		level++;
	}
}

bool Tower::is_shot()
{
	if(!timer.is_started())
		timer.start();

	if(timer.get_ticks() > delay)
	{
		timer.stop();
		return true;
	}

	return false;
}

void Gatling::draw_enemy_in(double angle , int index_of_attack)
{
	if(index_of_attack == 2 && level == 0)
		window -> draw_img(pic_path[0] , Rectangle(pic_x , pic_y , width , height) , clips[level][index_of_attack] , angle);

	if(index_of_attack == 2 && level > 0)
		window -> draw_img(pic_path[1] , Rectangle(pic_x , pic_y , width , height) , clips[level][index_of_attack] , angle);

	if(index_of_attack == 3)
		window -> draw_img(pic_path[1] , Rectangle(pic_x , pic_y , width , height) , clips[level][index_of_attack] , angle);

}

void Missile::draw_enemy_in(double angle , int index_of_attack)
{
	window -> draw_img(pic_path[0] , Rectangle(pic_x , pic_y , width , height) , clips[level][index_of_attack] , angle);
}

void Tesla::draw_enemy_in(double angle , int index_of_attack) 
{
	window -> draw_img(pic_path[0] , Rectangle(pic_x , pic_y , width , height) , clips[level][2]);
}

void Glue::draw_enemy_in(double angle , int index_of_attack)
{
	if(level == 2 && index_of_attack == 3)
		window -> draw_img(pic_path[1] , Rectangle(pic_x , pic_y , width , height) , clips[level][index_of_attack] , angle);

	else
		window -> draw_img(pic_path[0] , Rectangle(pic_x , pic_y , width , height) , clips[level][index_of_attack] , angle);
}

vector<vector<Rectangle> > Gatling::init_clips()
{
	vector<vector<Rectangle> > rects(NUMBER_OF_LEVELS);

	rects[LEVEL_1].push_back(Rectangle(17 , 130 , width , height));
	rects[LEVEL_1].push_back(Rectangle(14 , 0 , width , height));
	rects[LEVEL_1].push_back(Rectangle(910 , 560 , width + 10 , height + 10));
	rects[LEVEL_1].push_back(Rectangle(125 , 359 , width , height));
	rects[LEVEL_2].push_back(Rectangle(466 , 230 , width , height + 10));
	rects[LEVEL_2].push_back(Rectangle(570 , 115 , width , height + 10));
	rects[LEVEL_2].push_back(Rectangle(347 , 243 , width , height + 20));
	rects[LEVEL_2].push_back(Rectangle(366 , 399 , width + 10 , height + 10));
	rects[LEVEL_3].push_back(Rectangle(570 , 418 , width + 5 , height + 8));
	rects[LEVEL_3].push_back(Rectangle(353 , 470 , width + 5 , height + 8));
	rects[LEVEL_3].push_back(Rectangle(256 , 547 , width + 5 , height + 15));
	rects[LEVEL_3].push_back(Rectangle(736 , 755 , width + 5 , height + 15));

	return rects;
}

vector<vector<Rectangle> > Missile::init_clips()
{
	vector<vector<Rectangle> > rects(NUMBER_OF_LEVELS);

	rects[LEVEL_1].push_back(Rectangle(222 , 190 , width , height));
	rects[LEVEL_1].push_back(Rectangle(325 , 290 , width , height));
	rects[LEVEL_1].push_back(Rectangle(11 , 0 , width , height));
	rects[LEVEL_1].push_back(Rectangle(323 , 277 , width , height));
	rects[LEVEL_2].push_back(Rectangle(734 , 219 , width , height + 10));
	rects[LEVEL_2].push_back(Rectangle(841 , 123 , width , height + 10));
	rects[LEVEL_2].push_back(Rectangle(322 , 384 , width , height + 10));
	rects[LEVEL_2].push_back(Rectangle(841 , 123 , width , height + 10));
	rects[LEVEL_3].push_back(Rectangle(109 , 807 , width , height + 10));
	rects[LEVEL_3].push_back(Rectangle(426 , 505 , width , height + 10));
	rects[LEVEL_3].push_back(Rectangle(529 , 400 , width , height + 10));
	rects[LEVEL_3].push_back(Rectangle(426 , 505 , width , height + 10));

	return rects;
}

vector<vector<Rectangle> > Tesla::init_clips()
{
	vector<vector<Rectangle> > rects(NUMBER_OF_LEVELS);

	rects[LEVEL_1].push_back(Rectangle(0 , 0 , width , height));
	rects[LEVEL_1].push_back(Rectangle(0 , 408 , width , height));
	rects[LEVEL_1].push_back(Rectangle(0 , 408 , width , height));
	rects[LEVEL_2].push_back(Rectangle(0 , 120 , width , height));
	rects[LEVEL_2].push_back(Rectangle(0 , 528 , width , height));
	rects[LEVEL_2].push_back(Rectangle(0 , 528 , width , height));
	rects[LEVEL_3].push_back(Rectangle(0 , 249 , width , height + 30));
	rects[LEVEL_3].push_back(Rectangle(0 , 653 , width , height + 30));
	rects[LEVEL_3].push_back(Rectangle(0 , 653 , width , height + 30));

	return rects;
}

vector<vector<Rectangle> > Glue::init_clips()
{
	vector<vector<Rectangle> > rects(NUMBER_OF_LEVELS);

	rects[LEVEL_1].push_back(Rectangle(137 , 152 , width , height));
	rects[LEVEL_1].push_back(Rectangle(18 , 0 , width , height));
	rects[LEVEL_1].push_back(Rectangle(15 , 0 , width , height));
	rects[LEVEL_1].push_back(Rectangle(624 , 140 , width , height));
	rects[LEVEL_2].push_back(Rectangle(5 , 435 , width , height));
	rects[LEVEL_2].push_back(Rectangle(619 , 293 , width , height + 3));
	rects[LEVEL_2].push_back(Rectangle(619 , 293 , width , height + 3));
	rects[LEVEL_2].push_back(Rectangle(625 , 454 , width , height));
	rects[LEVEL_3].push_back(Rectangle(850 , 459 , width + 10 , height));
	rects[LEVEL_3].push_back(Rectangle(250 , 726 , width + 10, height));
	rects[LEVEL_3].push_back(Rectangle(250 , 726 , width + 10 , height));
	rects[LEVEL_3].push_back(Rectangle(7 , 467 , width , height));

	return rects;
}


