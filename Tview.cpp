#include "Tview.hpp"
#include <sys/ioctl.h>

void TView::cls()
{
	std::cout << "\e[H\e[J";
}

void TView::draw()
{
	cls();
	setcolor(0, 34);

	struct winsize wins;
	ioctl(0, TIOCGWINSZ, &wins);

	int win_xsize = wins.ws_row;
	int win_ysize = wins.ws_col;

	move(win_xsize/2, win_ysize/2);
	print_name("snake");
	std::cout << std::flush;

	draw_border('#', 0, 0, win_xsize, 0);
	draw_border('#', 0, 0, win_xsize, win_ysize);
	draw_border('#', win_xsize, 0, win_xsize, win_ysize);
	draw_border('#', 0, 0, 0, win_ysize);

	move(win_xsize, win_ysize);
	std::cout << std::flush;
}

void TView::draw_border(char symbol, int start_x, int start_y, int end_x, int end_y)
{
	move(start_x, start_y);

	if(start_x == end_x) // horizontal wall
    {
        for(int i = start_y; i < end_y; i++)
        {
            std::cout << symbol;
            move(start_x, i+1);
        }
    }

    if(start_y == end_y) //vertical wall
    {
        for(int i = start_x; i < end_x; i++)
        {
            std::cout << symbol;
            move(i+1, start_y);
        }
    }
}

void TView::setcolor(int brightness, int color)
{
    std::cout << "\e[" << brightness << ";" << color << "m";
}


void TView::move(int x, int y)
{
    std::cout << "\e[" << x << ";" << y << "H";
}

void TView::print_name(std::string game_name)
{
    std::cout << "Game: " << game_name;
}
