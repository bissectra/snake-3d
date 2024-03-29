//
// Created by atsocs on 25/04/2020.
//

#ifndef VECTOR_C14AC72190144CEC9580B7AF89EABAD3_H
#define VECTOR_C14AC72190144CEC9580B7AF89EABAD3_H

#include "../hardcoded/Constants.h"
#include "Direction.h"
#include "Position.h"
#include <vector>
#include <iostream>

class Vector
{
public:
	explicit Vector(int dimension = DIMENSION);
	explicit Vector(const Position &p);
	void centralize();
	std::vector<int> origin;
	Direction direction;
	[[nodiscard]] bool inSamePlaceAs(const Vector &v) const;
	[[nodiscard]] bool isOutOfBounds() const;
	Vector &operator+=(int value);
	Vector &operator-=(int value);
	Vector &operator++();
	Vector &operator--();
	friend Vector operator+(const Vector &v, int value);
	friend Vector operator+(int value, const Vector &v);

	friend std::ostream & operator<< (std::ostream & os, const Vector & vector);
};

Vector operator+(const Vector &v, int value);
Vector operator+(int value, const Vector &v);

std::ostream & operator<< (std::ostream & os, const Vector & vector);
#endif //VECTOR_C14AC72190144CEC9580B7AF89EABAD3_H
