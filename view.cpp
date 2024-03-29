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
	struct winsize wins;
	ioctl(0, TIOCGWINSZ, &wins);

	int win_xsize = wins.ws_row;
	int win_ysize = wins.ws_col;

	struct termios term = {};
	int a = tcgetattr(0, &term);

	term_old = term;

	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;

	a = tcsetattr(0, TCSANOW, &term);
}

View::~View()
{

}

void View::mainloop()
{
	std::function<void()>;
}