#pragma once

namespace math
{
using Value = int;

class Operation
{
public:
	virtual ~Operation();

	virtual int execute(Value, Value) = 0;
};

class Addition : public Operation
{
public:
	int execute(Value, Value) override;
};

class Multiplication : public Operation
{
public:
	int execute(Value, Value) override;
};
} // namespace math