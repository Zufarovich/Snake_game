#pragma once
#include <iostream>
#include <string>
#include <utility>

using coord = std::pair<int,int>;

class View
{
	public:
	static View* view;
	static View* get_view(std::string view_mode = "text_view");
	virtual ~View();
	virtual void print_name(std::string game_name) = 0;
	virtual void draw() = 0;
};
