#include<iostream>
#include<vector>
#include "rsdl.hpp"
#include "Timer.hpp"

#ifndef __Tower_CC__
#define __Tower_CC__

class Tower
{
public:
	Tower(int _x , int _y , std::vector<std::string> _pic_path , Window* _window);
	void draw(std::string mode , double angle = 0 , int index_of_attack_mode = 0);
	virtual std::string get_type() = 0;
	bool is_mouse_in_tower(Point mouse_point);
	virtual void level_up();
	int get_cost() { return cost; }
	int get_update_cost() { return update_cost; }
	int get_x() { return x; }
	int get_y() { return y; }
	int damage_enemy() { return make_damage; }
	bool is_shot();
	bool is_max_level() { return level >= 2; }
	virtual int get_glue_influence_time() { return -1; }

protected:
	int generate_index_of_mode(std::string mode);
	virtual std::vector< std::vector<Rectangle> > init_clips() = 0;
	virtual void draw_enemy_in(double angle , int index_of_attack_mode) = 0;
	
	int x , y , width , height;
	int pic_x , pic_y;
	int level;
	int make_damage;
	int delay;
	int cost;
	int update_cost;
	int delta_damage;
	std::vector<std::string> pic_path;
	std::vector< std::vector<Rectangle> > clips;
	Window* window;
	Timer timer;
};

#endif


#ifndef __Gatling_CC__
#define __Gatling_CC__

class Gatling : public Tower
{
public:
	Gatling(int _x ,int  _y , std::vector<std::string> _pic_path , Window* _window);
	virtual void draw_enemy_in(double angle , int index_of_attack_mode);
	virtual std::string get_type() { return "Gatling"; }

private:
	virtual std::vector< std::vector<Rectangle> > init_clips();
};

#endif


#ifndef __Missle_CC__
#define __Missle_CC__

class Missile : public Tower
{
public:
	Missile(int _x , int _y , std::vector<std::string> _pic_path , Window* _window);
	virtual void draw_enemy_in(double angle , int index_of_attack_mode);
	virtual std::string get_type() { return "Missile"; }

private:
	virtual std::vector< std::vector<Rectangle> > init_clips();
};

#endif


#ifndef __Tesla_CC__
#define __Tesla_CC__

class Tesla : public Tower
{
public:
	Tesla(int _x , int _y , std::vector<std::string> _pic_path , Window* _window);
	virtual void draw_enemy_in(double angle , int index_of_attack_mode);
	virtual std::string get_type() { return "Tesla"; }

private:
	virtual std::vector< std::vector<Rectangle> > init_clips();
};

#endif


#ifndef __Glue_CC__
#define __Glue_CC__

class Glue : public Tower
{
public:
	Glue(int _x , int _y , std::vector<std::string> _pic_path , Window* window);
	virtual void draw_enemy_in(double angle , int index_of_attack_mode);
	virtual std::string get_type() { return "Glue"; }
	virtual void level_up();
	int get_glue_influence_time() { return glue_influence_time; }

private:
	virtual std::vector<std::vector<Rectangle> > init_clips();
	int glue_influence_time;
	int delta_glue_influence_time;
};

#endif

