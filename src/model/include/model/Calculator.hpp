#pragma once

#include "math/Value.hpp"
#include "model/PostfixToken.hpp"
#include <vector>
#include <stack>

namespace model
{
class Calculator
{
public:
	Calculator(PostfixTokens tokens);

	using OperationResult = math::Value;
	OperationResult calculate_next();

	bool has_finished() const;

private:
	using ValueStack = std::stack<math::Value>;

	PostfixTokens tokens;
	PostfixTokens::const_iterator current_iterator;
	ValueStack value_stack;

	math::Value read_value_from_stack() const;

	math::Value extract_value_from_stack();

	math::Value read_current_value_token() const;

	void process_operation(PostfixToken::Operator);
};
} // namespace model