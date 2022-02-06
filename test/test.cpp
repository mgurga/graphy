#include "../src/graphy.cpp"
#include <gtest/gtest.h>
#include <stdio.h>
#include <string>
#include <vector>

#ifndef PARSER_CPP
#define PARSER_CPP
#include "../src/parser.cpp"
#endif

using namespace std;

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


TEST(GraphyTests, Sanity)
{
    EXPECT_EQ(1, 1);
}

TEST(GraphyTests, PingPong)
{
    Graphy g;
    string res = g.command("ping");
    EXPECT_EQ("PONG", res);
}

TEST(GraphyTests, SetResult)
{
    Graphy g;
    string res = g.command("set foo 5");
    EXPECT_EQ("OK", res);
}

TEST(GraphyTests, SetGet)
{
    Graphy g;
    g.command("set foo 1");
    string res = g.command("get foo");
    EXPECT_EQ("1", res);
}

TEST(GraphyTests, LongSet)
{
    Graphy g;
    g.command("set \"hello\" \"this is a very long string with no spaces\"");
    string res = g.command("get hello");
    EXPECT_EQ("this is a very long string with no spaces", res);
}

TEST(GraphyTests, KeyExists)
{
    Graphy g;
    g.command("set test val");
    g.command("set foo bar");
    g.command("set database test");
    string res = g.command("exists foo");
    EXPECT_EQ("(integer) 1", res);
}

TEST(GraphyTests, KeyDoesNotExists)
{
    Graphy g;
    string res = g.command("exists foo");
    EXPECT_EQ("(integer) 0", res);
}

TEST(GraphyTests, SimpleIncr)
{
    Graphy g;
    g.command("set foo 5");
    string res = g.command("incr foo");
    EXPECT_EQ("(integer) 6", res);
}

TEST(GraphyTests, ManyIncr)
{
    Graphy g;
    g.command("set foo 5");
    g.command("incr foo");
    g.command("incr foo");
    g.command("incr foo");
    string res = g.command("incr foo");
    EXPECT_EQ("(integer) 9", res);
}

TEST(GraphyTests, SimpleDecr)
{
    Graphy g;
    g.command("set foo 5");
    string res = g.command("incr foo");
    EXPECT_EQ("(integer) 6", res);
}

TEST(GraphyTests, ManyDecr)
{
    Graphy g;
    g.command("set foo 5");
    g.command("decr foo");
    g.command("decr foo");
    g.command("decr foo");
    string res = g.command("decr foo");
    EXPECT_EQ("(integer) 1", res);
}

TEST(GraphyTests, DeleteKey)
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

TEST(GraphyTests, DeleteMultiple)
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

TEST(GraphyTests, OverwriteKey)
{
    Graphy g;
    g.command("set test val");
    g.command("set test val2");
    g.command("set test val3");
    string res = g.command("get test");
    EXPECT_EQ("val3", res);
}

TEST(GraphyTests, Getset)
{
    Graphy g;
    g.command("set foo hello");
    string getsetres = g.command("getset foo world");
    string getres = g.command("get foo");
    EXPECT_EQ("hello", getsetres);
    EXPECT_EQ("world", getres);
}

TEST(GraphyTests, GetsetNotExisting)
{
    Graphy g;
    string res = g.command("getset unsetkey test");
    EXPECT_EQ("(nil)", res);
}

TEST(GraphyTests, Dbsize)
{
    Graphy g;
    g.command("set hello world");
    g.command("set second key");
    g.command("set final val");
    string res = g.command("dbsize");
    EXPECT_EQ("(integer) 3", res);
}

TEST(GraphyTests, EchoCorrectArgs)
{
    Graphy g;
    string res = g.command("echo \"hello world\"");
    EXPECT_EQ("hello world", res);
}

TEST(GraphyTests, EchoIncorrectArgs)
{
    Graphy g;
    string res = g.command("echo hello world");
    EXPECT_EQ("ERR incorrect number of arguments", res);
}

TEST(GraphyTests, Incrby5)
{
    Graphy g;
    g.command("set foo 5");
    string res = g.command("incrby foo 5");
    EXPECT_EQ("(integer) 10", res);
}

TEST(GraphyTests, Decrby5)
{
    Graphy g;
    g.command("set foo 5");
    string res = g.command("decrby foo 5");
    EXPECT_EQ("(integer) 0", res);
}

TEST(GraphyTests, RenameKeySuccess)
{
    Graphy g;
    g.command("set hello world");
    g.command("rename hello test");
    string res = g.command("get test");
    string res2 = g.command("get hello");
    EXPECT_EQ("world", res);
    EXPECT_EQ("(nil)", res2);
}

TEST(GraphyTests, RenamenxKeyExists)
{
    Graphy g;
    g.command("set hello world");
    g.command("set foo bar");
    string res = g.command("renamenx hello foo");
    string res2 = g.command("get foo");
    EXPECT_EQ("(integer) 0", res);
    EXPECT_EQ("bar", res2);
}

