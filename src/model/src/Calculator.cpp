#include "model/Calculator.hpp"
#include "model/Symbol.hpp"
#include "util/Exception.hpp"
#include <variant>
#include <vector>
#include <iostream>

namespace model
{
namespace
{
int execute_operation(OperationType type, int v1, int v2)
{
	switch (type)
	{
		case OperationType::ADDITION: return v1 + v2;
		case OperationType::MULTIPLICATION: return v1 * v2;
	}
}

bool is_value(const SymbolVariant& variant)
{
	return std::holds_alternative<Value>(variant);
}

bool is_operation_type(const SymbolVariant& variant)
{
	return std::holds_alternative<OperationType>(variant);
}
} // namespace

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

	extract_and_insert_values();

	process_operation();

	return value_stack.top();
}

bool Calculator::has_finished() const
{
	return current_iterator == symbols.end();
}

void Calculator::extract_and_insert_values()
{
	const auto has_more_value_symbols = [this](){ return not has_finished() and is_value(current_iterator->data); };

	while (has_more_value_symbols())
	{
		const auto& variant = current_iterator->data;
		const auto value = std::get<Value>(variant);
		value_stack.push(value);
		std::advance(current_iterator, 1);
	}
}

void Calculator::process_operation()
{
	if (not has_finished())
	{
		if (const auto& variant = current_iterator->data; is_operation_type(variant))
		{
			if (value_stack.size() < 2)
			{
				throw util::InputErrorException{"RPN input error - not enough values required for operation!"};
			}

			const auto operation_type = std::get<OperationType>(variant);
			const auto value1 = value_stack.top();
			value_stack.pop();
			const auto value2 = value_stack.top();
			value_stack.pop();
			const auto result = execute_operation(operation_type, value2, value1);
			value_stack.push(result);
		}
		std::advance(current_iterator, 1);
	}
}
} // namespace model