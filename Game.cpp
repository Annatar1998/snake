#include "Game.h"
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace sf;

Game::Game(): drawSnake(true),PlayerScore(1)
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(VideoMode(ScreenWidth,ScreenHeight),"Snake",Style::Close,settings);
    window.setFramerateLimit(120);



    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "No font found";
    }
}
Game::~Game()
{

}

Vector2f Game::getRandomPos()
{
    srand((unsigned int)time(NULL));

    Vector2i max(ScreenWidth/FoodSize,ScreenHeight/FoodSize);
    Vector2f RandomPos;

    do
    {
        RandomPos = Vector2f (float(rand()%max.x),float(rand()% max.y));
    }
    while(snake.contains(RandomPos*(float)FoodSize));

    return RandomPos;
}

void Game::createMap()
{
    for(int i = 0; i < ScreenWidth/FoodSize; i++)
        for(int j = 0; j < ScreenHeight/FoodSize; j++)
        {
            RectangleShape mapSquare;

            mapSquare.setSize(Vector2f((float)FoodSize,(float)FoodSize));
            mapSquare.setFillColor(Color::Black);
            mapSquare.setOutlineThickness(-1.f);
            mapSquare.setOutlineColor(Color(55,55,55));
            mapSquare.setPosition(Vector2f(i*(float)FoodSize,j*(float)FoodSize));

            map.push_back(mapSquare);
        }
}

void Game::setFoodFillColor()
{
    food.setFillColor(getRandomColor());
}

Color Game::getRandomColor()
{
    int n = rand() % 150 + 1;           //захотелось иметь 5 рандомных цветов, 150 - идеально подходящее число,которое не будет
    Color foodColor;
    switch (int(n % 150) / 25)          //превышать в конце 125(Спасибо гуглКалькулятору и Гуглу:)).
    {
    case 0:
        foodColor = Color(255, 10 * (n % 25), 0);
        break;
    case 1:
        foodColor = Color(255 - 10 * (n % 25), 255, 0);
        break;
    case 2:
        foodColor = Color(0, 255, 10 * (n % 25));
        break;
    case 3:
        foodColor = Color(0, 255 - 10 * (n % 25), 255);
        break;
    case 4:
        foodColor = Color(10 * (n % 25), 0, 255);
        break;
    case 5:
        foodColor = Color(255, 0, 255 - 10 * (n % 25));
        break;
    }
    return foodColor;
}

void Game::RunGame()
{
    createMap();

    food.setSize(Vector2f((float)FoodSize,(float)FoodSize));
    food.setPosition(getRandomPos()*(float)FoodSize);
    setFoodFillColor();

    mapBounds = FloatRect(0,0,ScreenWidth,ScreenHeight);

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                snake.ChangeDirection(Snake::DIR_UP);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                snake.ChangeDirection(Snake::DIR_DOWN);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                snake.ChangeDirection(Snake::DIR_LEFT);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                snake.ChangeDirection(Snake::DIR_RIGHT);
            }
        }



        window.clear();

        for(unsigned int i = 0; i < map.size(); i++)
            window.draw(map[i]);

        window.draw(food);

        window.draw(snake);

        if(snake.IsSelfBitting() || !mapBounds.contains(snake.GetHeadPosition() ))
        {
            window.capture();
            window.close();
            Score();
        }
        if(clock.getElapsedTime().asMilliseconds()>125)
        {
            setFoodFillColor();
            snake.Move();

            if(snake.GetHeadFloatRect() == food.getGlobalBounds())
            {
                food.setPosition(getRandomPos()*(float)FoodSize);
                snake.AddBodyPart();
                PlayerScore++;
            }
            clock.restart();
        }
        window.display();

    }

}
void Game::Score()
{
    Text score;
    std::ostringstream PlayerScoreString;

    PlayerScoreString << PlayerScore;

    score.setFont(font);
    score.setString("Your Score is: "+PlayerScoreString.str());
    score.setPosition(ScreenWidth/4,ScreenHeight/2);
    score.setCharacterSize(32);
    score.setColor(Color::Red);
    window.create(VideoMode(ScreenWidth,ScreenHeight),"Score",Style::Close);

    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }
        window.draw(score);
        window.display();
    }
}
