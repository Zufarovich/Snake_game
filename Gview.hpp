#pragma once
#include "view.hpp"
#include <SFML/Graphics.hpp>

#define RECTANGLE_SIZE 10

class GView : public View
{
    private:
    sf::RenderWindow window;
    sf::RectangleShape rectangle;
    sf::CircleShape head;
    sf::CircleShape body;
    sf::CircleShape rabbit_icon;

    public:
    GView();
    ~GView();
    virtual void print_name(std::string game_name);
    virtual void draw(std::list<Snake>& snakes, Herd_rabbits& herd);
    virtual void mainloop();
    void draw_border();
    void draw_rabbit(const Rabbit& rabbit);
    void draw_snake(const Snake& snake);
};
