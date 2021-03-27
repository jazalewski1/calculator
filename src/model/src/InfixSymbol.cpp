#include "model/InfixSymbol.hpp"

namespace model
{
bool is_value(const InfixSymbol& symbol)
{
	return std::holds_alternative<math::Value>(symbol.data);
}

bool is_operation_type(const InfixSymbol& symbol)
{
	return std::holds_alternative<InfixSymbol::Type>(symbol.data);
}

InfixSymbol::Type get_type(const InfixSymbol& symbol)
{
	return std::get<InfixSymbol::Type>(symbol.data);
}

math::Value get_value(const InfixSymbol& symbol)
{
	return std::get<math::Value>(symbol.data);
}
} // namespace model