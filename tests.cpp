#include "src/graphy.cpp"
#include "UnitTest++/UnitTest++.h"
#include <stdio.h>
#include <string>

using namespace std;

TEST(Sanity)
{
    CHECK_EQUAL(1, 1);
}

TEST(PingPong)
{
    Graphy g;
    string res = g.command("ping");
    CHECK_EQUAL("PONG", res);
}

TEST(SetResult)
{
    Graphy g;
    string res = g.command("set foo 5");
    CHECK_EQUAL("OK", res);
}

TEST(SetGet)
{
    Graphy g;
    g.command("set foo 1");
    string res = g.command("get foo");
    CHECK_EQUAL("1", res);
}

TEST(LongSet)
{
    Graphy g;
    g.command("set hello this is a very long string with no spaces");
    string res = g.command("get hello");
    CHECK_EQUAL("this is a very long string with no spaces", res);
}

TEST(KeyExists)
{
    Graphy g;
    g.command("set test val");
    g.command("set foo bar");
    g.command("set database test");
    string res = g.command("exists foo");
    CHECK_EQUAL("(integer) 1", res);
}

TEST(KeyDoesNotExists)
{
    Graphy g;
    string res = g.command("exists foo");
    CHECK_EQUAL("(integer) 0", res);
}

TEST(SimpleIncr)
{
    Graphy g;
    g.command("set foo 5");
    string res = g.command("incr foo");
    CHECK_EQUAL("6", res);
}

TEST(ManyIncr)
{
    Graphy g;
    g.command("set foo 5");
    g.command("incr foo");
    g.command("incr foo");
    g.command("incr foo");
    string res = g.command("incr foo");
    CHECK_EQUAL("9", res);
}

TEST(SimpleDecr)
{
    Graphy g;
    g.command("set foo 5");
    string res = g.command("incr foo");
    CHECK_EQUAL("6", res);
}

TEST(ManyDecr)
{
    Graphy g;
    g.command("set foo 5");
    g.command("decr foo");
    g.command("decr foo");
    g.command("decr foo");
    string res = g.command("decr foo");
    CHECK_EQUAL("1", res);
}

TEST(DeleteKey)
{
    Graphy g;
    g.command("set before value");
    g.command("set test key");
    g.command("set after data");
    string dres = g.command("del test");
    string res = g.command("get test");
    CHECK_EQUAL("(integer) 1", dres);
    CHECK_EQUAL("(nil)", res);
}

TEST(DeleteMultiple)
{
    Graphy g;
    g.command("set before value");
    g.command("set test key");
    g.command("set after data");
    g.command("set post info");
    string dres = g.command("del test after");
    string res = g.command("get test");
    string res2 = g.command("get after");
    CHECK_EQUAL("(integer) 2", dres);
    CHECK_EQUAL("(nil)", res);
    CHECK_EQUAL("(nil)", res2);
}

TEST(OverwriteKey)
{
    Graphy g;
    g.command("set test val");
    g.command("set test val2");
    g.command("set test val3");
    string res = g.command("get test");
    CHECK_EQUAL("val3", res);
}

TEST(Getset)
{
    Graphy g;
    g.command("set foo hello");
    string getsetres = g.command("getset foo world");
    string getres = g.command("get foo");
    CHECK_EQUAL("hello", getsetres);
    CHECK_EQUAL("world", getres);
}

TEST(GetsetNotExisting)
{
    Graphy g;
    string res = g.command("getset unsetkey test");
    CHECK_EQUAL("(nil)", res);
}