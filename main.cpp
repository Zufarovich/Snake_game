#include "view.hpp"
#include "game.hpp"
#include "controller.hpp"

int main()
{
	View* view = View::get_view("text_view");
	
	Model model(*view);
	Control control(model);
	
	control.get_users_name();

	return 0;
}
