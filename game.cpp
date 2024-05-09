#include "game.hpp"
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

void Model::change_name(char* buff)
{
	strncpy(game_name, buff, MAX_LENGTH);
	view.draw(snakes, herd);
	usleep(3000000);
}

void Model::create_herd(int number_of_rabbits)
{
	Rabbit rabbit;

	srand(time(NULL));

	for(int i = 0; i < number_of_rabbits; i++)
	{
		rabbit.position.first = 2 + rand() % (view.win_xsize - 2);
		rabbit.position.second = 2 + rand() % (view.win_ysize - 2);
		herd.rabbits.push_back(rabbit);
	}
}

void Model::create_snake()
{
	Snake snake;
	snake.length = 4;

	snake.head.first = 20;
	snake.head.second = 12;

	coord body_1 = {20, 11};
	snake.body.push_back(body_1);

	body_1 = {20, 10};
	snake.body.push_back(body_1);

	snake.tail.first = 20;
	snake.tail.second = 9;

	snakes.push_back(snake);
}

void Model::create_bot()
{
	Snake snake;
	snake.length = 4;

	snake.head.first = (*snakes.end()).head.first;
	snake.head.second = (*snakes.end()).head.second;

	while((snake.head.first == (*snakes.end()).head.first) || (snake.head.second == (*snakes.end()).head.second))
	{
		snake.head.first = 2 + rand() % (view.win_xsize - 2);
		snake.head.second = 2 + rand() % (view.win_ysize - 2);
	} 

	coord body_1 = {snake.head.first, snake.head.second - 1};
	snake.body.push_back(body_1);

	body_1 = {snake.head.first, snake.head.second - 2};
	snake.body.push_back(body_1);

	snake.tail.first = snake.head.first;
	snake.tail.second = snake.head.second - 3;

	snakes.push_back(snake);
}

int Model::check_self_intersection(std::list<Snake>::iterator snake)
{
	for(auto body_elem = (*snake).body.begin(); body_elem != (*snake).body.end(); body_elem++)
	{
		if((*snake).head == (*body_elem))
			return 1;
	}

	if(((*snake).head.first == 1) || ((*snake).head.first == view.win_xsize) || ((*snake).head.second == 1) || ((*snake).head.second == view.win_ysize))
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

void Model::generate_snakes(int number_of_bots)
{
	create_snake();
	
	for(int i = 0; i < number_of_bots; i++)
		create_bot();
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
			(*rabbit).position.first = 2 + rand() % (view.win_xsize - 2);
			(*rabbit).position.second = 2 + rand() % (view.win_ysize - 2);

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