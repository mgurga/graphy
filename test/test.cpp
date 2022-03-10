#include "../src/graphy.h"
#include <gtest/gtest.h>
#include <stdio.h>
#include <string>
#include <vector>

#ifndef PARSER_CPP
#define PARSER_CPP
#include "../src/parser.cpp"
#endif

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(GraphyMetaTests, Sanity)
{
    EXPECT_EQ(1, 1);
}

TEST(GraphyMetaTests, PingPong)
{
    Graphy g;
    string res = g.command("ping");
    EXPECT_EQ("PONG", res);
}

TEST(GraphyMetaTests, Dbsize)
{
    Graphy g;
    g.command("set hello world");
    g.command("set second key");
    g.command("set final val");
    string res = g.command("dbsize");
    EXPECT_EQ("(integer) 3", res);
}

TEST(GraphyMetaTests, EchoCorrectArgs)
{
    Graphy g;
    string res = g.command("echo \"hello world\"");
    EXPECT_EQ("hello world", res);
}

TEST(GraphyMetaTests, EchoIncorrectArgs)
{
    Graphy g;
    string res = g.command("echo hello world");
    EXPECT_EQ(ERR_NUM_OF_ARGS, res);
}

TEST(GraphyMetaTests, Incrby5)
{
    Graphy g;
    g.command("set foo 5");
    string res = g.command("incrby foo 5");
    EXPECT_EQ("(integer) 10", res);
}

TEST(GraphyMetaTests, Decrby5)
{
    Graphy g;
    g.command("set foo 5");
    string res = g.command("decrby foo 5");
    EXPECT_EQ("(integer) 0", res);
}

TEST(GraphyMetaTests, RenameKeySuccess)
{
    Graphy g;
    g.command("set hello world");
    g.command("rename hello test");
    string res = g.command("get test");
    string res2 = g.command("get hello");
    EXPECT_EQ("world", res);
    EXPECT_EQ("(nil)", res2);
}

TEST(GraphyMetaTests, RenamenxKeyExists)
{
    Graphy g;
    g.command("set hello world");
    g.command("set foo bar");
    string res = g.command("renamenx hello foo");
    string res2 = g.command("get foo");
    EXPECT_EQ("(integer) 0", res);
    EXPECT_EQ("bar", res2);
}

TEST(GraphyMetaTests, Quit)
{
    Graphy g;
    string res = g.command("quit");
    EXPECT_EQ("OK", res);
}

TEST(GraphyMetaTests, MultipleSet)
{
    Graphy g;
    g.command("mset key1 Hello key2 World");
    string key1 = g.command("get key1");
    string key2 = g.command("get key2");
    EXPECT_EQ("Hello", key1);
    EXPECT_EQ("World", key2);
}

TEST(GraphyMetaTests, MultipleGet)
{
    Graphy g;
    Utils f;
    g.command("mset key1 Hello key2 World");
    string res = g.command("mget key1 key2 nonexisting");
    EXPECT_EQ(f.redis_list({"Hello", "World", "(nil)"}), res);
}

TEST(GraphyMetaTests, RandomKey)
{
    Graphy g;
    Utils f;
    g.command("set hello world");
    g.command("set ending key");
    string res = g.command("randomkey");
    EXPECT_TRUE(res == "hello" || res == "ending");
}

TEST(GraphyMetaTests, FlushDB)
{
    Graphy g;
    g.command("set hello world");
    g.command("set foo bar");
    g.command("sadd test a b c");
    string res = g.command("flushdb");
    string keyexistsres = g.command("get hello");
    g.command("set baz bo");
    string getres = g.command("get baz");
    EXPECT_EQ("OK", res);
    EXPECT_EQ("(nil)", keyexistsres);
    EXPECT_EQ("bo", getres);
}

TEST(GraphyMetaTests, GetRange)
{
    Graphy g;
    g.command("set mykey \"This is a string\"");
    string range1 = g.command("getrange mykey 0 3");
    string range2 = g.command("getrange mykey -3 -1");
    string range3 = g.command("getrange mykey 0 -1");
    string range4 = g.command("getrange mykey 10 100");
    EXPECT_EQ("This", range1);
    EXPECT_EQ("ing", range2);
    EXPECT_EQ("This is a string", range3);
    EXPECT_EQ("string", range4);
}

TEST(GraphyMetaTests, Keys)
{
    Graphy g;
    g.command("mset firstname Jack lastname Stuntman age 35");
    string keys1 = g.command("keys \"*name*\"");
    string keys2 = g.command("keys \"a??\"");
    string keys3 = g.command("keys \"*\"");
    Utils u;
    EXPECT_EQ(u.redis_list({"firstname", "lastname"}), keys1);
    EXPECT_EQ(u.redis_list({"age"}), keys2);
    EXPECT_EQ(u.redis_list({"firstname", "lastname", "age"}), keys3);
}
