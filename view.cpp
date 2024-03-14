#include "view.hpp"
#include "Tview.hpp"
#include "Gview.hpp"

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

View::~View()
{

}
