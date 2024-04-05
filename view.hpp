#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <termios.h>
#include <functional>

using coord = std::pair<int,int>;
using on_key = std::function<void(const char d)>;
using on_time = std::function<void()>;

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
	void create_herd(int number_of_rabbits);
	std::list<Rabbit> rabbits;

	private:
};

class Snake
{
	public:
	void create_snake();
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
	private:
	struct termios term_old;

	public:
	static View* view;
	static View* get_view(std::string view_mode = "text_view");
	virtual ~View();
	View();
	virtual void print_name(std::string game_name) = 0;
	virtual void draw(std::list<Snake>& snakes, Herd_rabbits& herd) = 0;
	void set_onkey(on_key f);
    void set_ontimes(on_time f);
	virtual void mainloop() = 0;
	std::list<on_key> key_functions;
	std::list<on_time> time_functions;
};
