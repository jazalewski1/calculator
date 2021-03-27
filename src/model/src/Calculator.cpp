#include "math/Operation.hpp"
#include "model/Calculator.hpp"
#include "model/PostfixSymbol.hpp"
#include "util/Exception.hpp"
#include <variant>
#include <vector>

namespace model
{
namespace
{
math::OperationFunction convert_operation(PostfixSymbol::Type type)
{
	switch (type)
	{
		case PostfixSymbol::Type::ADDITION: return math::addition;
		case PostfixSymbol::Type::MULTIPLICATION: return math::multiplication;
	}
}
} // namespace

using Value = math::Value;
using OperationResult = Calculator::OperationResult;

Calculator::Calculator(std::vector<PostfixSymbol> input) : 
	symbols{input}, current_iterator{symbols.begin()}
{
}

OperationResult Calculator::calculate_next()
{
	if (has_finished())
	{
		throw util::BadAccessException{"Calculator has no more symbols!"};
	}

	while (not has_finished() and is_value(*current_iterator))
	{
		const auto value = read_current_value_symbol();
		value_stack.push(value);
		std::advance(current_iterator, 1);
	}

	if (not has_finished())
	{
		if (const auto& symbol = *current_iterator; is_operation_type(symbol))
		{
			const auto operation_type = get_type(symbol);
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
	const auto value = get_value(*current_iterator);
	return value;
}

void Calculator::process_operation(PostfixSymbol::Type operation_type)
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