#include <gtest/gtest.h>
#include "../src/graphy.h"

TEST(GraphyListTests, LeftPush)
{
    Graphy g;
    g.command("lpush l world");
    g.command("lpush l hello");
    string res = g.command("lrange l -100 100");
    Utils f;
    EXPECT_EQ(f.redis_list({"hello", "world"}), res);
}

TEST(GraphyListTests, RightPush)
{
    Graphy g;
    g.command("rpush l hello");
    g.command("rpush l world");
    string res = g.command("lrange l -100 100");
    Utils f;
    EXPECT_EQ(f.redis_list({"hello", "world"}), res);
}

TEST(GraphyListTests, LRange)
{
    Graphy g;
    g.command("rpush mylist one two three");
    string lrange_zero_zero = g.command("lrange mylist 0 0");
    string lrange_n3_2 = g.command("lrange mylist -3 2");
    string lrange_n100_100 = g.command("lrange mylist -100 100");
    string lrange_empty = g.command("lrange mylist 5 10");
    Utils f;
    EXPECT_EQ(f.redis_list({"one"}), lrange_zero_zero);
    EXPECT_EQ(f.redis_list({"one", "two", "three"}), lrange_n3_2);
    EXPECT_EQ(f.redis_list({"one", "two", "three"}), lrange_n100_100);
    EXPECT_EQ(f.redis_list({}), lrange_empty);
}

TEST(GraphyListTests, LRangeColors)
{
    Graphy g;
    g.command("lpush colors red red red green");
    string lrange_response = g.command("lrange colors 0 -1");
    string lrem_red = g.command("lrem colors 1 red");
    string lrem_members = g.command("lrange colors 0 -1");
    Utils f;
    EXPECT_EQ(f.redis_list({"green", "red", "red", "red"}), lrange_response);
    EXPECT_EQ("(integer) 1", lrem_red);
    EXPECT_EQ(f.redis_list({"green", "red", "red"}), lrem_members);
}

TEST(GraphyListTests, ListLength)
{
    Graphy g;
    g.command("rpush l hello");
    g.command("rpush l world");
    string res = g.command("llen l");
    EXPECT_EQ("(integer) 2", res);
}

TEST(GraphyListTests, ListRemove)
{
    Graphy g;
    g.command("rpush l hello");
    g.command("rpush l hello");
    g.command("rpush l foo");
    g.command("rpush l hello");
    string res = g.command("lrem l -2 hello");
    string rangeres = g.command("lrange l 0 -1");
    Utils f;
    EXPECT_EQ("(integer) 2", res);
    EXPECT_EQ(f.redis_list({"hello", "foo"}), rangeres);
}

TEST(GraphyListTests, ListSet)
{
    Graphy g;
    g.command("rpush l one two three");
    string lset1 = g.command("lset l 0 four");
    string lset2 = g.command("lset l -2 five");
    string lset_members = g.command("lrange l 0 -1");
    Utils f;
    EXPECT_EQ("OK", lset1);
    EXPECT_EQ("OK", lset2);
    EXPECT_EQ(f.redis_list({"four", "five", "three"}), lset_members);
}

TEST(GraphyListTests, ListLeftPop)
{
    Graphy g;
    g.command("rpush l one two three four five");
    string lpop1 = g.command("lpop l");
    string lpop2 = g.command("lpop l");
    string list_members = g.command("lrange l 0 -1");
    Utils f;
    EXPECT_EQ("one", lpop1);
    EXPECT_EQ("two", lpop2);
    EXPECT_EQ(f.redis_list({"three", "four", "five"}), list_members);
}

TEST(GraphyListTests, ListRightPop)
{
    Graphy g;
    g.command("rpush l one two three four five");
    string lpop1 = g.command("rpop l");
    string lpop2 = g.command("rpop l");
    string list_members = g.command("lrange l 0 -1");
    Utils f;
    EXPECT_EQ("five", lpop1);
    EXPECT_EQ("four", lpop2);
    EXPECT_EQ(f.redis_list({"one", "two", "three"}), list_members);
}

TEST(GraphyListTests, ListIndex)
{
    Graphy g;
    g.command("rpush l hello world 2");
    string index_1 = g.command("lindex l 0");
    string index_2 = g.command("lindex l -1");
    string index_null = g.command("lindex l 5");
    EXPECT_EQ("hello", index_1);
    EXPECT_EQ("2", index_2);
    EXPECT_EQ("(nil)", index_null);
}

TEST(GraphyListTests, ListTrim)
{
    Graphy g;
    g.command("rpush l one two three");
    string ltrim_response = g.command("ltrim l 1 -1");
    string ltrim_range = g.command("lrange l 0 -1");
    Utils f;
    EXPECT_EQ("OK", ltrim_response);
    EXPECT_EQ(f.redis_list({"two", "three"}), ltrim_range);
}

TEST(GraphyListTests, ListTrim2)
{
    Graphy g;
    g.command("rpush l hello hello foo bar");
    string ltrim_response = g.command("ltrim l 1 -1");
    string ltrim_range = g.command("lrange l 0 -1");
    Utils f;
    EXPECT_EQ("OK", ltrim_response);
    EXPECT_EQ(f.redis_list({"hello", "foo", "bar"}), ltrim_range);
}
