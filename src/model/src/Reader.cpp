#include "model/Reader.hpp"
#include "util/Exception.hpp"

namespace model
{
char Reader::extract()
{
	const auto out = peek();
	move_forward();
	return out;
}

bool Reader::empty() const
{
	return is_empty();
}

char Reader::peek() const
{
	if (is_empty())
	{
		throw util::BadAccessException{"Reader has no more characters to extract."};
	}
	return next_character();
}
} // namespace model