#pragma once
#include <string.h>
#include "view.hpp"
#include <list>

#define MAX_LENGTH 256
#define FPS 5 

const int number_of_rabbits = 5;

const coord direction_arr[4] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

class Model
{
	private:
	View& view;
	char game_name[MAX_LENGTH] = {};
	void generate_snakes();
	void snake_update();

	std::list<Snake> snakes;
	Herd_rabbits herd;

	public:
	Model(View& view_)
	:view(view_)
	{
		generate_snakes();
		herd.create_herd(number_of_rabbits);
	}


	void change_name(char* buff); 
};