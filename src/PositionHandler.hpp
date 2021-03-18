#include "rsdl.hpp"
#include<vector>
#include<iostream>

#ifndef __PositionHandler_CC__
#define __PositionHandler_CC__

class PositionHandler
{
public:
	static std::vector<Point> generate_places(std::vector<Point> points);
	static std::vector<int> s_to_i(int , std::vector<std::string>);
	static Point mouse_point_to_pos(Point mouse_point);
	static Point mouse_pos_to_point(Point mouse_point);
	static std::vector<Point> make_points_of_path(std::vector<Point> points);
	static void push_on_points_of_path(std::vector<Point>& path_points , Point p1 , Point p2 , std::string mode);
};

#endif