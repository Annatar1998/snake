#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "Snake.h"

using namespace sf;
class Game
{
public:
    Game();
    ~Game();

    void RunGame();

    static const double ScreenWidth = 512;
    static const double ScreenHeight = 512;
    static const int FoodSize = 32;
    static const int MapCenterX = 256;
    static const int MapCenterY = 224;
private:
    RenderWindow window;
    Snake  snake;
    RectangleShape food;
    Font font;
    sf::Clock clock;

    std::vector <RectangleShape> map;

    FloatRect mapBounds;

    bool drawSnake;

    Vector2f getRandomPos();
    Color getRandomColor();

    void createMap();
    void setFoodFillColor();


    int PlayerScore;
    void Score();

};


#endif // GAME_H_INCLUDED
