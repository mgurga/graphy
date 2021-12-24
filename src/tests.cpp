#include "UnitTest++/UnitTest++.h"
#include "graphy.cpp"
#include <stdio.h>
#include <string>

using namespace std;

TEST(Sanity)
{
    CHECK_EQUAL(1, 1);
}

TEST(SetResult)
{
    Graphy g;
    string res = g.command("set foo 5");
    CHECK_EQUAL(res, "OK");
}

TEST(SetGet)
{
    Graphy g;
    g.command("set foo 1");
    string res = g.command("get foo");
    CHECK_EQUAL(res, "1");
}

TEST(LongSet)
{
    Graphy g;
    g.command("set hello this is a very long string with no spaces");
    string res = g.command("get hello");
    CHECK_EQUAL(res, "this is a very long string with no spaces");
}