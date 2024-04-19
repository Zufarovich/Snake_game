#include "view.hpp"
#include "game.hpp"
#include "controller.hpp"

int main()
{
	View* view = View::get_view("g_view");
	
	Model model(*view);
	Control control(model, *(model.snakes.begin()));
	
	control.get_users_name();
	view->mainloop();

	return 0;
}
