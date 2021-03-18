#include "FieldRunners.hpp"
#include "rsdl.hpp"
#include "Player.hpp"
#include "defines.hpp"
#include "Towers.hpp"
#include "Enemy.hpp"
#include "Timer.hpp"
#include "Shot.hpp"
#include "PositionHandler.hpp"
#include<algorithm>
#include<vector>
#include<iostream>
#include<ctime>

using namespace std;

FieldRunners::FieldRunners(Window* _window , Player* _player , vector<string> _stdin)
{
	window = _window;
	player = _player;
	stdin = _stdin;
	make_waves();
	num_of_waves = waves.size();
	current_wave = 1;
	timers.resize(6);
}

vector<Point> FieldRunners::make_points()
{
	vector<int> nums = PositionHandler::s_to_i(0 , stdin);
	vector<Point> points;
	for(int i = 0 ; i < nums.size() - 1 ; i += 2)
		points.push_back(Point(nums[i] , nums[i + 1]));

	return points;
}

void FieldRunners::make_waves()
{
	for(int i = 1 ; i < stdin.size() ; i++)
		waves.push_back(PositionHandler::s_to_i(i , stdin));
}

void FieldRunners::play()
{
	Event e;
	Point mouse_point;
	vector<Point> points = PositionHandler::generate_places(make_points());
	vector<Point> path_points = PositionHandler::make_points_of_path(make_points());
	Point click_mouse_point;
	char type;

	while(true)
	{
		start_waves(points);
		kill_enemy();
		check_shot_collision();

		e = window -> poll_for_event();
		mouse_point = get_current_mouse_position();

		handle_input(e , mouse_point , click_mouse_point , type);

		check_game_state(mouse_point , path_points);
	}
}

void FieldRunners::handle_input(Event& e , Point& mouse_point , Point& click_mouse_point , char& type)
{
	static bool is_click = false;

	if(e.get_type() == Event::QUIT)
		exit(0);

	if(e.get_type() == Event::LCLICK)
	{
		is_click = true;
		click_mouse_point = mouse_point;
	}

	if(is_click == true)
		if(e.get_pressed_key() == U)
		{
			update_tower(mouse_point);
			is_click = false;
		}

	if((type = move_on_tower_icons(mouse_point)) != NOTHING || e.get_type() == Event::KEY_PRESS)
		new_tower(type , e , click_mouse_point , make_points());
}	

void FieldRunners::draw_icons()
{
	int money = player -> get_money();
	window -> draw_img(MIS_ICON + to_string(money < MISSILE_COST) + JPG , Rectangle(MIS_ICON_X , MIS_ICON_Y , MIS_ICON_W , MIS_ICON_H));
	window -> draw_img(GLUE_ICON + to_string(money < GLUE_COST) + JPG , Rectangle(GLUE_ICON_X , GLUE_ICON_Y , GLUE_ICON_W , GLUE_ICON_H));
	window -> draw_img(TESLA_ICON + to_string(money < TESLA_COST) + JPG , Rectangle(TESLA_ICON_X , TESLA_ICON_Y , TESLA_ICON_W , TESLA_ICON_H));
	window -> draw_img(GAT_ICON + to_string(money < GATLING_COST) + JPG , Rectangle(GAT_ICON_X , GAT_ICON_Y , GAT_ICON_W , GAT_ICON_H));
}

char FieldRunners::move_on_tower_icons(Point mouse_point)
{
	if(mouse_point.x > MIS_ICON_X && mouse_point.x < MIS_ICON_W + MIS_ICON_X && mouse_point.y > MIS_ICON_Y && mouse_point.y < MIS_ICON_H + MIS_ICON_Y)
		return M;

	if(mouse_point.x > GLUE_ICON_X && mouse_point.x < GLUE_ICON_X + GLUE_ICON_W && mouse_point.y > GLUE_ICON_Y && mouse_point.y < GLUE_ICON_Y + GLUE_ICON_H)
		return L;

	if(mouse_point.x > TESLA_ICON_X && mouse_point.x < TESLA_ICON_X + TESLA_ICON_W && mouse_point.y > TESLA_ICON_Y && mouse_point.y < TESLA_ICON_Y + TESLA_ICON_H)
		return T;

	if(mouse_point.x > GAT_ICON_X && mouse_point.x < GAT_ICON_X + GAT_ICON_W && mouse_point.y > GAT_ICON_Y && mouse_point.y < GAT_ICON_Y + GAT_ICON_H)
		return G;

	return NOTHING;
}

