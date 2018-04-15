#include "Game.h"
#include "Snake.h"

using namespace sf;

Snake::Snake()
	:hasDirectionChanged(false)
{
	RectangleShape head;
	head.setFillColor(Color(60,100,255));
	head.setSize(Vector2f((float)Game::FoodSize, (float)Game::FoodSize));
	head.setPosition(Game::MapCenterX, Game::MapCenterY);

	SnakeBody.push_back(head);

	direction = DIR_UP;
}

/*Snake::Snake(&Snake)
{

}*/

Snake::~Snake()
{
}

Vector2f Snake::getDirection()
{
	Vector2f dir(0, 0);

	switch (direction)
	{
	case DIR_LEFT:
		dir.x = -1;
		break;

	case DIR_RIGHT:
		dir.x = 1;
		break;

	case DIR_UP:
		dir.y = -1;
		break;

	case DIR_DOWN:
		dir.y = 1;
		break;
	}
	hasDirectionChanged = false;
	return dir;
}

Vector2f Snake::getMovement()
{
	Vector2f direction = getDirection();
	Vector2f offset(direction.x * Game::FoodSize, direction.y * Game::FoodSize);
	return offset;
}

void Snake::Move()
{
	Vector2f prevPos = SnakeBody[0].getPosition();
	SnakeBody[0].move(getMovement());

	for (unsigned int i = 1; i < SnakeBody.size(); i++)
	{
		Vector2f tmp = SnakeBody[i].getPosition();
		SnakeBody[i].setPosition(prevPos);
		prevPos = tmp;
	}
}


void Snake::ChangeDirection(Direction dir)
{
	if (!hasDirectionChanged && abs(dir-direction)!=1)
	{
		direction = dir;
		hasDirectionChanged = true;
	}
}


void Snake::AddBodyPart()
{
	RectangleShape bodyPart(Vector2f((float)Game::FoodSize, (float)Game::FoodSize));

	setNewColor(bodyPart);

    /*bodyPart.setFillColor(Color::Green);
    bodyPart.setOutlineColor(Color(155,255,155));*/

	bodyPart.setOutlineThickness(-2.f);
	bodyPart.setSize(Vector2f((float)Game::FoodSize, (float)Game::FoodSize));
	bodyPart.setPosition(-32, -32);
	SnakeBody.push_back(bodyPart);
}

void Snake::setNewColor(RectangleShape & bodyPart)
{

    int n = rand() % 150 + 1;           //захотелось иметь 5 рандомных цветов, 150 - идеально подходящее число,которое не будет
    Color bodyPartColor;
    switch (int(n % 150) / 25)          //превышать в конце 125(Спасибо гуглКалькулятору и Гуглу:)).
    {
    case 0:
         bodyPartColor = Color(255, 10 * (n % 25), 0);
         break;
    case 1:
         bodyPartColor = Color(255 - 10 * (n % 25), 255, 0);
         break;
    case 2:
         bodyPartColor = Color(0, 255, 10 * (n % 25));
         break;
    case 3:
         bodyPartColor = Color(0, 255 - 10 * (n % 25), 255);
         break;
    case 4:
         bodyPartColor = Color(10 * (n % 25), 0, 255);
         break;
    case 5:
         bodyPartColor = Color(255, 0, 255 - 10 * (n % 25));
         break;
    }
    bodyPartColor.a = 60;
    bodyPart.setFillColor(bodyPartColor);
    bodyPartColor.a = 80;
    bodyPart.setOutlineColor(bodyPartColor);
}



bool Snake::IsSelfBitting()
{
	const Vector2f posAfterMove = SnakeBody[0].getPosition();
	const Vector2f *bodyPart;
	for (unsigned int i = 1; i < SnakeBody.size(); i++)
	{
		bodyPart = &SnakeBody[i].getPosition();
		if (posAfterMove == *bodyPart)
		{
			return true;
		}
	}

	return false;
}

FloatRect Snake::GetHeadFloatRect() const
{
	return SnakeBody[0].getGlobalBounds();
}

bool Snake::contains(const Vector2f& position)
{
	for (unsigned int i = 0; i < SnakeBody.size(); i++)
	{
		if (SnakeBody[i].getPosition() == position)
		{
			return true;
		}
	}
	return false;
}


void Snake::draw(RenderTarget & target, RenderStates states) const
{
	for (unsigned int i = 0; i < SnakeBody.size(); i++)
	{
		target.draw(SnakeBody[i]);
	}

}

Vector2f Snake::GetHeadPosition()
{
	return SnakeBody[0].getPosition();
}
