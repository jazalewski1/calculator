#include "math/Operation.hpp"
#include "math/Value.hpp"
#include "model/Calculator.hpp"
#include "model/PostfixToken.hpp"
#include "util/Exception.hpp"
#include <variant>
#include <vector>

namespace model
{
using Value = math::Value;

namespace
{
Value execute_operation(PostfixToken::Operator type, const Value& lhs, const Value& rhs)
{
	const auto lhs_value = math::is_integer(lhs) ? math::get_integer(lhs) : math::get_double(lhs);
	const auto rhs_value = math::is_integer(rhs) ? math::get_integer(rhs) : math::get_double(rhs);
	switch (type)
	{
		case PostfixToken::Operator::SUBTRACTION: return math::subtraction(lhs_value, rhs_value);
		case PostfixToken::Operator::ADDITION: return math::addition(lhs_value, rhs_value);
		case PostfixToken::Operator::DIVISION: return math::division(lhs_value, rhs_value);
		case PostfixToken::Operator::MULTIPLICATION: return math::multiplication(lhs_value, rhs_value);
	}
}
} // namespace

Calculator::Calculator(std::vector<PostfixToken> input) : 
	tokens{input}, current_iterator{tokens.begin()}
{
}

using OperationResult = Calculator::OperationResult;
OperationResult Calculator::calculate_next()
{
	if (has_finished())
	{
		throw util::BadAccessException{"Calculator has no more tokens!"};
	}

	while (not has_finished() and is_value(*current_iterator))
	{
		const auto value = read_current_value_token();
		value_stack.push(value);
		std::advance(current_iterator, 1);
	}

	if (not has_finished())
	{
		if (const auto& token = *current_iterator; is_operator(token))
		{
			const auto operator_type = get_operator(token);
			process_operation(operator_type);
			std::advance(current_iterator, 1);
		}
	}

	return read_value_from_stack();
}

bool Calculator::has_finished() const
{
	return current_iterator == tokens.end();
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

Value Calculator::read_current_value_token() const
{
	const auto value = get_value(*current_iterator);
	return value;
}

void Calculator::process_operation(PostfixToken::Operator operation_type)
{
	if (value_stack.size() < 2)
	{
		throw util::InputErrorException{"Wrong RPN input - not enough values required for operation!"};
	}

	const auto value1 = extract_value_from_stack();
	const auto value2 = extract_value_from_stack();

	const auto result = execute_operation(operation_type, value2, value1);
	value_stack.push(result);
}
} // namespace model