void FieldRunners::check_game_state(Point mouse_point , vector<Point> path_points)
{
	if(is_end() == NOT_END)
		update(mouse_point , path_points);

	if(is_end() == LOSE_END)
	{
		delete_towers();
		show_you_lose();
	}

	else if(is_end() == WIN_END)
	{
		delete_towers();
		show_you_win();
	}

}

void FieldRunners::delete_towers()
{
	for(int i = 0 ; i < towers.size() ; i++)
		if(towers[i] != NULL)
		{
			delete towers[i];
			towers[i] = NULL;
		}
}

void FieldRunners::show_you_win()
{
	static int y = 0;

	if(!timers[2].is_started())
		timers[2].start();

	if(timers[2].get_ticks() < END_UP_TIME)
	{
		window -> draw_img(WIN_PIC_PATH);
		window -> draw_img(END_WIN  , Rectangle(700 , y , 150 , 150));
		y += DELTA_Y;

		window -> update_screen();
	}

	else 
		exit(0);
}

void FieldRunners::show_you_lose()
{
	if(!timers[2].is_started())
		timers[2].start();
	
	if(timers[2].get_ticks() < END_UP_TIME)
	{
		window -> draw_img(LOSE_PIC_PATH);
		window -> draw_img(END_LOSE , Rectangle(700 , 700 , 100 , 120));

		window -> update_screen();
	}

	else
		exit(0);
}

void FieldRunners::new_runner(vector<Point> points)
{
	vector<string> paths {"./extra/unit_light_soldier_00000.png" , "./extra/unit_light_soldier_00001.png"};
	TheRunner* runner = new TheRunner(paths , window , points , current_wave);
	enemies.push_back(runner);
}

void FieldRunners::new_stubborn_runner(vector<Point> points)
{
	vector<string> paths {"./extra/unit_icerunner_00000.png" , "./extra/unit_icerunner_00001.png" , "./extra/unit_icerunner_00002.png"};
	StubbornRunner* stubborn = new StubbornRunner(paths , window , points , current_wave);
	enemies.push_back(stubborn);
}

void FieldRunners::new_super_trooper(vector<Point> points)
{
	vector<string> paths {"./extra/unit_heavy_soldier_00000.png" , "./extra/unit_heavy_soldier_00001.png"};
	SuperTrooper* super_trooper = new SuperTrooper(paths , window , points , current_wave);
	enemies.push_back(super_trooper);
}

void FieldRunners::new_scrambler(vector<Point> points)
{
	vector<string> paths {"./extra/unit_bike_00000.png" , "./extra/unit_bike_00001.png"};
	Scrambler* scrambler = new Scrambler(paths , window , points , current_wave);
	enemies.push_back(scrambler);
}

int FieldRunners::is_end()
{
	if(player -> is_lose())
		return LOSE_END;

	else if(waves.size() == 0)
		return WIN_END;

	return NOT_END;
}

void FieldRunners::start_waves(vector<Point> points)
{
	if(waves.size() > 0)
		new_enemies(points);

	if(is_enemies_killed())
	{
		if(!timers[3].is_started())
			timers[3].start();

		if(timers[3].get_ticks() > DELAY_OF_WAVES)
		{
			waves.erase(waves.begin());
			current_wave++;
			enemies.clear();
			timers[3].stop();
		}
	}
}

void FieldRunners::update(Point mouse_point , vector<Point> path_points)
{
	window -> draw_img(BACK_IMG_PATH);
	player -> show_money_heart();
	window -> show_text("Wave " + to_string(num_of_waves - waves.size() + 1) + " / " +to_string(num_of_waves) , Point(117 , 20) , BLACK , TTF_MONEY_PATH , 32);

	draw_icons();
	draw_path(path_points);
	draw_enemies();
	draw_shots();
	draw_towers_by_checking_place(mouse_point);

	window -> update_screen();
	window -> clear();
	delay(GAME_DELAY);
}

