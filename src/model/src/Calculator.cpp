#include "math/Operation.hpp"
#include "model/OperationData.hpp"
#include "model/Calculator.hpp"
#include <iostream>

namespace model
{
namespace
{
std::shared_ptr<math::Operation> make_operation(OperationType type, std::shared_ptr<int> lhs, std::shared_ptr<int> rhs)
{
	switch (type) // TODO: refactor this switch
	{
		case OperationType::ADDITION:
			return std::make_shared<math::Addition>(lhs, rhs);
		case OperationType::MULTIPLICATION:
			return std::make_shared<math::Multiplication>(lhs, rhs);
	}
}
} // namespace

Calculator::Calculator(const OperationDataVector& input) :
	running_total{std::make_shared<int>(0)}
{
	const auto value_or_running = [this](const std::optional<int>& input) -> std::shared_ptr<int>
	{
		return input ? std::make_shared<int>(input.value()) : running_total;
	};

	operations.reserve(input.size());
	for (const auto& data : input)
	{
		const auto lhs = value_or_running(data.lhs);
		const auto rhs = value_or_running(data.rhs);
		operations.emplace_back(make_operation(data.type, lhs, rhs));
	}

	current_operation_iter = operations.begin();
}

Result Calculator::calculate_next()
{
	auto& current_operation = *current_operation_iter;
	const auto output = current_operation->execute();
	*running_total = output;
	std::advance(current_operation_iter, 1);
	return output;
}

Result Calculator::get_running_total() const
{
	return *running_total;
}

bool Calculator::finished() const
{
	return current_operation_iter == operations.end();
}
} // namespace model