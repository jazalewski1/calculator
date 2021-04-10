#include <gmock/gmock.h>
#include "model/Reader.hpp"

namespace model
{
class ReaderMock : public Reader
{
public:
	MOCK_METHOD(char, extract, (), ());

	MOCK_METHOD(char, peek, (), (const));

	MOCK_METHOD(bool, empty, (), (const));

	MOCK_METHOD(void, move_forward, (), (override));

	MOCK_METHOD(char, next_character, (), (const, override));

	MOCK_METHOD(bool, is_empty, (), (const, override));
};
} // namespace model