TEST(GraphyTests, Quit)
{
    Graphy g;
    string res = g.command("quit");
    EXPECT_EQ("OK", res);
}

TEST(GraphyTests, AddToSet)
{
    Graphy g;
    g.command("set beginning key");
    g.command("sadd myset hello");
    g.command("sadd myset world");
    g.command("sadd myset hi");
    g.command("set following value");
    vector<string> mem = g.db->smembers("myset");
    vector<string> exp = {"hello", "world", "hi"};
    EXPECT_EQ(exp, mem);
}

TEST(GraphyTests, AddDuplicatesToSet)
{
    Graphy g;
    g.command("sadd myset hello");
    g.command("sadd myset world");
    string res = g.command("sadd myset hello");
    EXPECT_EQ("(integer) 0", res);
}

TEST(GraphyTests, GetSetMemberList)
{
    Graphy g;
    g.command("set beginning key");
    g.command("sadd myset hello");
    g.command("sadd myset world");
    g.command("set following value");
    string res = g.command("smembers myset");
    EXPECT_EQ("1) \"hello\"\n2) \"world\"", res);
}

TEST(GraphyTests, IsSetMember)
{
    Graphy g;
    g.command("sadd set hello");
    string ismem = g.command("sismember set hello");
    string notmem = g.command("sismember set world");
    EXPECT_EQ("(integer) 1", ismem);
    EXPECT_EQ("(integer) 0", notmem);
}

TEST(GraphyTests, SetSize)
{
    Graphy g;
    g.command("set beginning key");
    g.command("sadd test hello");
    g.command("sadd test world");
    string res = g.command("scard test");
    EXPECT_EQ("(integer) 2", res);
}

TEST(GraphyTests, SetIntersection)
{
    Graphy g;
    g.command("sadd key1 a b c");
    g.command("sadd key2 c d e");
    string res = g.command("sinter key1 key2");
    EXPECT_EQ("1) \"c\"", res);
}

TEST(GraphyTests, SetIntersectionStore)
{
    Graphy g;
    g.command("sadd key1 a b c");
    g.command("sadd key2 c d e");
    g.command("sinterstore res key1 key2");
    string res = g.command("smembers res");
    EXPECT_EQ("1) \"c\"", res);
}

TEST(GraphyTests, SetDifference)
{
    Graphy g;
    g.command("sadd key1 a b c");
    g.command("sadd key2 c d e");
    string res = g.command("sdiff key1 key2");
    EXPECT_EQ("1) \"a\"\n2) \"b\"", res);
}

TEST(GraphyTests, SetDifferenceStore)
{
    Graphy g;
    g.command("sadd key1 a b c");
    g.command("sadd key2 c d e");
    g.command("sdiffstore res key1 key2");
    string res = g.command("smembers res");
    EXPECT_EQ("1) \"a\"\n2) \"b\"", res);
}

TEST(GraphyTests, MultipleSet)
{
    Graphy g;
    g.command("mset key1 Hello key2 World");
    string key1 = g.command("get key1");
    string key2 = g.command("get key2");
    EXPECT_EQ("Hello", key1);
    EXPECT_EQ("World", key2);
}

TEST(GraphyTests, MultipleGet)
{
    Graphy g;
    Formatter f;
    g.command("mset key1 Hello key2 World");
    string res = g.command("mget key1 key2 nonexisting");
    EXPECT_EQ(f.redis_list({"Hello", "World", "(nil)"}), res);
}

TEST(GraphyTests, RemoveSet)
{
    Graphy g;
    g.command("set hello world");
    g.command("sadd test a");
    g.command("sadd test b");
    g.command("set ending key");
    string res = g.command("srem test a");
    string ismemres = g.command("sismember test a");
    EXPECT_EQ("(integer) 1", res);
    EXPECT_EQ("(integer) 0", ismemres);
}

TEST(GraphyTests, PopSet)
{
    Graphy g;
    g.command("set hello world");
    g.command("sadd test a b c");
    g.command("set ending key");
    string res = g.command("spop test");
    if (res == "\"a\"" || res == "\"b\"" || res == "\"c\"")
        EXPECT_EQ(true, true);
    else
        EXPECT_EQ(true, false);
}

TEST(GraphyTests, MultiplePopSet)
{
    Graphy g;
    Formatter f;
    g.command("sadd test a b");
    string res = g.command("spop test 3");
    if (res == f.redis_list({"a", "b"}) || res == f.redis_list({"b", "a"}))
        EXPECT_EQ(true, true);
    else
        EXPECT_EQ(true, false);
}

TEST(GraphyTests, RandomSetMember)
{
    Graphy g;
    g.command("sadd test a b c");
    string res = g.command("srandmember test");
    if (res == "\"a\"" || res == "\"b\"" || res == "\"c\"")
        EXPECT_EQ(true, true);
    else
        EXPECT_EQ(true, false);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
