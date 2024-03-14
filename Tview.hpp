#pragma once
#include "view.hpp"

class TView : public View
{
	private:
	void cls();
	void setcolor(int brightness, int color);
	void move(int x, int y);
	void draw_border(char symbol, int start_x, int start_y, int end_x, int end_y);

	public:
	virtual void print_name(std::string game_name);
	virtual void draw();
};
