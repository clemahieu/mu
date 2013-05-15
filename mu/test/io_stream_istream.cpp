#include <mu/io/stream_istream.hpp>
#include <gtest/gtest.h>

#include <sstream>

TEST (string_istream, empty)
{
    std::stringstream stream1 ("");
    mu::io::stream_istream stream2 (stream1, 2);
    EXPECT_EQ (2, stream2.size ());
    EXPECT_EQ (U'\U0000FFFF', stream2 [0]);
    EXPECT_EQ (U'\U0000FFFF', stream2 [1]);
}

TEST (stream_istream, test1)
{
    std::stringstream stream1 ("test");
    mu::io::stream_istream stream2 (stream1, 1);
    EXPECT_EQ (1, stream2.size ());
    EXPECT_EQ (U't', stream2 [0]);
    stream2.consume (1);
    EXPECT_EQ (U'e', stream2 [0]);
    stream2.consume (1);
    EXPECT_EQ (U's', stream2 [0]);
    stream2.consume (1);
    EXPECT_EQ (U't', stream2 [0]);
    stream2.consume (1);
    EXPECT_EQ (U'\U0000FFFF', stream2 [0]);
}

TEST (stream_istream, test2)
{
    std::stringstream stream1 ("test");
    mu::io::stream_istream stream2 (stream1, 2);
    EXPECT_EQ (2, stream2.size ());
    EXPECT_EQ (U't', stream2 [0]);
    EXPECT_EQ (U'e', stream2 [1]);
    stream2.consume (1);
    EXPECT_EQ (U'e', stream2 [0]);
    EXPECT_EQ (U's', stream2 [1]);
    stream2.consume (1);
    EXPECT_EQ (U's', stream2 [0]);
    EXPECT_EQ (U't', stream2 [1]);
    stream2.consume (1);
    EXPECT_EQ (U't', stream2 [0]);
    EXPECT_EQ (U'\U0000FFFF', stream2 [1]);
    stream2.consume (1);
    EXPECT_EQ (U'\U0000FFFF', stream2 [0]);
    EXPECT_EQ (U'\U0000FFFF', stream2 [1]);
}

TEST (stream_istream, test3)
{
    std::stringstream stream1 ("test");
    mu::io::stream_istream stream2 (stream1, 2);
    EXPECT_EQ (2, stream2.size ());
    EXPECT_EQ (U't', stream2 [0]);
    EXPECT_EQ (U'e', stream2 [1]);
    stream2.consume (2);
    EXPECT_EQ (U's', stream2 [0]);
    EXPECT_EQ (U't', stream2 [1]);
    stream2.consume (2);
    EXPECT_EQ (U'\U0000FFFF', stream2 [0]);
    EXPECT_EQ (U'\U0000FFFF', stream2 [1]);
}