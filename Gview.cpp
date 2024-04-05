#include "Gview.hpp"
#include "view.hpp"

void GView::draw(std::list<Snake>& snakes, Herd_rabbits& herd)
{

    print_name("grsnake");
}

void GView::print_name(std::string game_name)
{
    std::cout << "(GView)Game: " << game_name << std::endl  ;
}

void GView::mainloop()
{
    return;
}