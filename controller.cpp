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

	auto func_time = std::bind(&Control::timer, this);
	model.view.set_ontimes(func_time);
}

void Control::pressed_key(const char key)
{
	snake.change_direction(key);
}

void Control::timer()
{
	model.update_model();
}