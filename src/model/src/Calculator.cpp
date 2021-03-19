#include "math/Operation.hpp"
#include "model/OperationData.hpp"
#include "model/Calculator.hpp"
#include <memory>

namespace model
{
namespace
{
std::shared_ptr<math::Operation> make_operation(OperationType type)
{
	switch (type) // TODO: refactor this switch
	{
		case OperationType::ADDITION:
			return std::make_shared<math::Addition>();
		case OperationType::MULTIPLICATION:
			return std::make_shared<math::Multiplication>();
	}
}
} // namespace

void Calculator::calculate(const OperationData& input)
{
	const auto lhs = input.lhs.value_or(running_total);
	const auto rhs = input.rhs.value_or(running_total);
	const auto operation = make_operation(input.type);

	running_total = operation->execute(lhs, rhs);
}

Calculator::Result Calculator::get_running_total() const
{
	return running_total;
}
} // namespace model