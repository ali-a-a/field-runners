#include<iostream>
#include<vector>

using namespace std;

vector<string> get_std_input()
{
	vector<string> positions;
	string save_input;
	
	while(getline(cin , save_input))
		positions.push_back(save_input);
	
	return positions;
}