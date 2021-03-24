#pragma once

#include "math/Value.hpp"
#include "model/Symbol.hpp"
#include <vector>
#include <stack>

namespace model
{
class Calculator
{
public:
	Calculator(Symbols symbols);

	using OperationResult = int;
	OperationResult calculate_next();

	bool has_finished() const;

private:
	using ValueStack = std::stack<math::Value>;

	Symbols symbols;
	Symbols::const_iterator current_iterator;
	ValueStack value_stack;

	math::Value read_value_from_stack() const;

	math::Value extract_value_from_stack();

	math::Value read_current_value_symbol() const;

	void process_operation(OperationType);
};
} // namespace model