#include <gtest/gtest.h>
#include "../src/graphy.h"

TEST(ParserTests, NoQuotes)
{
    Parser p;
    vector<string> res = p.parse("set hello world");
    vector<string> expected = {"set", "hello", "world"};
    EXPECT_EQ(expected, res);
}

TEST(ParserTests, Quotes)
{
    Parser p;
    vector<string> res = p.parse("set \"hello\" \"world\"");
    vector<string> expected = {"set", "hello", "world"};
    EXPECT_EQ(expected, res);
}

TEST(ParserTests, QuotesWithSpaces)
{
    Parser p;
    vector<string> res = p.parse("set \"hello there\" \"this is a long string\"");
    vector<string> expected = {"set", "hello there", "this is a long string"};
    EXPECT_EQ(expected, res);
}

TEST(ParserTests, QuotesLeadingSpaces)
{
    Parser p;
    vector<string> res = p.parse("          set \"hello\" \"world\"          ");
    vector<string> expected = {"set", "hello", "world"};
    EXPECT_EQ(expected, res);
}
