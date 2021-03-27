#include "math/Value.hpp"
#include "model/PostfixSymbol.hpp"

namespace model
{
bool is_value(const PostfixSymbol& symbol)
{
	return std::holds_alternative<math::Value>(symbol.data);
}

bool is_operation_type(const PostfixSymbol& symbol)
{
	return std::holds_alternative<PostfixSymbol::Type>(symbol.data);
}

PostfixSymbol::Type get_type(const PostfixSymbol& symbol)
{
	return std::get<PostfixSymbol::Type>(symbol.data);
}

math::Value get_value(const PostfixSymbol& symbol)
{
	return std::get<math::Value>(symbol.data);
}
} // namespace model