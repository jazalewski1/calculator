#include "math/Operation.hpp"
#include "model/Calculator.hpp"
#include "model/Symbol.hpp"
#include "util/Exception.hpp"
#include <variant>
#include <vector>

namespace model
{
namespace
{
math::OperationFunction convert_operation(OperationType type)
{
	switch (type)
	{
		case OperationType::ADDITION: return math::addition;
		case OperationType::MULTIPLICATION: return math::multiplication;
	}
}
} // namespace

using Value = math::Value;
using OperationResult = Calculator::OperationResult;

Calculator::Calculator(std::vector<Symbol> input) : 
	symbols{input}, current_iterator{symbols.begin()}
{
}

OperationResult Calculator::calculate_next()
{
	if (has_finished())
	{
		throw util::BadAccessException{"Calculator has no more symbols!"};
	}

	while (not has_finished() and is_value(current_iterator->data))
	{
		const auto value = read_current_value_symbol();
		value_stack.push(value);
		std::advance(current_iterator, 1);
	}

	if (not has_finished())
	{
		if (const auto& variant = current_iterator->data; is_operation_type(variant))
		{
			const auto operation_type = get_operation_type(variant);
			process_operation(operation_type);
			std::advance(current_iterator, 1);
		}
	}


	return read_value_from_stack();
}

bool Calculator::has_finished() const
{
	return current_iterator == symbols.end();
}

Value Calculator::read_value_from_stack() const
{
	return value_stack.top();
}

Value Calculator::extract_value_from_stack()
{
	const auto output = read_value_from_stack();
	value_stack.pop();
	return output;
}

Value Calculator::read_current_value_symbol() const
{
	const auto& variant = current_iterator->data;
	const auto value = get_value(variant);
	return value;
}

void Calculator::process_operation(OperationType operation_type)
{
	if (value_stack.size() < 2)
	{
		throw util::InputErrorException{"Wrong RPN input - not enough values required for operation!"};
	}

	const auto value1 = extract_value_from_stack();
	const auto value2 = extract_value_from_stack();

	const auto operation = convert_operation(operation_type);
	const auto result = operation(value1, value2);
	value_stack.push(result);
}
} // namespace model