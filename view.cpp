#include "view.hpp"
#include "Tview.hpp"
#include "Gview.hpp"
#include <termios.h>
#include <sys/ioctl.h>

View* View::view = NULL;

View* View::get_view(std::string view_mode)
{
	if(view)
		return view;

	if (view_mode == "text_view")
		view = new TView;
	else
		view = new GView;

	return view;
}

View::View()
{
	struct termios term = {};
	tcgetattr(0, &term);

	term_old = term;

	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;

	tcsetattr(0, TCSANOW, &term);
}

void Snake::change_direction(const char d)
{
	switch(d)
	{
		case 'w':
			if(direction != 1)
				direction = 0;
			break;

		case 's':
			if(direction != 0)
				direction = 1;
			break;

		case 'd':
			if(direction != 3)
				direction = 2;
			break;

		case 'a':
			if(direction != 2)
				direction = 3;
			break;
	}
}

View::~View()
{

}

void View::set_onkey(on_key f)
{
	key_functions.push_back(f);
}

void View::set_ontimes(on_time f)
{
	time_functions.push_back(f);
}