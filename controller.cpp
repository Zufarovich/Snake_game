#include "controller.hpp"

void Control::get_users_name()
{
	char buff[MAX_LENGTH] = "snake";

	model.change_name(buff);	
}