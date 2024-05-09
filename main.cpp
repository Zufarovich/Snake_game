#include "view.hpp"
#include "game.hpp"
#include "controller.hpp"
#include <getopt.h>
#include <unistd.h>
#include <iostream>

struct option long_options[] = {
	{"text_view",		 no_argument, NULL, 't' },
	{"graphical_view",  no_argument, NULL, 'g' },
	{"rabbits", required_argument, NULL, 'r'},
	{"bots", required_argument, NULL, 'b'},
	{"help", no_argument, NULL, 'h'},
	{NULL, 0, NULL, 0}
};

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		int  opt          = '\0';
		int  option_index = 0;
		View* view;
		bool continue_game = false;
		int number_of_rabbits = 5;
		int number_of_bots = 1;

		while((opt = getopt_long(argc, argv, "tgh::r:b:", long_options, &option_index)) != -1)
		{
			switch(opt){
			case 't':
				view = View::get_view("text_view");
				continue_game = true;
				break;
			case 'g':
				view = View::get_view("g_view");
				continue_game = true;
				break;	
			case 'r':
				if(optarg)
					number_of_rabbits = strtol(optarg, NULL, 10);
				else
					std::cout << "option -r requires argument(number_of_rabbits)" << std::endl;
				break;
			case 'b':
				if(optarg)
					number_of_bots = strtol(optarg, NULL, 10);
				else
					std::cout << "option -b requres argument(number_of_bots)" << std::endl;
				break;
			case 'h':
				std::cout << "use option -t(--text_view) to use text view and -g(--graphical_view) to use graphical view" << std::endl;
				std::cout << "option -r and num_of_rabbits to set number of rabbits" << std::endl;
				std::cout << "option -b and num_of_bots to set number of bots" << std::endl;
				break;
			default:
				view = View::get_view("g_view");
				std::cout << "with command \"snake --help\" you can get additional information." << std::endl;
				break;
			}
		}	

		if(!continue_game)
		{
			std::cout << "with command \"snake --help\" you can get additional information." << std::endl;
			return 0;
		}
		
		Model model(*view, number_of_rabbits, number_of_bots);
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
