#pragma once
#include "view.hpp"

class GView : public View
{
    public:
    virtual void print_name(std::string game_name);
    virtual void draw(std::list<Snake>& snakes, Herd_rabbits& herd);
};
