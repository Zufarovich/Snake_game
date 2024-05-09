#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <termios.h>
#include <functional>
#include <stdlib.h>

struct coord : public std::pair<int, int>
{
	using base = std::pair<int, int>;
	using base::base;

	int distance(const coord second_point)
	{
		return std::abs(second_point.first - first) + std::abs(second_point.second - second); 
	}
};

using on_key = std::function<void(const char d)>;
using on_time = std::function<void(int* game_ended)>;

class Rabbit
{
	public:
	void change_position();
	coord position;

	private:
};

class Herd_rabbits
{
	public:
	std::list<Rabbit> rabbits;

	private:
};

class Snake
{
	public:
	int length;
	coord head;
	coord tail;
	std::list<coord> body;

	void change_direction(const char d);

	int get_direction()
	{
		return direction;
	}

	private:
	int direction = 2;	
};

class View
{
	protected:
	struct termios term_old;

	public:
	int win_xsize;
	int win_ysize;
	static View* view;
	static View* get_view(std::string view_mode = "text_view");
	virtual ~View();
	View();
	virtual void print_name(std::string game_name) = 0;
	virtual void draw(std::list<Snake>& snakes, Herd_rabbits& herd) = 0;
	void set_onkey(on_key f);
    void set_ontimes(on_time f);
	virtual void mainloop(std::list<Snake>& snakes) = 0;
	std::list<on_key> key_functions;
	std::list<on_time> time_functions;
};
