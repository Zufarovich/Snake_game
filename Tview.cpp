#include "Tview.hpp"
#include <sys/ioctl.h>
#include <functional>
#include <poll.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <chrono>

#define BUFSIZE 128
#define FPS 5

TView::TView()
{
    struct termios term = {};
	tcgetattr(0, &term);

	term_old = term;

	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;

	tcsetattr(0, TCSANOW, &term);
}

TView::~TView()
{
    tcsetattr(0, TCSANOW, &term_old);
}

void TView::cls()
{
	std::cout << "\e[H\e[J";
}

void TView::draw(std::list<Snake>& snakes, Herd_rabbits& herd)
{
	cls();
	setcolor(0, 34);

	move((*view).win_xsize/2, (*view).win_ysize/2);

    if(!name_printed)
    {
	    print_name("snake");
        name_printed = true;
    }
	std::cout << std::flush;

	draw_border('|', 0, 0, (*view).win_xsize, 0);
	draw_border('|', 0, (*view).win_ysize, (*view).win_xsize, (*view).win_ysize);
	draw_border('-', (*view).win_xsize, 0, (*view).win_xsize, (*view).win_ysize);
	draw_border('-', 0, 0, 0, (*view).win_ysize);

    draw_herd(herd);

    for(const auto& snake: snakes)
        if(snake.length)
            draw_snake(snake);

    std::cout << std::flush;

    setcolor(0, 31);
    move(2, (*view).win_ysize - 10);
    std::cout<< "Score:" << snakes.front().length;

    setcolor(0, 34);
	move((*view).win_xsize, (*view).win_ysize);
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

void TView::draw_herd(const Herd_rabbits& herd)
{
    for(const Rabbit& rabbit : herd.rabbits)
    {
        move(rabbit.position.first, rabbit.position.second);
        std::cout << 'R';
    }
}

void TView::draw_snake(const Snake& snake)
{
    move(snake.head.first, snake.head.second);
    setcolor(0, 31);
    std::cout << 'O';

    setcolor(0, 32);
    for(const auto& body_elem: snake.body)
    {
        move(body_elem.first, body_elem.second);
        std::cout << 'o';
    }

    move(snake.tail.first, snake.tail.second);
    std::cout << '*';
    setcolor(0, 34);
}

void TView::mainloop(std::list<Snake>& snakes)
{
    struct pollfd input = {0, POLLIN, 0};
    char buf[BUFSIZE] = "";

    int timeout = 1000/FPS;
    int game_ended = 0;

	while(!game_ended)
	{
        struct winsize wins;
        ioctl(0, TIOCGWINSZ, &wins);

        (*view).win_xsize = wins.ws_row;
        (*view) .win_ysize = wins.ws_col;

        auto first_time = std::chrono::system_clock::now();
        int n = poll(&input, 1, timeout);
        auto second_time = std::chrono::system_clock::now();
        int time = std::chrono::duration_cast<std::chrono::milliseconds>(second_time - first_time).count();
        timeout -= time;

        if(n == 0 || timeout <= 0)
        {
            for(const auto& ontime: time_functions)
            {  
                ontime(&game_ended);
                timeout = 1000/FPS;
            }
        }

        if(n == 1)
        {
            int a = read(0, buf, sizeof(buf));
                
            for(int i = 0; i < a; i++)
            {
                for(const auto& onkey: key_functions)
                    onkey(buf[i]);
            }

            buf[0] = '\0';
	    }  
    }

    cls();

    move((*view).win_xsize/2, (*view).win_ysize/2);
    setcolor(0, 31);
    std::cout << "Score:" << (*snakes.begin()).length;
    move((*view).win_xsize, (*view).win_ysize);

    std::cout << std::flush;

    usleep(5000000);

    cls();
    std::cout << std::flush;
}