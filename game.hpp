#pragma once
#include <string.h>
#include "view.hpp"
#include <list>

#define MAX_LENGTH 256
#define FPS 5 

const coord direction_arr[4] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

class Model
{
	private:
	char game_name[MAX_LENGTH] = {};
	void generate_snakes();
	void snake_update(std::list<Snake>::iterator snake);
	void create_bot();
	void create_snake();
	void create_herd(int number_of_rabbits);

	public:
	View& view;
	std::list<Snake> snakes;
	Herd_rabbits herd;

	Model(View& view_, int number_of_rabbits)
	:view(view_)
	{
		generate_snakes();
		create_herd(number_of_rabbits);
	}

	int  check_enemy_intersection(std::list<Snake>::iterator candidate, std::list<Snake>::iterator enemy_snake);
	void check_eaten_rabbit(std::list<Snake>::iterator snake, Herd_rabbits& herd);
	void bot_update(std::list<Snake>::iterator snake, Herd_rabbits& herd);
	int  check_self_intersection(std::list<Snake>::iterator snake);
	void change_name(char* buff);
	void update_model();
};