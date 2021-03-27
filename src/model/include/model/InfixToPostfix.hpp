#pragma once

#include "model/InfixSymbol.hpp"
#include "model/PostfixSymbol.hpp"

namespace model
{
PostfixSymbols infix_to_postfix(const InfixSymbols&);
} // namespace model