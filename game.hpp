#pragma once
#include <string.h>
#include "game.hpp"
#include "view.hpp"
#include <list>

#define MAX_LENGTH 256

class Model
{
	private:
		View& view;
		char game_name[MAX_LENGTH] = {};

	public:
		Model(View& view_)
		:view(view_)
		{

		}

		std::list<Rabbit> rabbits;
		std::list<Snake> snakes;

		void change_name(char* buff); 
};

class Rabbit
{
	public:
	coord position;
}

class Snake
{
	public:
	int length;
	coord head;
	coord tail;
	std::list<coord> body;		
}
