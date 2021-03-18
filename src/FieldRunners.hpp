#include<iostream>
#include "rsdl.hpp"
#include "Player.hpp"
#include "defines.hpp"
#include "Towers.hpp"
#include "Timer.hpp"
#include "Enemy.hpp"

#ifndef __FieldRunners_CC__
#define __FieldRunners_CC__

class FieldRunners
{
public:
	FieldRunners(Window* _window , Player* _player , std::vector<std::string> _stdin);
	void play();

private:
	char move_on_tower_icons(Point mouse_point);
	void handle_input(Event& e , Point& mouse_point , Point& , char&);
	void draw_icons();
	bool is_point_draw(std::vector<Point> pre_point , Point cur_point);
	void update(Point mouse_point , std::vector<Point> path_points);
	void new_tower(char type , Event e , Point mouse_point , std::vector<Point> points);
	bool is_place_in_enemies_path(Point mouse_point , std::vector<Point> points);
	bool is_place_invalid(Point mouse_point);
	bool is_tower_in_place(Point point);
	void new_missile(Point mouse_point);
	void new_gatling(Point mouse_point);
	void new_tesla(Point mouse_point);
	void new_glue(Point mouse_point);
	void update_tower(Point mouse_point);
	void new_runner(std::vector<Point> points);
	void new_stubborn_runner(std::vector<Point> points);
	void new_super_trooper(std::vector<Point> points);
	void new_scrambler(std::vector<Point> points);
	void make_rand_enemies(std::vector<Point> points);
	void draw_towers_by_checking_place(Point mouse_point);
	void draw_enemies();
	void draw_path(std::vector<Point> path_points);
	void handle_path_frames(Timer& timer , int& frame , int& inc , int& reduce);
	void new_enemies(std::vector<Point> points);
	int check_place_for_attack(int);
	void check_shot_collision();
	std::vector<Point> make_points();
	void make_waves();
	void start_waves(std::vector<Point> points);
	bool is_enemies_killed();
	void kill_enemy();
	void check_game_state(Point mouse_point , std::vector<Point> path_points);
	void delete_towers();
	void show_you_win();
	void show_you_lose();
	int is_end();
	void draw_shots();
	void push_on_points_of_path(std::vector<Point>& path_points , Point p1 , Point p2 , std::string mode);
	void shot_collision(Point col_point , int index_of_enemy , int index_of_tower , std::string shot_type);

	Window* window;
	Player* player;
	std::vector<std::string> stdin;
	std::vector<Tower*> towers;
	std::vector<Enemy*> enemies;
	std::vector<std::vector<int> > waves;
	std::vector<Timer> timers;
	int current_wave;
	int num_of_waves;
};

#endif
