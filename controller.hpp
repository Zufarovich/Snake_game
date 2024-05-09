#pragma once
#include <iostream>
#include "game.hpp"

#define MAX_LENGTH 256

class Control
{
	private:
	Model& model;
	Snake& snake;

	public:
	Control(Model& model_, Snake& snake_);

	void check_intersections(int* game_ended);
	void get_users_name();
	void pressed_key(const char key);
	void timer(int* game_ended);
};
