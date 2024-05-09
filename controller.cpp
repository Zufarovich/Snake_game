#include "controller.hpp"

void Control::get_users_name()
{
	char buff[MAX_LENGTH] = "snake";

	model.change_name(buff);	
}

Control::Control(Model& model_, Snake& snake)
				: model(model_), snake(snake)
{
	auto func_key = std::bind(&Control::pressed_key, this, std::placeholders::_1);
	model.view.set_onkey(func_key);

	auto func_time = std::bind(&Control::timer, this, std::placeholders::_1);
	model.view.set_ontimes(func_time);

	auto func_check = std::bind(&Control::check_intersections, this, std::placeholders::_1);
	model.view.set_ontimes(func_check);
}

void Control::pressed_key(const char key)
{
	snake.change_direction(key);
}

void Control::timer(int* game_ended)
{
	model.update_model();
}

void Control::check_intersections(int* game_ended)
{
	auto snake = model.snakes.begin();

	if(model.check_self_intersection(snake))
        *game_ended = 1;
        
	snake++;

	for(snake; snake != model.snakes.end(); snake++)
	{
		if(model.check_self_intersection(snake))
		{
			(*snake).length = 0;
		}
	}
}