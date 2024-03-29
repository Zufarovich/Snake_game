#include "game.hpp"
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

void Model::change_name(char* buff)
{
	strncpy(game_name, buff, MAX_LENGTH);
	view.draw(snakes, herd);
	usleep(3000000);

	while(1)
	{
		snake_update();
		view.draw(snakes, herd);
		usleep(1000000/FPS);
	}
}

void Rabbit::change_position()
{
	struct winsize wins;
	ioctl(0, TIOCGWINSZ, &wins);

	int win_xsize = wins.ws_row;
	int win_ysize = wins.ws_col;

	position.first = 1 + rand() % (win_xsize - 1);
	position.second = 1 + rand() % (win_ysize - 1);
}

void Herd_rabbits::create_herd(int number_of_rabbits)
{
	Rabbit rabbit;

	srand(time(NULL));

	for(int i = 0; i < number_of_rabbits; i++)
	{
		rabbit.change_position();
		rabbits.push_back(rabbit);
	}
}

void Snake::create_snake()
{
	length = 4;

	head.first = 20;
	head.second = 12;

	coord body_1 = {20, 11};
	body.push_back(body_1);

	body_1 = {20, 10};
	body.push_back(body_1);

	tail.first = 20;
	tail.second = 9;
}

void Model::generate_snakes()
{
	Snake snake;
	snake.create_snake();

	snakes.push_back(snake);
}
 
void Model::snake_update()
{
	for(auto snake = snakes.begin(); snake != snakes.end(); snake++)
	{		
		coord last_head = {(*snake).head.first, (*snake).head.second};
		
		(*snake).head.first += direction_arr[(*snake).get_direction()].first;
		(*snake).head.second += direction_arr[(*snake).get_direction()].second;

		(*snake).body.push_front(last_head);
		(*snake).tail = (*snake).body.back();
		(*snake).body.pop_back();
	}
}