#include "math/Value.hpp"
#include <variant>

namespace math
{
bool is_integer(const Value& value)
{
	return std::holds_alternative<int>(value);
}

bool is_double(const Value& value)
{
	return std::holds_alternative<double>(value);
}

int get_integer(const Value& value)
{
	return std::get<int>(value);
}

int get_double(const Value& value)
{
	return std::get<double>(value);
}
} // namespace math