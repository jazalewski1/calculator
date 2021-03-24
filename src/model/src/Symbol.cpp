#include "model/Symbol.hpp"

namespace model
{
bool is_value(const SymbolVariant& variant)
{
	return std::holds_alternative<Value>(variant);
}

bool is_operation_type(const SymbolVariant& variant)
{
	return std::holds_alternative<OperationType>(variant);
}

OperationType get_operation_type(const SymbolVariant& symbol)
{
	return std::get<OperationType>(symbol);
}

Value get_value(const SymbolVariant& symbol)
{
	return std::get<Value>(symbol);
}
} // namespace model