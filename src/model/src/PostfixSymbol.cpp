#include "math/Value.hpp"
#include "model/PostfixSymbol.hpp"

namespace model
{
bool is_value(const PostfixSymbol& symbol)
{
	return std::holds_alternative<math::Value>(symbol.data);
}

bool is_operator(const PostfixSymbol& symbol)
{
	return std::holds_alternative<PostfixSymbol::Operator>(symbol.data);
}

PostfixSymbol::Operator get_operator(const PostfixSymbol& symbol)
{
	return std::get<PostfixSymbol::Operator>(symbol.data);
}

math::Value get_value(const PostfixSymbol& symbol)
{
	return std::get<math::Value>(symbol.data);
}
} // namespace model