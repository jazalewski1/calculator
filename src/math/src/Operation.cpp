#include "math/Operation.hpp"

namespace math
{
Operation::~Operation() {}

int Addition::execute(Value lhs, Value rhs)
{
	return lhs + rhs;
};

int Multiplication::execute(Value lhs, Value rhs)
{
	return lhs * rhs;
};
} // namespace math