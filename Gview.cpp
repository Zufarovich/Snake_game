#include "Gview.hpp"

void GView::draw()
{

    print_name("grsnake");
}

void GView::print_name(std::string game_name)
{
    std::cout << "(GView)Game: " << game_name << std::endl  ;
}

