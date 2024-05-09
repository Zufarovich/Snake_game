#include "Gview.hpp"
#include "view.hpp"
#include <unistd.h>

GView::GView()
    :window(sf::VideoMode(140*RECTANGLE_SIZE + 300, 80*RECTANGLE_SIZE), "Window Game"), rectangle(sf::Vector2f(10.f, 10.f)), head(10.f), body(10.f),rabbit_icon(10.f, 3)
{
    win_xsize = 78;
    win_ysize = 138;

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
    for(int i  = 0; i < win_ysize + 32; i++)
    {
        rectangle.setPosition(i*RECTANGLE_SIZE, 0);
        window.draw(rectangle);
        rectangle.setPosition(i*RECTANGLE_SIZE, win_xsize*RECTANGLE_SIZE + RECTANGLE_SIZE);
        window.draw(rectangle);
    }

    for(int i = 0; i < win_xsize + 2; i++)
    {
        rectangle.setPosition(0, i*RECTANGLE_SIZE);
        window.draw(rectangle);
        rectangle.setPosition(win_ysize*RECTANGLE_SIZE + RECTANGLE_SIZE, i*RECTANGLE_SIZE);
        window.draw(rectangle);
    }

    for(int i = 0; i < win_xsize + 2; i++)
    {
        rectangle.setPosition((win_ysize + 30)*RECTANGLE_SIZE + RECTANGLE_SIZE, i*RECTANGLE_SIZE);
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
        if((snake).length)
            draw_snake(snake);

    auto snake = snakes.begin();
    score.setFont(font);
    score.setFillColor(sf::Color::Red);
    score.setPosition((win_ysize + 3)*RECTANGLE_SIZE, 30);
    score.setStyle(sf::Text::Bold | sf::Text::Underlined);
    score.setString("Your score:" + std::to_string((*snake).length));
    score.setCharacterSize(20);
    window.draw(score);

    int bot_index = 1;
    snake++;

    for(snake; snake != snakes.end(); snake++)
    {
        score.setPosition((win_ysize + 3)*RECTANGLE_SIZE, 30 + bot_index*35);
        score.setString("Bot(" + std::to_string(bot_index) + "):" + std::to_string((*snake).length));
        window.draw(score);
        bot_index++;
    }

    window.display();
}

void GView::mainloop(std::list<Snake>& snakes)
{
    int game_ended = 0;

    while(window.isOpen() && !game_ended)
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
            ontime(&game_ended);

        window.display();
    }

    window.clear();

    auto snake = snakes.begin();
    int bot_index = 1;

    score.setFont(font);
    score.setString("Your score:" + std::to_string(snakes.front().length));
    score.setCharacterSize(25);
    score.setFillColor(sf::Color::Red);
    score.setPosition(800, 30);
    score.setStyle(sf::Text::Bold | sf::Text::Underlined);
    window.draw(score);

    snake++;

    for(snake; snake != snakes.end(); snake++)
    {
        score.setPosition(800, 30 + bot_index*35);
        score.setString("Bot(" + std::to_string(bot_index) + "):" + std::to_string((*snake).length));
        window.draw(score);
        bot_index++;
    }    

    window.display();

    usleep(3000000);
}

void GView::print_name(std::string game_name)
{
    std::cout << "(GView)Game: " << game_name << std::endl  ;
}