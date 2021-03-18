#include<iostream>
#include "rsdl.hpp"
#include "Timer.hpp"
#include "Shot.hpp"

#ifndef __Enemy_CC__
#define __Enemy_CC__

class Enemy
{
public:
	Enemy(std::vector<std::string> _pic_path , Window* _window , std::vector<Point> _points);
	~Enemy();
	virtual std::vector<std::vector<Rectangle> > make_clips() = 0;
	void draw();
	bool is_killed();
	bool is_reached();
	bool is_in_range(int x , int y , int r);
	int make_angle(int x , int y , double& angle);
	void get_hurt(int damage);
	int get_reduce_player_health() { return reduce_player_health; }
	int get_kill_price() { return kill_price; }
	void draw_killed();
	int get_kill_state() { return kill_state; }
	void kill_state_on() { kill_state = 1; }
	void give_shot(Shot* shot) { shots.push_back(shot); }
	bool is_shot_collision(std::string& shot_type , int& index_of_tower);
	void draw_shots();
	Point get_collision_point();
	void slow_down(int damage , int glue_influence_time);
	bool is_stuck();
	void check_speed();
	virtual std::string get_type() = 0;
	Timer* get_kill_timer() { return kill_timer; }
	
protected:
	void new_point();
	void replace_point();
	int width , height;
	double initial_health;
	double health;
	int vel_per_pix;
	int const_vel;
	int kill_price;
	int reduce_player_health;
	std::vector<std::string> pic_path;
	std::vector<std::vector<Rectangle> > clips;
	Window* window;
	std::vector<Timer> timers;
	Timer* kill_timer;
	std::vector<Point> points;
	std::vector<Shot*> shots;
	std::vector<Shot*> collided_shots;
	std::vector<Timer> collided_shots_timers;
	int frame;
	int kill_frame;
	int sprite_mode;
	int kill_state;
	int time_to_speed_up;
};

#endif


#ifndef __TheRunner_CC__
#define __TheRunner_CC__

class TheRunner : public Enemy
{
public:
	TheRunner(std::vector<std::string> _pic_path , Window* _window , std::vector<Point> points , int current_wave);
	virtual std::string get_type() { return "TheRunner"; }

private:
	virtual std::vector<std::vector<Rectangle> > make_clips();
};

#endif


#ifndef __StubbornRunner_CC__
#define __StubbornRunner_CC__

class StubbornRunner : public Enemy
{
public:
	StubbornRunner(std::vector<std::string> _pic_path , Window* _window , std::vector<Point> points , int current_wave);
	virtual std::string get_type() { return "StubbornRunner"; }

private:
	virtual std::vector<std::vector<Rectangle> > make_clips();
};

#endif


#ifndef __SuperTrooper_CC__
#define __SuperTrooper_CC__

class SuperTrooper : public Enemy
{
public:
	SuperTrooper(std::vector<std::string> _pic_path , Window* _window , std::vector<Point> points , int current_wave);
	virtual std::string get_type() { return "SuperTrooper"; }

private:
	virtual std::vector<std::vector<Rectangle> > make_clips();
};

#endif


#ifndef __Scrambler_CC__
#define __Scrambler_CC__

class Scrambler : public Enemy
{
public:
	Scrambler(std::vector<std::string> _pic_path , Window* _window , std::vector<Point> points , int current_wave);
	virtual std::string get_type() { return "Scrambler"; }

private:
	virtual std::vector<std::vector<Rectangle> > make_clips();
};

#endif