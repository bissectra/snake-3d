//
// Created by atsocs on 25/04/2020.
//

#include "Game.h"

#include <utility>
#include <algorithm>

Game::Game() : Game(Snake{})
{

}

Game::Game(Snake snake)
		: score{0}, fruits{}, snake{std::move(snake)}
{
	generateFruit(Fruit{Position{{3, 4/*BOARD_SIZE / 2 - 1*/}}});
}

void Game::generateFruit(int count)
{
	for (int i = 0; i < count; ++i)
	{ generateRandomFruit(); }
}

void Game::generateFruit(const Fruit &f)
{
	if (isPositionOccupied(f.position))
	{ return; }
	fruits.push_back(f);
}

void Game::generateRandomFruit()
{
	Fruit f{};
	f.position.setRandom();
	while (isPositionOccupied(f.position))
	{
		f.position.setRandom();
	}
	fruits.push_back(f);
}

bool Game::isPositionOccupiedWithFruit(const Position &position) const
{
	for (const auto &fruit : fruits)
	{
		if (position == fruit.position)
		{
			return true;
		}
	}
	return false;
}

bool Game::isPositionOccupied(const Position &position) const
{
	return
			(isPositionOccupiedWithFruit(position)
			 || snake.isPositionOccupied(position));
}

void Game::draw() const
{
	drawFruits();
	snake.draw();
}

void Game::drawFruits() const
{
	for (const auto &fruit : fruits)
	{
		drawFruit(fruit.position.origin[0], fruit.position.origin[1]);
	}
}

void Game::drawFruit(int x, int y)
{
	DrawEllipse(BORDER_IN_PIXELS + FRUIT_PADDING_WIDTH_IN_PIXELS + FRUIT_RADIUS_H + x * CELL_WIDTH_IN_PIXELS,
	            BORDER_IN_PIXELS + FRUIT_PADDING_HEIGHT_IN_PIXELS + FRUIT_RADIUS_V + y * CELL_HEIGHT_IN_PIXELS,
	            FRUIT_RADIUS_H,
	            FRUIT_RADIUS_V, FRUIT_COLOR);
}

double Game::getSnakeSpeed()
{
	return snake.getSpeed();

}

void Game::searchForFruitsToEat(const Vector &snakeHeadNext)
{
	auto found = std::find_if(fruits.begin(), fruits.end(), [&](const Fruit &fruit)
	{
		return snakeHeadNext.inSamePlaceAs(Vector{fruit.position});
	});
	if (found != fruits.end())
	{
		eatFruit(found);
		fruits.erase(found);
		generateRandomFruit();
	}
}

void Game::moveSnake()
{
	Vector snakeHeadNext = (++snake.getHead());
	searchForFruitsToEat(snakeHeadNext);
	snake.move();
}

void Game::turnSnakeTo(Direction direction)
{
	Vector snakeHeadNext = snake.getHead();
	snakeHeadNext.direction = direction;
	++snakeHeadNext;
	searchForFruitsToEat(snakeHeadNext);
	snake.turnTo(direction);
}

void Game::eatFruit(std::list<Fruit>::iterator fruit)
{
	snake.eatFruit(*fruit);

	score += fruit->score;
	if (score < 0)
	{ score = 0; }
}

std::ostream &operator<<(std::ostream &os, const Game &game)
{
	using std::endl;
	os << "Game: " << "score " << game.score << endl;
	os << game.snake;
	os << "Fruits" << (game.fruits.empty() ? " is empty." : ": ") << endl;
	for (const auto &fruit : game.fruits)
	{
		os << "\t" << fruit << endl;
	}
	return os;
}

bool Game::alive() const
{
	return snake.isAlive();
}

int Game::getScore() const
{
	return score;
}
