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
	char game_name[MAX_LENGTH] = {};
	void generate_snakes();
	void snake_update(std::list<Snake>::iterator snake);

	public:
	View& view;
	std::list<Snake> snakes;
	Herd_rabbits herd;

	Model(View& view_)
	:view(view_)
	{
		generate_snakes();
		herd.create_herd(number_of_rabbits);
	}

	void check_eaten_rabbit(std::list<Snake>::iterator snake, Herd_rabbits& herd);
	void change_name(char* buff);
	void update_model();
};