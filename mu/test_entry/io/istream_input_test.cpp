#include <mu/io/lexer_istream_input.h>

#include <sstream>

#include <assert.h>

#include <gtest/gtest.h>

TEST (io_test, istream_input_test1)
{
	std::stringstream str ("");
	mu::io::lexer::istream_input input (str);
	wchar_t val (input ());
	EXPECT_EQ (val, L'\uffff');
}

TEST (io_test, istream_input_test2)
{
	std::stringstream str ("Hello world!");
	mu::io::lexer::istream_input input (str);
    mu::string target;
    auto failure (input (0, 0, target));
    EXPECT_TRUE (!failure);
    EXPECT_TRUE (target == mu::string (U""));
}

TEST (io_test, istream_input_test3)
{
	std::stringstream str ("Hello world!");
	mu::io::lexer::istream_input input (str);
    mu::string target;
    auto failure (input (3, 1, target));
    EXPECT_TRUE (!failure);
    EXPECT_TRUE (target == mu::string (U"l"));
}

TEST (io_test, istream_input_test4)
{
	std::stringstream str ("Hello world!");
	mu::io::lexer::istream_input input (str);
    mu::string target;
    str.seekg (6, std::ios_base::beg);
    auto initial (str.tellg());
    auto failure (input (3, 1, target));
    EXPECT_TRUE (!failure);
    EXPECT_TRUE (target == mu::string (U"l"));
    EXPECT_TRUE (str.tellg () == initial);
}

TEST (io_test, istream_input_test5)
{
	std::stringstream str ("Hello world!");
	mu::io::lexer::istream_input input (str);
    mu::string target;
    str.seekg (6, std::ios_base::beg);
    auto initial (str.tellg());
    auto failure (input (9, 5, target));
    EXPECT_TRUE (failure);
}