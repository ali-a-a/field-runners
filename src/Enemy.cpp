#include<iostream>
#include<vector>
#include<cmath>
#include "rsdl.hpp"
#include "Enemy.hpp"
#include "Timer.hpp"
#include "Shot.hpp"
#include "defines.hpp"

using namespace std;

Enemy::Enemy(vector<string> _pic_path , Window* _window , vector<Point> _points)
{
	frame = 0;
	kill_state = 0;
	sprite_mode = 0;
	kill_frame = 0;
	points = _points;
	window = _window;
	pic_path = _pic_path;
	kill_timer = new Timer();
	timers.resize(3);
}

Enemy::~Enemy()
{
	for(int i = 0 ; i < collided_shots.size() ; i++)
	{
		delete collided_shots[i];
		collided_shots[i] = NULL;
	}

	for(int i = 0 ; i < shots.size() ; i++)
	{
		delete shots[i];
		shots[i] = NULL;
	}

	delete kill_timer;
	kill_timer = NULL;
}

TheRunner::TheRunner(std::vector<std::string> _pic_path , Window* _window , vector<Point> _points , int current_wave)
	: Enemy(_pic_path , _window , _points)
{
	width = 35;
	height = 60;
	initial_health = 250;
	health = (0.9 + 0.1 * current_wave) * initial_health;
	vel_per_pix = 50;
	const_vel = vel_per_pix;
	kill_price = 6;
	reduce_player_health = 1;
	clips = make_clips();
}	

StubbornRunner::StubbornRunner(std::vector<std::string> _pic_path , Window* _window , vector<Point> _points , int current_wave)
	: Enemy(_pic_path , _window , _points)
{
	width = 47;
	height = 71;
	initial_health = 400;
	health = (0.9 + 0.1 * current_wave) * initial_health;
	vel_per_pix = 30;
	const_vel = vel_per_pix;
	kill_price = 10;
	reduce_player_health = 4;
	clips = make_clips();
}

SuperTrooper::SuperTrooper(std::vector<std::string> _pic_path , Window* _window , vector<Point> _points , int current_wave)
	: Enemy(_pic_path , _window , _points)
{
	width = 64;
	height = 69;
	initial_health = 500;
	health = (0.9 + 0.1 * current_wave) * initial_health;
	vel_per_pix = 25;
	const_vel = vel_per_pix;
	kill_price = 8;
	reduce_player_health = 4;
	clips = make_clips();
}

Scrambler::Scrambler(std::vector<std::string> _pic_path , Window* _window , vector<Point> _points , int current_wave)
	: Enemy(_pic_path , _window , _points)
{	
	width = 86;
	height = 68;
	initial_health = 100;
	health = (0.9 + 0.1 * current_wave) * initial_health;
	vel_per_pix = 90;
	const_vel = vel_per_pix;
	kill_price = 4;
	reduce_player_health = 2;
	clips = make_clips();
}

bool Enemy::is_reached()
{
	if(points.size() == 1)
		return true;

	return false;
}

bool Enemy::is_killed()
{
	if(health <= 0 )
		return true;

	return false;
}

void Enemy::get_hurt(int damage)
{
	health -= damage;
}

void Enemy::check_speed()
{
	if(!timers[1].is_started())
		timers[1].start();

	if(timers[1].get_ticks() > time_to_speed_up)
	{
		vel_per_pix = const_vel;
		timers[1].stop();
	}

}

void Enemy::slow_down(int damage , int glue_influence_time)
{
	vel_per_pix = (100 - damage) * vel_per_pix / 100;
	time_to_speed_up = glue_influence_time;
	check_speed();
}

bool Enemy::is_stuck()
{
	if(timers[1].is_started())
		return true;

	return false;
}

bool Enemy::is_in_range(int x , int y , int r)
{
	if(sqrt(pow(x - points[0].x , 2) + pow(y - points[0].y , 2)) > r)
		return false;

	return true;
}

