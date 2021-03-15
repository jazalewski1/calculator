#pragma once

#include "math/ValuePtr.hpp"

namespace math
{
class Operation
{
public:
	virtual ~Operation();

	virtual int execute() = 0;
};

class Addition : public Operation
{
public:
	Addition(ValuePtr lhs, ValuePtr rhs);

	int execute() override;

private:
	ValuePtr lhs, rhs;
};

class Multiplication : public Operation
{
public:
	Multiplication(ValuePtr lhs, ValuePtr rhs);

	int execute() override;

private:
	ValuePtr lhs, rhs;
};
} // namespace math