#include "math/Operation.hpp"
#include "math/ValuePtr.hpp"

namespace math
{
Operation::~Operation() {}

Addition::Addition(ValuePtr lhs, ValuePtr rhs) :
	lhs{lhs}, rhs{rhs}
{
}

int Addition::execute()
{
	return *lhs + *rhs;
};

Multiplication::Multiplication(ValuePtr lhs, ValuePtr rhs) :
	lhs{lhs}, rhs{rhs}
{
}

int Multiplication::execute()
{
	return *lhs * *rhs;
};
} // namespace math