int Enemy::make_angle(int x , int y , double& angle)
{
	angle = atan2(points[0].y - y , points[0].x - x);
	angle = angle * 180.0 / M_PI;
	
	if(points[0].y <= y)
	{
		if(x <= points[0].x)
	 		angle += NINETY;
		if(x > points[0].x)
			angle += NINETY;

		return INDEX_OF_ATTACK_2;
	}
	if(points[0].y > y)
	{
		if(x <= points[0].x)
	 		angle -= NINETY;
		if(x > points[0].x)
			angle -= NINETY;

		return INDEX_OF_ATTACK_3;
	}

	return -1;
}

vector<vector<Rectangle> > TheRunner::make_clips()
{
	vector<vector<Rectangle> > rects(5);
	for(int i = 0 ; i < 270 ; i += 41)
		rects[RUNNING_RIGHT].push_back(Rectangle(i , 120 , width , height));

	for(int i = 232 ; i < 397; i += 33)
		rects[RUNNING_DOWN].push_back(Rectangle(i , 0 , width , height));
	rects[RUNNING_DOWN].push_back(Rectangle(231 , 0 , width , height));

	for(int i = 987 ; i > 700 ; i -= 39)
		rects[RUNNING_LEFT].push_back(Rectangle(i , 120 , width , height));

	rects[RUNNING_UP].push_back(Rectangle(56 , 0 , width , height));
	for(int i = 90 ; i < 220 ; i += 34)
		rects[RUNNING_UP].push_back(Rectangle(i , 0 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(56 , 0 , width ,height));

	rects[DEATH].push_back(Rectangle(901 , 862 , width + 12 , height - 10));
	rects[DEATH].push_back(Rectangle(950 , 862 , width + 12, height - 10));
	rects[DEATH].push_back(Rectangle(895 , 943 , width + 12 , height - 10));
	rects[DEATH].push_back(Rectangle(948 , 933 , width + 12 , height - 10));
	rects[DEATH].push_back(Rectangle(488 , 362 , width + 12 , height - 10));
	rects[DEATH].push_back(Rectangle(488 , 362 , width + 12 , height - 10));

	return rects;
}

vector<vector<Rectangle> > StubbornRunner::make_clips()
{
	vector<vector<Rectangle> > rects(5);
	for(int i = 0 ; i < 192 ; i += 48)
		rects[RUNNING_RIGHT].push_back(Rectangle(i , 228 , width , height));
	rects[RUNNING_RIGHT].push_back(Rectangle(2 , 372 , width , height));
	rects[RUNNING_RIGHT].push_back(Rectangle(2 , 230 , width , height));

	for(int i = 105 ; i < 361 ; i += 52)
		rects[RUNNING_DOWN].push_back(Rectangle(i , 302 , width + 5 , height));
	rects[RUNNING_DOWN].push_back(Rectangle(233 , 379 , width + 5 , height));

	rects[RUNNING_LEFT].push_back(Rectangle(740 , 151 , width , height));
	rects[RUNNING_LEFT].push_back(Rectangle(739 , 148 , width , height));
	rects[RUNNING_LEFT].push_back(Rectangle(689 , 151 , width , height));
	rects[RUNNING_LEFT].push_back(Rectangle(637 , 148 , width , height - 1));
	rects[RUNNING_LEFT].push_back(Rectangle(581 , 139 , width , height));
	rects[RUNNING_LEFT].push_back(Rectangle(581 , 139 , width , height));
	rects[RUNNING_LEFT].push_back(Rectangle(581 , 139 , width , height));
	rects[RUNNING_LEFT].push_back(Rectangle(581 , 139 , width , height));

	rects[RUNNING_UP].push_back(Rectangle(0 , 0 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(51 , 0 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(104 , 0 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(158 , 0 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(252 , 0 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(303 , 0 ,width , height));

	rects[DEATH].push_back(Rectangle(713 , 695 , width , height));
	rects[DEATH].push_back(Rectangle(891 , 501 , width , height));
	rects[DEATH].push_back(Rectangle(982 , 303 , width , height));
	rects[DEATH].push_back(Rectangle(598 , 342 , width , height));
	rects[DEATH].push_back(Rectangle(547 , 410 , width , height));
	rects[DEATH].push_back(Rectangle(547 , 410 , width , height));

	return rects;
}

vector<vector<Rectangle> > SuperTrooper::make_clips()
{
	vector<vector<Rectangle> > rects(5);
	rects[RUNNING_RIGHT].push_back(Rectangle(70 , 224 , width , height));
	rects[RUNNING_RIGHT].push_back(Rectangle(70 , 224 , width , height));
	rects[RUNNING_RIGHT].push_back(Rectangle(149 , 309 , width , height));
	rects[RUNNING_RIGHT].push_back(Rectangle(240 , 225 , width , height));
	rects[RUNNING_RIGHT].push_back(Rectangle(375 , 159 , width , height));
	rects[RUNNING_RIGHT].push_back(Rectangle(437 , 159 , width , height));

	rects[RUNNING_DOWN].push_back(Rectangle(510 , 0 , width , height));
	rects[RUNNING_DOWN].push_back(Rectangle(579 , 0 , width , height));
	rects[RUNNING_DOWN].push_back(Rectangle(648 , 0 , width , height));
	rects[RUNNING_DOWN].push_back(Rectangle(445 , 82 , width , height));
	rects[RUNNING_DOWN].push_back(Rectangle(514 , 71 , width , height));
	rects[RUNNING_DOWN].push_back(Rectangle(514 , 71 , width , height));

	rects[RUNNING_LEFT].push_back(Rectangle(955 , 230 , width , height));
	rects[RUNNING_LEFT].push_back(Rectangle(643 , 150 , width - 4 , height + 2));
	rects[RUNNING_LEFT].push_back(Rectangle(889 , 225 , width , height));
	rects[RUNNING_LEFT].push_back(Rectangle(782 , 224 , width - 1 , height));
	rects[RUNNING_LEFT].push_back(Rectangle(722 , 225 , width - 1 , height));
	rects[RUNNING_LEFT].push_back(Rectangle(722 , 225 , width - 1 , height));

	rects[RUNNING_UP].push_back(Rectangle(0 , 67 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(124 , 72 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(187 , 72 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(328 , 0 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(324 , 80 , width , height));
	rects[RUNNING_UP].push_back(Rectangle(65 , 0 , width , height));

	rects[DEATH].push_back(Rectangle(172 , 596 , width + 25, height));
	rects[DEATH].push_back(Rectangle(172 , 596 , width + 25, height));
	rects[DEATH].push_back(Rectangle(268 , 532 , width + 25 , height));	
	rects[DEATH].push_back(Rectangle(4 , 809 , width + 25 , height));
	rects[DEATH].push_back(Rectangle(167 , 766 , width + 25 , height));
	rects[DEATH].push_back(Rectangle(167 , 766 , width + 25 , height));

	return rects;
}

vector<vector<Rectangle> > Scrambler::make_clips()
{
	vector<vector<Rectangle> > rects(5);
	for(int i = 0 ; i < 6 ; i++)
		rects[RUNNING_RIGHT].push_back(Rectangle(3 , 77 , width , height - 1));

	for(int i = 0 ; i < 6 ; i++)
		rects[RUNNING_DOWN].push_back(Rectangle(168 , 80 , width , height));

	for(int i = 0 ; i < 6 ; i++)
		rects[RUNNING_LEFT].push_back(Rectangle(940 , 77 , width , height - 1));

	for(int i = 0; i < 6 ; i++)
		rects[RUNNING_UP].push_back(Rectangle(0 , 0 , width , height));

	rects[DEATH].push_back(Rectangle(1 , 200 , width , height));
	rects[DEATH].push_back(Rectangle(0 , 267 , width , height));
	rects[DEATH].push_back(Rectangle(0 , 339 , width , height));
	rects[DEATH].push_back(Rectangle(0 , 416 , width , height));
	rects[DEATH].push_back(Rectangle(85 , 415 , width , height));
	rects[DEATH].push_back(Rectangle(85 , 415 , width , height));

	return rects;
}

void Enemy::draw()
{
	int index_of_pic = 0;

	if(sprite_mode == RUNNING_LEFT)
		index_of_pic = 1;

	window -> draw_img(pic_path[index_of_pic] , Rectangle(points[0].x - width / 2 , points[0].y - height / 2, width , height) , clips[sprite_mode][frame]);
	window -> show_text(to_string((int)health) , Point(points[0].x - 20 , points[0].y - 50) , RED , "./money.TTF" , 16);

	if(!timers[0].is_started())
		timers[0].start();
	if(timers[0].get_ticks() > TIME_OF_CHANGE_FRAME)
	{
		frame++;

		if(frame == MAX_FRAME_FOR_RUN)
			frame = 0;

		new_point();
		timers[0].start();
	}
}

void Enemy::draw_killed()
{
	window -> draw_img(pic_path[0] , Rectangle(points[0].x - width / 2 , points[0].y - height / 2 , width , height) , clips[DEATH][kill_frame]);
	if(!timers[0].is_started())
		timers[0].start();
	if(timers[0].get_ticks() > KILL_CHANGE_FRAME_TIME)
	{
		if(kill_frame != MAX_FRAME_FOR_DIE)
			kill_frame++;

		timers[0].start();
	}
}

void Enemy::new_point()
{
	if(points.size() > 1)
	{
		if(points[0].x < points[1].x)
		{
			points[0].x += vel_per_pix / TEN;
			if(points[0].x >= points[1].x)
				replace_point(); 
			sprite_mode = RUNNING_RIGHT;
		}

		else if(points[0].y < points[1].y)
		{
			points[0].y += vel_per_pix / TEN;
			if(points[0].y >= points[1].y)
				replace_point();

			sprite_mode = RUNNING_DOWN;
		}

		if(points[0].x > points[1].x)
		{
			points[0].x -= vel_per_pix / TEN;
			if(points[0].x <= points[1].x)
				replace_point();

			sprite_mode = RUNNING_LEFT;
		}

		else if(points[0].y > points[1].y)
		{
			points[0].y -= vel_per_pix / TEN;
			if(points[0].y <= points[1].y)
				replace_point();

			sprite_mode = RUNNING_UP;
		}
	}
}

void Enemy::replace_point()
{
	points[0].x = points[1].x;
	points[0].y = points[1].y;
	points.erase(points.begin() + 1); 
}

bool Enemy::is_shot_collision(string& shot_type , int& index_of_tower)
{
	for(int i = 0 ; i < shots.size() ; i++)
		if(points[0].x == shots[i] -> get_x() && points[0].y == shots[i] -> get_y())
		{
			shot_type = shots[i] -> get_shot_type();
			index_of_tower = shots[i] -> get_index_of_tower();
			shots[i] -> set_x(points[0].x - 1);
			shots[i] -> set_y(points[0].y - 1);
			collided_shots.push_back(shots[i]);
			shots.erase(shots.begin() + i);

			if(kill_state == 0)
				return true;
			else 
				return false;
		}

	return false;
}

void Enemy::draw_shots()
{
	for(int j = 0 ; j < collided_shots.size() ; j++)
		collided_shots[j] -> draw(points[0].x , points[0].y , "collision");

	for(int i = 0 ; i < shots.size() ; i++)
		shots[i] -> draw(points[0].x , points[0].y);
}

Point Enemy::get_collision_point()
{
	return points[0];
}


