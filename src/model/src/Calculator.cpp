#include "model/Calculator.hpp"
#include "model/Symbol.hpp"

namespace model
{
Calculator::~Calculator()
{
}

Calculator::OperationResult Calculator::calculate_next()
{
	return do_calculate_next();
}

bool Calculator::has_finished() const
{
	return do_has_finished();
}
} // namespace model