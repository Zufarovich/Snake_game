#include "view.hpp"
#include "game.hpp"
#include "controller.hpp"
#include <getopt.h>
#include <unistd.h>

struct option long_options[] = {
	{"text_view",		 no_argument, 0, 't' },
	{"graphical_view",  no_argument, 0, 'g' },
};

int main(int argc, char* argv[])
{
	int  opt          = '\0';
	int  option_index = 0;
	View* view;

	while((opt = getopt_long(argc, argv, "tg", long_options, &option_index)) != -1)
	{
		switch(opt){
		case 't':
			view = View::get_view("text_view");
			break;
		case 'g':
		    view = View::get_view("g_view");
			break;
		default:
			view = View::get_view("g_view");
			printf("with command \"snake --help\" you can get additional information.\n");
			break;
		}
	}	
	
	Model model(*view);
	Control control(model, *(model.snakes.begin()));
	
	control.get_users_name();
	view->mainloop();

	return 0;
}
