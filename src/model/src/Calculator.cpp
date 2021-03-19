#include "math/Operation.hpp"
#include "model/OperationData.hpp"
#include "model/Calculator.hpp"
#include <memory>

namespace model
{
namespace
{
math::OperationFunction make_operation(OperationType type)
{
	switch (type) // TODO: refactor this switch
	{
		case OperationType::ADDITION:
			return math::addition;
		case OperationType::MULTIPLICATION:
			return math::multiplication;
	}
}
} // namespace

void Calculator::calculate(const OperationData& input)
{
	const auto lhs = input.lhs.value_or(running_total);
	const auto rhs = input.rhs.value_or(running_total);
	const auto operation = make_operation(input.type);

	running_total = operation(lhs, rhs);
}

Calculator::Result Calculator::get_running_total() const
{
	return running_total;
}
} // namespace model