bool FieldRunners::is_enemies_killed()
{
	if(enemies.size() == 0)
		return false;

	for(int i = 0 ; i < enemies.size() ; i++)
		if(enemies[i] != NULL)
			return false;

	return true;
}

void FieldRunners::draw_path(vector<Point> path_points)
{
	vector<Point> path_pos = PositionHandler::generate_places(path_points);
	static int frame = 0;
	static int inc = 1 , reduce = 0;
	vector<Point> pre_paths;
	
	if(!timers[1].is_started())
		timers[1].start();

	for(int i = 0 ; i < path_pos.size() ; i++)
	{
	 	if(!is_point_draw(pre_paths , path_pos[i]))
			window -> draw_img("./path_" + to_string(frame) + PNG , Rectangle(path_pos[i].x - SIZE_OF_SQUARE / 2 , path_pos[i].y - SIZE_OF_SQUARE / 2 , SIZE_OF_SQUARE , SIZE_OF_SQUARE));
	 	pre_paths.push_back(path_pos[i]);
	}

	handle_path_frames(timers[1] , frame , inc , reduce);
}

void FieldRunners::handle_path_frames(Timer& timer , int& frame , int& inc , int& reduce)
{
	if(frame == PATH_MAX_FRAME)
	{
		inc = 0;
		reduce = 1;
	}
	if(frame == 0)
	{
		inc = 1;
		reduce = 0;
	}

	if(timer.get_ticks() > PATH_DELAY)
	{
		if(inc && frame != PATH_MAX_FRAME)
			frame++;

		if(reduce && frame != 0)
			frame--;

		timer.stop();
	}
}

bool FieldRunners::is_point_draw(vector<Point> pre_point , Point cur_point)
{
	for(int i = 0 ; i < pre_point.size() ; i++)
		if(cur_point.x == pre_point[i].x && cur_point.y == pre_point[i].y)
			return true;

	return false;
}

void FieldRunners::kill_enemy()
{
	for(int i = 0 ; i < enemies.size() ; i++)
		if(enemies[i] != NULL)
		{
			if(enemies[i] -> is_killed())
			{
				enemies[i] -> kill_state_on();
				if(!enemies[i] -> get_kill_timer() -> is_started())
					enemies[i] -> get_kill_timer() -> start();
				if(enemies[i] -> get_kill_timer() -> get_ticks() > KILL_DELAY) 
				{
					player -> inc_money(enemies[i] -> get_kill_price());

					enemies[i] -> get_kill_timer() -> stop();
					delete enemies[i];
					enemies[i] = NULL;
				}
			}
			else if(enemies[i] -> is_reached())
			{
				player -> new_heart(enemies[i] -> get_reduce_player_health());
				delete enemies[i];
				enemies[i] = NULL;
			}
		}
}

void FieldRunners::new_gatling(Point mouse_point)
{
	Point point = PositionHandler::mouse_point_to_pos(mouse_point);
	vector<string> paths { "./extra/tower_gatling_00000.png" , "./extra/tower_gatling_00001.png" , "./extra/tower_gatling_00002.png"};
	Gatling* gatling = new Gatling(point.x , point.y , paths , window);

	if(player -> get_money() < gatling -> get_cost())
	{
		delete gatling;
		return;
	}

	player -> reduce_money(gatling -> get_cost());

	towers.push_back(gatling);
}

void FieldRunners::new_tesla(Point mouse_point)
{
	Point point = PositionHandler::mouse_point_to_pos(mouse_point);
	vector<string> paths { "./extra/tower_lightning_00000.png"};
	Tesla* tesla = new Tesla(point.x , point.y , paths , window);

	if(player -> get_money() < tesla -> get_cost())
	{
		delete tesla;
		return;
	}

	player -> reduce_money(tesla -> get_cost());

	towers.push_back(tesla);
}

void FieldRunners::new_glue(Point mouse_point)
{
	Point point = PositionHandler::mouse_point_to_pos(mouse_point);
	vector<string> paths { "./extra/tower_goo_00000.png" , "./extra/tower_goo_00001.png"};
	Glue* glue = new Glue(point.x , point.y , paths , window);

	if(player -> get_money() < glue -> get_cost())
	{
		delete glue;
		return;
	}

	player -> reduce_money(glue -> get_cost());

	towers.push_back(glue);
}

