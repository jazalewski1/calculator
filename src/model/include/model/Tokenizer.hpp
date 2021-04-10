#pragma once

#include "model/InfixToken.hpp"
#include "model/Reader.hpp"

namespace model
{
InfixTokens produce_infix_tokens(Reader&);
} // namespace model