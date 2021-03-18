#include "PositionHandler.hpp"
#include "rsdl.hpp"
#include "defines.hpp"
#include<vector>

using namespace std;


vector<Point> PositionHandler::generate_places(vector<Point> points)
{
	for(int i = 0 ; i < points.size() ; i++)
	{
		int pos_x = POS_X_0_0;
		int pos_y = POS_Y_0_0;
		for(int j = 0 ; j <= NUM_OF_COL ; j++)
		{
			if(points[i].x == j)
			{
				points[i].x = pos_x;
				break;
			}
			pos_x += SIZE_OF_SQUARE;
		}

		for(int j = 0 ; j <= NUM_OF_ROW ; j++)
		{
			if(points[i].y == j)
			{
				points[i].y = pos_y;
				break;
			}
			pos_y += SIZE_OF_SQUARE;
		}
	}

	return points;
}


vector<int> PositionHandler::s_to_i(int num_of_line , vector<string> stdin)
{
	vector<int> nums;
	string digit = "";
	for(int i = 0 ; i < stdin[num_of_line].length() ; i++)
	{
		while(stdin[num_of_line][i] != SPACE && i < stdin[num_of_line].length())
		{
			digit +=stdin[num_of_line][i];
			i++;
		}
		nums.push_back(stoi(digit));
		digit = "";
	}

	return nums;
}


Point PositionHandler::mouse_point_to_pos(Point mouse_point)
{
	vector<Point> points = generate_places(vector<Point>(1 , mouse_pos_to_point(mouse_point)));
	Point point = points[0];
	return point;
}


Point PositionHandler::mouse_pos_to_point(Point mouse_point)
{
	Point point;
	int pos_x = 121;
	int pos_y = 175;
	for(int i = 0 ; i <= NUM_OF_COL ; i++)
	{
		if(mouse_point.x >= pos_x && mouse_point.x <= pos_x + SIZE_OF_SQUARE)
		{
			point.x = i;
			break;
		}
		pos_x += SIZE_OF_SQUARE;
	}

	for(int j = 0 ; j <= NUM_OF_ROW ; j++)
	{
		if(mouse_point.y >= pos_y && mouse_point.y <= pos_y + SIZE_OF_SQUARE)
		{
			point.y = j;
			break;
		}
		pos_y += SIZE_OF_SQUARE;
	}

	return point;
}


vector<Point> PositionHandler::make_points_of_path(vector<Point> points)
{
	vector<Point> path_points;
	for(int i = 0 ; i < points.size() - 1 ; i++)
	{
		if(points[i].x == points[i + 1].x)
		{
			if(points[i + 1].y > points[i].y)
				push_on_points_of_path(path_points , points[i] , points[i + 1] , X);

			if(points[i + 1].y < points[i].y)
				push_on_points_of_path(path_points , points[i + 1] , points[i] , X);

		}

		if(points[i].y == points[i + 1].y)
		{
			if(points[i + 1].x > points[i].x)
				push_on_points_of_path(path_points , points[i] , points[i + 1] , Y);

			if(points[i + 1].x < points[i].x)
				push_on_points_of_path(path_points , points[i + 1] , points[i] , Y);
		}
	}

	path_points.push_back(Point(points.back().x , points.back().y));

	return path_points;
}


void PositionHandler::push_on_points_of_path(vector<Point>& path_points , Point p1 , Point p2 , string mode)
{
	if(mode == X)
		for(int i = p1.y ; i <= p2.y ; i++)
			path_points.push_back(Point(p1.x , i));

	if(mode == Y)
		for(int i = p1.x ; i <= p2.x ; i++)
			path_points.push_back(Point(i , p1.y));
}