#include "io/StringReader.hpp"
#include "util/Exception.hpp"
#include <gtest/gtest.h>

TEST(ReaderTests, When_input_is_empty_then_extract_throws)
{
	const std::string input{};
	
	io::StringReader sut{input.begin(), input.end()};

	ASSERT_TRUE(sut.empty());
	EXPECT_THROW(sut.extract(), util::BadAccessException);
}

TEST(ReaderTests, When_input_is_empty_then_peek_throws)
{
	const std::string input{};
	
	io::StringReader sut{input.begin(), input.end()};

	ASSERT_TRUE(sut.empty());
	EXPECT_THROW(sut.peek(), util::BadAccessException);
}

TEST(ReaderTests, When_input_has_one_character_then_extract_correct)
{
	const std::string input{"7"};
	
	io::StringReader sut{input.begin(), input.end()};

	ASSERT_FALSE(sut.empty());

	constexpr auto expected = '7';
	const auto result = sut.extract();

	EXPECT_EQ(expected, result);
	EXPECT_TRUE(sut.empty());
}

TEST(ReaderTests, When_input_has_one_character_then_peek_correct)
{
	const std::string input{"7"};
	
	io::StringReader sut{input.begin(), input.end()};

	ASSERT_FALSE(sut.empty());

	constexpr auto expected = '7';
	const auto result = sut.peek();

	ASSERT_FALSE(sut.empty());

	EXPECT_EQ(expected, result);
}

TEST(ReaderTests, When_input_has_multiple_characters_then_extract_correct)
{
	const std::string input{"1234"};
	
	io::StringReader sut{input.begin(), input.end()};

	EXPECT_EQ(sut.extract(), '1');
	EXPECT_EQ(sut.extract(), '2');
	EXPECT_EQ(sut.extract(), '3');
	EXPECT_EQ(sut.extract(), '4');
}

TEST(ReaderTests, When_input_has_multiple_characters_then_peek_multiple_times_correct)
{
	const std::string input{"1234"};
	
	io::StringReader sut{input.begin(), input.end()};

	EXPECT_EQ(sut.extract(), '1');
	EXPECT_EQ(sut.extract(), '2');
	EXPECT_EQ(sut.peek(), '3');
	EXPECT_EQ(sut.peek(), '3');
	EXPECT_EQ(sut.peek(), '3');
}

TEST(ReaderTests, When_extracting_beyond_input_then_extract_throws)
{
	const std::string input{"1234"};
	
	io::StringReader sut{input.begin(), input.end()};

	EXPECT_EQ(sut.extract(), '1');
	EXPECT_EQ(sut.extract(), '2');
	EXPECT_EQ(sut.extract(), '3');
	EXPECT_EQ(sut.extract(), '4');

	ASSERT_TRUE(sut.empty());
	EXPECT_THROW(sut.extract(), util::BadAccessException);
}

TEST(ReaderTests, When_extracting_beyond_input_then_peek_throws)
{
	const std::string input{"1234"};
	
	io::StringReader sut{input.begin(), input.end()};

	EXPECT_EQ(sut.extract(), '1');
	EXPECT_EQ(sut.extract(), '2');
	EXPECT_EQ(sut.extract(), '3');
	EXPECT_EQ(sut.extract(), '4');

	ASSERT_TRUE(sut.empty());
	EXPECT_THROW(sut.peek(), util::BadAccessException);
}