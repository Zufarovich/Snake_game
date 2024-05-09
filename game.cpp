#include "game.hpp"
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

int win_xsize;
int win_ysize;

void Model::change_name(char* buff)
{
	strncpy(game_name, buff, MAX_LENGTH);
	view.draw(snakes, herd);
	usleep(3000000);
}

void Rabbit::change_position()
{
	struct winsize wins;
	ioctl(0, TIOCGWINSZ, &wins);

	win_xsize = wins.ws_row;
	win_ysize = wins.ws_col;

	position.first = 1 + rand() % (win_xsize - 2);
	position.second = 1 + rand() % (win_ysize - 2);
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

void Snake::create_bot(Snake& previous)
{
	length = 4;

	head.first = previous.head.first;
	head.second = previous.head.second;

	while((head.first == previous.head.first) || (head.second == previous.head.second))
	{
		head.first = 2 + rand() % (win_xsize - 2);
		head.second = 2 + rand() % (win_ysize - 2);
	}

	coord body_1 = {head.first, head.second - 1};
	body.push_back(body_1);

	body_1 = {head.first, head.second - 2};
	body.push_back(body_1);

	tail.first = head.first;
	tail.second = head.second - 3;
}

int Snake::check_self_intersection()
{
	for(auto body_elem = body.begin(); body_elem != body.end(); body_elem++)
	{
		if(head == (*body_elem))
			return 1;
	}

	if((head.first == 1) || (head.first == win_xsize) || (head.second == 1) || (head.second == win_ysize))
		return 1;

	return 0;
}

int Model::check_enemy_intersection(std::list<Snake>::iterator candidate, std::list<Snake>::iterator enemy_snake)
{
	
	if((*enemy_snake).head == (*candidate).head)
		return 1;

	for(auto body_elem = (*enemy_snake).body.begin(); body_elem != (*enemy_snake).body.end(); body_elem++)
	{
		if((*candidate).head == (*body_elem))
			return 1;
	}

	if((*enemy_snake).tail == (*candidate).head)
		return 1;

	return 0;
}

void Model::generate_snakes()
{
	Snake snake;
	Snake bot;
	snake.create_snake();
	bot.create_bot(snake);

	snakes.push_back(snake);
	snakes.push_back(bot);
}
 
void Model::snake_update(std::list<Snake>::iterator snake)
{
	coord last_head = {(*snake).head.first, (*snake).head.second};
	
	(*snake).head.first += direction_arr[(*snake).get_direction()].first;
	(*snake).head.second += direction_arr[(*snake).get_direction()].second;

	(*snake).body.push_front(last_head);
	(*snake).tail = (*snake).body.back();
	(*snake).body.pop_back();
}

void Model::bot_update(std::list<Snake>::iterator snake, Herd_rabbits& herd)
{
	if((*snake).length)
	{
		int min_distance = INT_MAX;
		Rabbit closest;

		for(auto rabbit = herd.rabbits.begin(); rabbit != herd.rabbits.end(); rabbit++)
		{
			int save = (*snake).head.distance(rabbit->position);

			if(min_distance > save)
			{
				min_distance = save;
				closest.position.first = (*rabbit).position.first;
				closest.position.second = (*rabbit).position.second;
			}
		}

		if(closest.position.first != (*snake).head.first)
		{
			if((*snake).head.first < closest.position.first)
			{
				if((*snake).get_direction() != 0)
					(*snake).change_direction('s');
				else
					(*snake).change_direction('d');
			}
			else
			{
				if((*snake).get_direction() != 1)
					(*snake).change_direction('w');
				else
					(*snake).change_direction('a');
			}
		}
		else
		{
			if((*snake).head.second != closest.position.second)
			{
				if((*snake).head.second < closest.position.second)
				{
					if((*snake).get_direction() != 3)
						(*snake).change_direction('d');
					else
						(*snake).change_direction('s');
				}
				else
				{
					if((*snake).get_direction() != 2)
						(*snake).change_direction('a');
					else
						(*snake).change_direction('w');
				}
			}
		}

		coord last_head = {(*snake).head.first, (*snake).head.second};
		
		(*snake).head.first += direction_arr[(*snake).get_direction()].first;
		(*snake).head.second += direction_arr[(*snake).get_direction()].second;

		(*snake).body.push_front(last_head);
		(*snake).tail = (*snake).body.back();
		(*snake).body.pop_back();
	}
}

void Model::check_eaten_rabbit(std::list<Snake>::iterator snake, Herd_rabbits& herd)
{
	for(auto rabbit = herd.rabbits.begin(); rabbit != herd.rabbits.end(); rabbit++)
	{
		if((*rabbit).position == (*snake).head) 
		{
			(*rabbit).change_position();

			(*snake).length++;
			coord buf_coord = {0, 0};
			(*snake).body.push_back(buf_coord);
		}
	}
}

void Model::update_model()
{
	int i = 0;

	for(auto snake = snakes.begin(); snake != snakes.end(); snake++)
	{
		if(!i)
		{
			snake_update(snake);
			check_eaten_rabbit(snake, herd);
			i++;
		}
		else
		{
			bot_update(snake, herd);
			check_eaten_rabbit(snake, herd);
		}
	}

	view.draw(snakes, herd);
}