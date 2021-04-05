#pragma once

#include "math/Value.hpp"
#include "model/InfixSymbol.hpp"
#include "model/PostfixSymbol.hpp"
#include <stack>

namespace model
{
class InfixToPostfixConverter
{
public:
	PostfixSymbols convert(const InfixSymbols& input);

private:
	using Operator = InfixSymbol::Operator;
	using Value = math::Value;

	void process(Value);

	void process(Operator);

	void finish_process();

	std::stack<Operator> operator_stack{};
	PostfixSymbols output{};
};
} // namespace model