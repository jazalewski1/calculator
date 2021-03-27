#include "math/Value.hpp"
#include "model/Symbol.hpp"

namespace model
{
bool is_value(const Symbol& symbol)
{
	return std::holds_alternative<math::Value>(symbol.data);
}

bool is_operation_type(const Symbol& symbol)
{
	return std::holds_alternative<OperationType>(symbol.data);
}

OperationType get_operation_type(const Symbol& symbol)
{
	return std::get<OperationType>(symbol.data);
}

math::Value get_value(const Symbol& symbol)
{
	return std::get<math::Value>(symbol.data);
}
} // namespace model