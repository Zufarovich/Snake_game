#pragma once
#include "view.hpp"

class TView : public View
{
	private:
	bool name_printed = false;
	void cls();
	void setcolor(int brightness, int color);
	void move(int x, int y);
	void draw_border(char symbol, int start_x, int start_y, int end_x, int end_y);
	void draw_snake(const Snake& snake);
	void draw_herd(const Herd_rabbits& herd);

	public:
	virtual void print_name(std::string game_name);
	virtual void draw(std::list<Snake>& snakes, Herd_rabbits& herd);
	virtual void mainloop();
};
