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
    CHECK_EQUAL("1", res);
}

TEST(KeyDoesNotExists)
{
    Graphy g;
    string res = g.command("exists foo");
    CHECK_EQUAL("0", res);
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

TEST(DeleteKey)
{
    Graphy g;
    g.command("d");
    g.command("set before value");
    g.command("set test key");
    g.command("set after data");
    g.command("del test");
    string res = g.command("get test");
    g.command("save");
    CHECK_EQUAL("(nil)", res);
}