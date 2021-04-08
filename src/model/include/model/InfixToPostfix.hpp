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
	using Value = math::Value;

	void process(Value);

	void process(InfixSymbol::Operator);

	void process(InfixSymbol::OpenPar);

	void process(InfixSymbol::ClosePar);

	void finish_process();

	std::stack<InfixSymbol> temporary_stack{};
	PostfixSymbols output{};
};
} // namespace model