#include "model/InfixSymbol.hpp"

namespace model
{
int precedence(InfixSymbol::Operator input)
{
	switch (input)
	{
		case InfixSymbol::Operator::SUBTRACTION: return 1;
		case InfixSymbol::Operator::ADDITION: return 1;
		case InfixSymbol::Operator::DIVISION: return 2;
		case InfixSymbol::Operator::MULTIPLICATION: return 2;
	}
}

bool is_value(const InfixSymbol& symbol)
{
	return std::holds_alternative<math::Value>(symbol.data);
}

bool is_operator(const InfixSymbol& symbol)
{
	return std::holds_alternative<InfixSymbol::Operator>(symbol.data);
}

bool is_open_par(const InfixSymbol& symbol)
{
	return std::holds_alternative<InfixSymbol::OpenPar>(symbol.data);
}

bool is_close_par(const InfixSymbol& symbol)
{
	return std::holds_alternative<InfixSymbol::ClosePar>(symbol.data);
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