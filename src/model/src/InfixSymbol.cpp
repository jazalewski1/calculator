#include "model/InfixSymbol.hpp"

namespace model
{
bool is_value(const InfixSymbol& symbol)
{
	return std::holds_alternative<math::Value>(symbol.data);
}

bool is_operator(const InfixSymbol& symbol)
{
	return std::holds_alternative<InfixSymbol::Operator>(symbol.data);
}

InfixSymbol::Operator get_operator(const InfixSymbol& symbol)
{
	return std::get<InfixSymbol::Operator>(symbol.data);
}

math::Value get_value(const InfixSymbol& symbol)
{
	return std::get<math::Value>(symbol.data);
}
} // namespace model