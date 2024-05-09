#include "view.hpp"
#include "game.hpp"
#include "controller.hpp"
#include <getopt.h>
#include <unistd.h>
#include <iostream>

struct option long_options[] = {
	{"text_view",		 no_argument, 0, 't' },
	{"graphical_view",  no_argument, 0, 'g' },
	{"help", no_argument, 0, 'h'},
};

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		int  opt          = '\0';
		int  option_index = 0;
		View* view;
		bool continue_game = true;

		while((opt = getopt_long(argc, argv, "tg", long_options, &option_index)) != -1)
		{
			switch(opt){
			case 't':
				view = View::get_view("text_view");
				break;
			case 'g':
				view = View::get_view("g_view");
				break;	
			case 'h':
				std::cout << "use option -t(--text_view) to use text view and -g(--graphical_view) to use graphical view" << std::endl;
				continue_game = false;
				break;
			default:
				view = View::get_view("g_view");
				std::cout << "with command \"snake --help\" you can get additional information." << std::endl;
				continue_game = false;
				break;
			}
		}	

		if(!continue_game)
			return 0;
		
		Model model(*view);
		Control control(model, *(model.snakes.begin()));
		
		control.get_users_name();
		view->mainloop(model.snakes);

		return 0;
	}
	else
	{
		std::cout << "Incorrect usage with command \"snake --help\" you can get additional information." << std::endl;
	}
}
