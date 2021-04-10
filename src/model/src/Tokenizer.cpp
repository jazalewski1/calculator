#include "model/Tokenizer.hpp"
#include <cctype>
#include <string_view>

namespace
{
bool is_digit(char c) { return std::isdigit(c); }
bool is_operator(char c) { return std::string_view{"+-*/"}.find(c) != std::string_view::npos; }
bool is_open_parenthesis(char c) { return c == '('; }
bool is_close_parenthesis(char c) { return c == ')'; }
} // namespace

namespace model
{
InfixTokens produce_infix_tokens(Reader& reader)
{
	if (reader.empty())
	{
		return {};
	}
	// while (not reader.empty())
	// {

	// }
	return {};
}
} // namespace model