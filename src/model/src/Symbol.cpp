#include "math/Value.hpp"
#include "model/Symbol.hpp"

namespace model
{
bool is_value(const Symbol::Variant& variant)
{
	return std::holds_alternative<math::Value>(variant);
}

bool is_operation_type(const Symbol::Variant& variant)
{
	return std::holds_alternative<OperationType>(variant);
}

OperationType get_operation_type(const Symbol::Variant& symbol)
{
	return std::get<OperationType>(symbol);
}

math::Value get_value(const Symbol::Variant& symbol)
{
	return std::get<math::Value>(symbol);
}
} // namespace model