#include <gtest/gtest.h>
#include "../src/graphy.h"

TEST(GraphySetTests, SetUnion)
{
    Graphy g;
    Utils f;
    g.command("sadd hello a b c");
    g.command("sadd world c d e");
    string res = g.command("sunion hello world");
    EXPECT_EQ(f.redis_list({"a", "b", "c", "d", "e"}), res);
}

TEST(GraphySetTests, StoreSetUnion)
{
    Graphy g;
    Utils f;
    g.command("sadd hello a b c");
    g.command("sadd world c d e");
    string storeres = g.command("sunionstore key hello world");
    string memres = g.command("smembers key");
    EXPECT_EQ("(integer) 5", storeres);
    EXPECT_EQ(f.redis_list({"a", "b", "c", "d", "e"}), memres);
}

TEST(GraphySetTests, RemoveSet)
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

TEST(GraphySetTests, PopSet)
{
    Graphy g;
    g.command("set hello world");
    g.command("sadd test a b c");
    g.command("set ending key");
    string res = g.command("spop test");
    EXPECT_TRUE(res == "\"a\"" || res == "\"b\"" || res == "\"c\"");
}

TEST(GraphySetTests, MultiplePopSet)
{
    Graphy g;
    Utils f;
    g.command("sadd test a b");
    string res = g.command("spop test 3");
    EXPECT_TRUE(res == f.redis_list({"a", "b"}) || res == f.redis_list({"b", "a"}));
}

TEST(GraphySetTests, RandomSetMember)
{
    Graphy g;
    g.command("sadd test a b c");
    string res = g.command("srandmember test");
    EXPECT_TRUE(res == "\"a\"" || res == "\"b\"" || res == "\"c\"");
}

TEST(GraphySetTests, SetMove)
{
    Graphy g;
    Utils f;
    g.command("sadd test a b c");
    g.command("sadd dest d e");
    string res = g.command("smove test dest a");
    string resmem = g.command("smembers dest");
    EXPECT_EQ("(integer) 1", res);
    EXPECT_EQ(f.redis_list({"d", "e", "a"}), resmem);
}

TEST(GraphySetTests, AddToSet)
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

TEST(GraphySetTests, AddDuplicatesToSet)
{
    Graphy g;
    g.command("sadd myset hello");
    g.command("sadd myset world");
    string res = g.command("sadd myset hello");
    EXPECT_EQ("(integer) 0", res);
}

TEST(GraphySetTests, GetSetMemberList)
{
    Graphy g;
    g.command("set beginning key");
    g.command("sadd myset hello");
    g.command("sadd myset world");
    g.command("set following value");
    string res = g.command("smembers myset");
    EXPECT_EQ("1) \"hello\"\n2) \"world\"", res);
}

TEST(GraphySetTests, IsSetMember)
{
    Graphy g;
    g.command("sadd set hello");
    string ismem = g.command("sismember set hello");
    string notmem = g.command("sismember set world");
    EXPECT_EQ("(integer) 1", ismem);
    EXPECT_EQ("(integer) 0", notmem);
}

TEST(GraphySetTests, SetSize)
{
    Graphy g;
    g.command("set beginning key");
    g.command("sadd test hello");
    g.command("sadd test world");
    string res = g.command("scard test");
    EXPECT_EQ("(integer) 2", res);
}

TEST(GraphySetTests, SetIntersection)
{
    Graphy g;
    g.command("sadd key1 a b c");
    g.command("sadd key2 c d e");
    string res = g.command("sinter key1 key2");
    EXPECT_EQ("1) \"c\"", res);
}

TEST(GraphySetTests, SetIntersectionStore)
{
    Graphy g;
    g.command("sadd key1 a b c");
    g.command("sadd key2 c d e");
    g.command("sinterstore res key1 key2");
    string res = g.command("smembers res");
    EXPECT_EQ("1) \"c\"", res);
}

TEST(GraphySetTests, SetDifference)
{
    Graphy g;
    g.command("sadd key1 a b c");
    g.command("sadd key2 c d e");
    string res = g.command("sdiff key1 key2");
    EXPECT_EQ("1) \"a\"\n2) \"b\"", res);
}

TEST(GraphySetTests, SetDifferenceStore)
{
    Graphy g;
    g.command("sadd key1 a b c");
    g.command("sadd key2 c d e");
    g.command("sdiffstore res key1 key2");
    string res = g.command("smembers res");
    EXPECT_EQ("1) \"a\"\n2) \"b\"", res);
}