void FieldRunners::draw_towers_by_checking_place(Point mouse_point)
{
	int attack_mode = 0;
	for(int i = 0 ; i < towers.size() ; i++)
	{
		attack_mode = check_place_for_attack(i);

		if(attack_mode == 0)
			if(towers[i] -> is_mouse_in_tower(mouse_point))
			{
				towers[i] -> draw("mouse_in");
				continue;
			}

		if(attack_mode == 0)
			towers[i] -> draw("new_tower");

		attack_mode = 0;
	}
}

int FieldRunners::check_place_for_attack(int i)
{
	int attack_mode = 0;

	for(int j = 0 ; j < enemies.size() ; j++)
		if(enemies[j] != NULL)
		{
			if(enemies[j] -> get_kill_state() == 0)
			{
				if(enemies[j] -> is_in_range(towers[i] -> get_x() , towers[i] -> get_y() , RANGE_OF_TOWERS))
				{
					double angle;
					int index_of_attack = enemies[j] -> make_angle(towers[i] -> get_x() , towers[i] -> get_y() , angle);
					towers[i] -> draw("enemy_in" , angle , index_of_attack);

					if(towers[i] -> is_shot())
						if(enemies[j] -> get_kill_state() == 0)
							enemies[j] -> give_shot(new Shot(towers[i] -> get_x() , towers[i] -> get_y() + 30 , window , towers[i] , i));
					

					attack_mode = 1;
					break;
				}
			}
		}

	return attack_mode;
}

void FieldRunners::check_shot_collision()
{
	string shot_type;
	int index_of_tower;
	for(int i = 0 ; i < enemies.size() ; i++)
		if(enemies[i] != NULL)
			if(enemies[i] -> is_shot_collision(shot_type , index_of_tower))
				shot_collision(enemies[i] -> get_collision_point() , i , index_of_tower , shot_type);
}

void FieldRunners::shot_collision(Point col_point , int index_of_enemy , int index_of_tower , string shot_type)
{
	if(shot_type == GATLING)
		if(enemies[index_of_enemy] -> get_type().compare("StubbornRunner") != 0)
			enemies[index_of_enemy] -> get_hurt(towers[index_of_tower] -> damage_enemy());

	if(shot_type == TESLA)
		enemies[index_of_enemy] -> get_hurt(towers[index_of_tower] -> damage_enemy());

	if(shot_type == MISSILE)
		for(int i = 0 ; i < enemies.size() ; i++)
			if(enemies[i] != NULL)
				if(enemies[i] -> is_in_range(col_point.x , col_point.y , RANGE_OF_MISSILE_SHOT))
					enemies[i] -> get_hurt(towers[index_of_tower] -> damage_enemy());

	if(shot_type == GLUE)
		for(int i = 0 ; i < enemies.size() ; i++)
			if(enemies[i] != NULL)
				if(enemies[i] -> is_in_range(col_point.x , col_point.y , RANGE_OF_GLUE_SHOT) && (enemies[i] -> get_type().compare("StubbornRunner") != 0))
					if(!enemies[i] -> is_stuck())
						enemies[i] -> slow_down(towers[index_of_tower] -> damage_enemy() , towers[index_of_tower] -> get_glue_influence_time());

}

void FieldRunners::new_enemies(vector<Point> points)
{
	if(!(timers[0].is_started()))
		timers[0].start();

	if(timers[0].get_ticks() > DELAY_OF_NEW_ENEMIES)
	{
		make_rand_enemies(points);
		timers[0].start();
	}

	if(enemies.size() == waves[0][0] + waves[0][1] + waves[0][2] + waves[0][3])
		timers[0].stop();
}

