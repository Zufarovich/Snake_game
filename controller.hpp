#pragma once
#include <iostream>
#include "game.hpp"

#define MAX_LENGTH 256

class Control
{
	private:
	Model& model;

	public:
	Control(Model& model_)
	:model(model_)
	{

	}
	
	void get_users_name();
};
