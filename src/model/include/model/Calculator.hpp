#pragma once

#include "model/Symbol.hpp"
#include <vector>
#include <stack>

namespace model
{
class Calculator
{
public:
	using Symbols = std::vector<Symbol>;
	Calculator(Symbols symbols);

	using OperationResult = int;
	OperationResult calculate_next();

	bool has_finished() const;

private:
	using ValueStack = std::stack<int>;

	Symbols symbols;
	Symbols::const_iterator current_iterator;
	ValueStack value_stack;

	Value read_value_from_stack() const;

	Value extract_value_from_stack();

	Value read_current_value_symbol() const;

	void process_operation(OperationType);
};
} // namespace model