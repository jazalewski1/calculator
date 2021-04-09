#pragma once

#include "math/Value.hpp"
#include "model/InfixToken.hpp"
#include "model/PostfixToken.hpp"
#include <stack>

namespace model
{
class InfixToPostfixConverter
{
public:
	PostfixTokens convert(const InfixTokens& input);

private:
	using Value = math::Value;

	void process(Value);

	void process(InfixToken::Operator);

	void process(InfixToken::OpenPar);

	void process(InfixToken::ClosePar);

	void finish_process();

	std::stack<InfixToken> temporary_stack{};
	PostfixTokens output{};
};
} // namespace model