void FieldRunners::make_rand_enemies(vector<Point> points)
{
	srand(time(0));
	static int runner_count = 0 , stubborn_count = 0 , super_count = 0 , scrambler_count = 0;
	static int num_of_wave = current_wave;

	if(num_of_wave < current_wave)
	{
		runner_count = stubborn_count = super_count = scrambler_count = 0;
		num_of_wave = current_wave;
	}

	while(runner_count < waves[0][0] || stubborn_count < waves[0][1] || super_count < waves[0][2] || scrambler_count < waves[0][3])
	{
		int rand_num = rand() % NUM_OF_ENEMIES;
		if(rand_num == 0)
			if(runner_count < waves[0][rand_num])
			{
				runner_count++;
				new_runner(points);
				return;
			}

		if(rand_num == 1)
			if(stubborn_count < waves[0][rand_num])
			{
				stubborn_count++;
				new_stubborn_runner(points);
				return;
			}

		if(rand_num == 2)
			if(super_count < waves[0][rand_num])
			{
				super_count++;
				new_super_trooper(points);
				return;
			}

		if(rand_num == 3)
		{
			if(scrambler_count < waves[0][rand_num])
			{
				scrambler_count++;
				new_scrambler(points);
				return;
			}
		}
	}
}

void FieldRunners::draw_enemies()
{
	for(int i = 0 ; i < enemies.size() ; i++)
	{
		if(enemies[i] != NULL)
		{
			if(enemies[i] -> get_kill_state() == 0)
			{
				if(enemies[i] -> is_stuck())
					enemies[i] -> check_speed();

				enemies[i] -> draw();
			}
			else
				enemies[i] -> draw_killed();
		}
	}
}

void FieldRunners::draw_shots()
{
	for(int i = 0 ; i < enemies.size() ; i++)
		if(enemies[i] != NULL)
			enemies[i] -> draw_shots();
}

void FieldRunners::new_missile(Point mouse_point)
{
	vector<Point> points = PositionHandler::generate_places(vector<Point>(1 , PositionHandler::mouse_pos_to_point(mouse_point)));
	Point point = points[0];
	vector<string> paths {"./extra/tower_missile_00000.png"};
	Missile* missile = new Missile(point.x , point.y , paths , window);

	if(player -> get_money() < missile -> get_cost())
	{
		delete missile;
		return;
	}

	player -> reduce_money(missile -> get_cost());

	towers.push_back(missile);
}

void FieldRunners::new_tower(char type , Event e , Point mouse_point , vector<Point> points)
{
	if(is_place_in_enemies_path(mouse_point , points))
		return;

	if(is_tower_in_place(mouse_point))
		return;

	if(is_place_invalid(mouse_point))
		return;

	if(type == G || e.get_pressed_key() == G)	
		new_gatling(mouse_point);

	if(type == M || e.get_pressed_key() == M)
		new_missile(mouse_point);

	if(type == T || e.get_pressed_key() == T)
		new_tesla(mouse_point);

	if(type == L || e.get_pressed_key() == L)
		new_glue(mouse_point);
}

bool FieldRunners::is_place_invalid(Point mouse_point)
{
	if(mouse_point.x > MAX_X_OF_BOARD || mouse_point.x < MIN_X_OF_BOARD || mouse_point.y > MAX_Y_OF_BOARD || mouse_point.y < MIN_Y_OF_BOARD)
		return true;

	return false;
}

bool FieldRunners::is_tower_in_place(Point point)
{
	Point mouse_point = PositionHandler::mouse_point_to_pos(point);
	for(int i = 0 ; i < towers.size() ; i++)
		if(mouse_point.x == towers[i] -> get_x() && mouse_point.y == towers[i] -> get_y())
			return true;

	return false;
}

void FieldRunners::update_tower(Point mouse_point)
{
	for(int i = 0 ; i < towers.size() ; i++)
		if(towers[i] -> is_mouse_in_tower(mouse_point))
		{
			if(player -> get_money() >= towers[i] -> get_update_cost() && !(towers[i] -> is_max_level()))
			{
				player -> reduce_money(towers[i] -> get_update_cost());
				towers[i] -> level_up();
			}
		}
}

bool FieldRunners::is_place_in_enemies_path(Point mouse_point , vector<Point> points)
{
	vector<Point> path_points = PositionHandler::make_points_of_path(points);

	for(int i = 0 ; i < path_points.size() ; i++)
		if(PositionHandler::mouse_pos_to_point(mouse_point).x == path_points[i].x && PositionHandler::mouse_pos_to_point(mouse_point).y == path_points[i].y)
			return true;

	return false;
}