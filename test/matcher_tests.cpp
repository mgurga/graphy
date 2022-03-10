#include <gtest/gtest.h>
#include "../src/graphy.h"

TEST(MatcherTests, QuestionMark)
{
    Utils u;
    EXPECT_EQ(u.matches("hello", "h?llo"), true);
    EXPECT_EQ(u.matches("hallo", "h?llo"), true);
    EXPECT_EQ(u.matches("hxallo", "h?llo"), false);
}

TEST(MatcherTests, Wildcard)
{
    Utils u;
    EXPECT_EQ(u.matches("heeeeeeeeeeeeeeeeello", "h*llo"), true);
    EXPECT_EQ(u.matches("hllo", "h*llo"), true);
    EXPECT_EQ(u.matches("hxxxxxxllo", "h*llo"), true);
}

TEST(MatcherTests, MultipleLetters)
{
    Utils u;
    EXPECT_EQ(u.matches("hello", "h[aei]llo"), true);
    EXPECT_EQ(u.matches("hillo", "h[aei]llo"), true);
    EXPECT_EQ(u.matches("hxllo", "h[aei]llo"), false);
}

TEST(MatcherTests, LetterRange)
{
    Utils u;
    EXPECT_EQ(u.matches("hallo", "h[a-m]llo"), true);
    EXPECT_EQ(u.matches("hlllo", "h[a-m]llo"), true);
    EXPECT_EQ(u.matches("hzllo", "h[a-m]llo"), false);
}

TEST(MatcherTests, LetterRangeCaret)
{
    Utils u;
    EXPECT_EQ(u.matches("hallo", "h[^e]llo"), true);
    EXPECT_EQ(u.matches("hlllo", "h[^e]llo"), true);
}
