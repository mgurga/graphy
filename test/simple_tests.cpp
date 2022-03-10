#include <gtest/gtest.h>
#include "../src/graphy.h"

TEST(GraphySimpleTests, SetResult)
{
    Graphy g;
    string res = g.command("set foo 5");
    EXPECT_EQ("OK", res);
}

TEST(GraphySimpleTests, SetGet)
{
    Graphy g;
    g.command("set foo 1");
    string res = g.command("get foo");
    EXPECT_EQ("1", res);
}

TEST(GraphySimpleTests, LongSet)
{
    Graphy g;
    g.command("set \"hello\" \"this is a very long string with no spaces\"");
    string res = g.command("get hello");
    EXPECT_EQ("this is a very long string with no spaces", res);
}

TEST(GraphySimpleTests, KeyExists)
{
    Graphy g;
    g.command("set test val");
    g.command("set foo bar");
    g.command("set database test");
    string res = g.command("exists foo");
    EXPECT_EQ("(integer) 1", res);
}

TEST(GraphySimpleTests, KeyDoesNotExists)
{
    Graphy g;
    string res = g.command("exists foo");
    EXPECT_EQ("(integer) 0", res);
}

TEST(GraphySimpleTests, SimpleIncr)
{
    Graphy g;
    g.command("set foo 5");
    string res = g.command("incr foo");
    EXPECT_EQ("(integer) 6", res);
}

TEST(GraphySimpleTests, ManyIncr)
{
    Graphy g;
    g.command("set foo 5");
    g.command("incr foo");
    g.command("incr foo");
    g.command("incr foo");
    string res = g.command("incr foo");
    EXPECT_EQ("(integer) 9", res);
}

TEST(GraphySimpleTests, SimpleDecr)
{
    Graphy g;
    g.command("set foo 5");
    string res = g.command("incr foo");
    EXPECT_EQ("(integer) 6", res);
}

TEST(GraphySimpleTests, ManyDecr)
{
    Graphy g;
    g.command("set foo 5");
    g.command("decr foo");
    g.command("decr foo");
    g.command("decr foo");
    string res = g.command("decr foo");
    EXPECT_EQ("(integer) 1", res);
}

TEST(GraphySimpleTests, DeleteKey)
{
    Graphy g;
    g.command("set before value");
    g.command("set test key");
    g.command("set after data");
    string dres = g.command("del test");
    string res = g.command("get test");
    EXPECT_EQ("(integer) 1", dres);
    EXPECT_EQ("(nil)", res);
}

TEST(GraphySimpleTests, DeleteMultiple)
{
    Graphy g;
    g.command("set before value");
    g.command("set test key");
    g.command("set after data");
    g.command("set post info");
    string dres = g.command("del test after");
    string res = g.command("get test");
    string res2 = g.command("get after");
    EXPECT_EQ("(integer) 2", dres);
    EXPECT_EQ("(nil)", res);
    EXPECT_EQ("(nil)", res2);
}

TEST(GraphySimpleTests, OverwriteKey)
{
    Graphy g;
    g.command("set test val");
    g.command("set test val2");
    g.command("set test val3");
    string res = g.command("get test");
    EXPECT_EQ("val3", res);
}

TEST(GraphySimpleTests, Getset)
{
    Graphy g;
    g.command("set foo hello");
    string getsetres = g.command("getset foo world");
    string getres = g.command("get foo");
    EXPECT_EQ("hello", getsetres);
    EXPECT_EQ("world", getres);
}

TEST(GraphySimpleTests, GetsetNotExisting)
{
    Graphy g;
    string res = g.command("getset unsetkey test");
    EXPECT_EQ("(nil)", res);
}
