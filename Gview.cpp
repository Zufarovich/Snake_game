#include "Gview.hpp"
#include "view.hpp"
#include <unistd.h>

GView::GView()
    :window(sf::VideoMode(1600, 800), "Window Game"), rectangle(sf::Vector2f(10.f, 10.f)), head(10.f), body(10.f),rabbit_icon(10.f, 3)
{
    if(!font.loadFromFile("SEASRN__.ttf"))
        std::cout << "Error while loading font" << std::endl;

    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(0.f, 0.f);
    window.setFramerateLimit(10);
    rabbit_icon.setFillColor(sf::Color::White);
    rabbit_icon.setPosition(0.f, 0.f);
    head.setFillColor(sf::Color::Red);
    body.setFillColor(sf::Color::Green);
}

GView::~GView()
{

}

void GView::draw_border()
{
    for(int i  = 0; i < 1600/RECTANGLE_SIZE; i++)
    {
        rectangle.setPosition(i*RECTANGLE_SIZE, 0);
        window.draw(rectangle);
        rectangle.setPosition(i*RECTANGLE_SIZE, 800 - RECTANGLE_SIZE);
        window.draw(rectangle);
    }

    for(int i = 0; i < 800/RECTANGLE_SIZE; i++)
    {
        rectangle.setPosition(0, i*RECTANGLE_SIZE);
        window.draw(rectangle);
        rectangle.setPosition(1600 - RECTANGLE_SIZE, i*RECTANGLE_SIZE);
        window.draw(rectangle);
    }
}

void GView::draw_rabbit(const Rabbit& rabbit)
{
    rabbit_icon.setPosition(rabbit.position.second*10, rabbit.position.first*10);
    window.draw(rabbit_icon);
}

void GView::draw_snake(const Snake& snake)
{
    head.setPosition(snake.head.second*10, snake.head.first*10);
    window.draw(head);

    for(const auto& body_elem : snake.body)
    {
        body.setPosition(body_elem.second*10, body_elem.first*10);
        window.draw(body);
    }

    body.setPosition(snake.tail.second*10, snake.tail.first*10);
    window.draw(body);
}

void GView::draw(std::list<Snake>& snakes, Herd_rabbits& herd)
{
    draw_border();

    for(const auto& rabbit : herd.rabbits)
        draw_rabbit(rabbit);

    for(const auto& snake : snakes)
        draw_snake(snake);

    score.setFont(font);
    score.setString("Score:" + std::to_string(snakes.front().length));
    score.setCharacterSize(25);
    score.setFillColor(sf::Color::Red);
    score.setPosition(1400, 30);
    score.setStyle(sf::Text::Bold | sf::Text::Underlined);
    window.draw(score);

    window.display();
}

void GView::mainloop(std::list<Snake>& snakes)
{
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();

        window.clear();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            for(const auto& onkey: key_functions)
                    onkey('a');
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            for(const auto& onkey: key_functions)
                    onkey('s');
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            for(const auto& onkey: key_functions)
                    onkey('d');
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            for(const auto& onkey: key_functions)
                    onkey('w');
        }

        for(const auto& ontime : time_functions)
            ontime();

        auto snake = snakes.begin();

        if((*snake).check_self_intersection())
            break;
        
        snake++;

        window.display();
    }
}

void GView::print_name(std::string game_name)
{
    std::cout << "(GView)Game: " << game_name << std::endl  ;
}