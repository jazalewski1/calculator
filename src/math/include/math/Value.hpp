#pragma once

#include <variant>

namespace math
{
using Value = std::variant<int, double>;

bool is_integer(const Value&);

bool is_double(const Value&);

int get_integer(const Value&);

int get_double(const Value&);
} // namespace math