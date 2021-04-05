#pragma once

#include "math/Value.hpp"
#include "model/PostfixSymbol.hpp"
#include <vector>
#include <stack>

namespace model
{
class Calculator
{
public:
	Calculator(PostfixSymbols symbols);

	using OperationResult = math::Value;
	OperationResult calculate_next();

	bool has_finished() const;

private:
	using ValueStack = std::stack<math::Value>;

	PostfixSymbols symbols;
	PostfixSymbols::const_iterator current_iterator;
	ValueStack value_stack;

	math::Value read_value_from_stack() const;

	math::Value extract_value_from_stack();

	math::Value read_current_value_symbol() const;

	void process_operation(PostfixSymbol::Operator);
};
} // namespace model