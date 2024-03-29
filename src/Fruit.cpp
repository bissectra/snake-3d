//
// Created by atsocs on 25/04/2020.
//

#include "Fruit.h"
#include <cassert>
#include <utility>

Fruit::Fruit(Position  p, int score, int healthBenefit)
		: eaten{false}, position{std::move(p)}, score{score}, hp{healthBenefit}
{
//	position.setRandom();
	assert(!Vector{position}.isOutOfBounds());
}

void Fruit::eat()
{
	assert(!eaten);
	eaten = true;
}

std::ostream &operator<<(std::ostream &os, const Fruit &fruit)
{
	os << (fruit.eaten ? "eaten" : "not eaten") << ", at " << fruit.position << ", hp += " << fruit.hp
	   << ", score += " << fruit.score;
	return os;
}