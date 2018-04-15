#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class Snake:
    public sf::Drawable
{
public:
    Snake();
   // Snake(&Snake);
    ~Snake();

    enum Direction
    {
        DIR_UP=1, DIR_DOWN=2, DIR_LEFT=4, DIR_RIGHT=5
    };

    FloatRect GetHeadFloatRect() const;
    Vector2f GetHeadPosition();

    void Move();
    void ChangeDirection(Direction dir);
    void AddBodyPart();
    bool IsSelfBitting();
    bool contains(const Vector2f& position);

    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
    std::vector <sf::RectangleShape> SnakeBody;
    Direction direction;
    bool hasDirectionChanged;

    Vector2f getMovement();
    Vector2f getDirection();
    void setNewColor(RectangleShape& bodyPart);
};

#endif // SNAKE_H_INCLUDED
