#pragma once

#include "model/Calculator.hpp"
#include "model/Symbol.hpp"
#include <vector>
#include <stack>

namespace model
{
class RpnCalculator : public Calculator
{
public:
	RpnCalculator(std::vector<Symbol> symbols);

private:
	using Symbols = std::vector<Symbol>;
	using ValueStack = std::stack<int>;

	Symbols symbols;
	Symbols::const_iterator current_iterator;
	ValueStack value_stack;

	OperationResult do_calculate_next() override;

	bool do_has_finished() const override;

	void extract_and_insert_values();

	void process_operation();
};
} // namespace model