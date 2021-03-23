#pragma once

#include "model/Symbol.hpp"
#include <vector>
#include <stack>

namespace model
{
class Calculator
{
public:
	Calculator(std::vector<Symbol> symbols);

	using OperationResult = int;
	OperationResult calculate_next();

	bool has_finished() const;

private:
	using Symbols = std::vector<Symbol>;
	using ValueStack = std::stack<int>;

	Symbols symbols;
	Symbols::const_iterator current_iterator;
	ValueStack value_stack;

	void extract_and_insert_values();

	void process_operation();
};
} // namespace model