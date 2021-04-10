#include "model/Tokenizer.hpp"
#include "model/InfixToken.hpp"
#include "model/ReaderMock.hpp"
#include "InfixTokenOperators.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string_view>
#include <iostream>

using namespace testing;

struct TokenizerTests : Test
{
	NiceMock<model::ReaderMock> reader{};

	void set_reader_expectations(std::string_view input)
	{
		EXPECT_CALL(reader, empty).WillRepeatedly(Return(false));
		InSequence seq{};
		for (auto c : input)
		{
			EXPECT_CALL(reader, peek)
				.WillRepeatedly(Return(c))
				.RetiresOnSaturation();
			EXPECT_CALL(reader, extract)
				.WillOnce(Return(c))
				.RetiresOnSaturation();
		}
		EXPECT_CALL(reader, empty).WillRepeatedly(Return(true));
	}
};

TEST_F(TokenizerTests, When_input_is_empty_then_output_is_empty)
{
	EXPECT_CALL(reader, is_empty).WillOnce(Return(true));

	const auto result = model::produce_infix_tokens(reader);

	EXPECT_TRUE(result.empty());
}

TEST_F(TokenizerTests, When_input_has_one_digit_value_then_produces_correct_token)
{
	constexpr auto input = "7"; 
	set_reader_expectations(input);

	const auto result = model::produce_infix_tokens(reader);

	EXPECT_THAT(
		result,
		ElementsAre(
			model::InfixToken{math::Value{7}}
		)
	);
}