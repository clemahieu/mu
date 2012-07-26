#include <mu/test_entry/io/lexer_result.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/source.h>
#include <mu/io/tokens/token.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/right_square.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/parameters.h>
#include <mu/core/errors/error_list.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (io_test, lexer2)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U"");
	EXPECT_EQ (result.results.size (), 1);
	auto t1 (result.results [0]);
	EXPECT_NE (dynamic_cast <mu::io::tokens::stream_end *> (t1.first), nullptr);
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 0);
	EXPECT_EQ (t1.second.last.column, 1);
	EXPECT_EQ (t1.second.last.row, 1);
}

TEST (io_test, lexer3)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U"a[];");
	EXPECT_EQ (result.results.size (), 5);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t3 (result.results [2]);
	auto t4 (result.results [3]);
	auto t5 (result.results [4]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1i->string.size (), 1);
	EXPECT_EQ (t1i->string [0], L'a');
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 0);
	EXPECT_EQ (t1.second.last.column, 1);
	EXPECT_EQ (t1.second.last.row, 1);
	EXPECT_NE (dynamic_cast <mu::io::tokens::left_square *> (t2.first), nullptr);
	EXPECT_EQ (t2.second.first.character, 1);
	EXPECT_EQ (t2.second.first.column, 2);
	EXPECT_EQ (t2.second.first.row, 1);
	EXPECT_EQ (t2.second.last.character, 1);
	EXPECT_EQ (t2.second.last.column, 2);
	EXPECT_EQ (t2.second.last.row, 1);
	EXPECT_NE (dynamic_cast <mu::io::tokens::right_square *> (t3.first), nullptr);
	EXPECT_EQ (t3.second.first.character, 2);
	EXPECT_EQ (t3.second.first.column, 3);
	EXPECT_EQ (t3.second.first.row, 1);
	EXPECT_EQ (t3.second.last.character, 2);
	EXPECT_EQ (t3.second.last.column, 3);
	EXPECT_EQ (t3.second.last.row, 1);
	EXPECT_NE (dynamic_cast <mu::io::tokens::divider *> (t4.first), nullptr);
	EXPECT_EQ (t4.second.first.character, 3);
	EXPECT_EQ (t4.second.first.column, 4);
	EXPECT_EQ (t4.second.first.row, 1);
	EXPECT_EQ (t4.second.last.character, 3);
	EXPECT_EQ (t4.second.last.column, 4);
	EXPECT_EQ (t4.second.last.row, 1);
	EXPECT_NE (dynamic_cast <mu::io::tokens::stream_end *> (t5.first), nullptr);
	EXPECT_EQ (t5.second.first.character, 4);
	EXPECT_EQ (t5.second.first.column, 5);
	EXPECT_EQ (t5.second.first.row, 1);
	EXPECT_EQ (t5.second.last.character, 4);
	EXPECT_EQ (t5.second.last.column, 5);
	EXPECT_EQ (t5.second.last.row, 1);
}

TEST (io_test, lexer4)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U"{}");
	ASSERT_TRUE (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	ASSERT_TRUE (t1i != nullptr);
	EXPECT_EQ (t1i->string.size (), 0);
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 1);
	EXPECT_EQ (t1.second.last.column, 2);
	EXPECT_EQ (t1.second.last.row, 1);
	ASSERT_TRUE (dynamic_cast <mu::io::tokens::stream_end *> (t2.first) != nullptr);
	EXPECT_EQ (t2.second.first.character, 2);
	EXPECT_EQ (t2.second.first.column, 3);
	EXPECT_EQ (t2.second.first.row, 1);
	EXPECT_EQ (t2.second.last.character, 2);
	EXPECT_EQ (t2.second.last.column, 3);
	EXPECT_EQ (t2.second.last.row, 1);
}

TEST (io_test, lexer5)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U"{a}a");
	ASSERT_TRUE (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	ASSERT_TRUE (t1i != nullptr);
	EXPECT_EQ (t1i->string.size (), 0);
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 3);
	EXPECT_EQ (t1.second.last.column, 4);
	EXPECT_EQ (t1.second.last.row, 1);
	EXPECT_NE (dynamic_cast <mu::io::tokens::stream_end *> (t2.first), nullptr);
	EXPECT_EQ (t2.second.first.character, 4);
	EXPECT_EQ (t2.second.first.column, 5);
	EXPECT_EQ (t2.second.first.row, 1);
	EXPECT_EQ (t2.second.last.character, 4);
	EXPECT_EQ (t2.second.last.column, 5);
	EXPECT_EQ (t2.second.last.row, 1);
}

TEST (io_test, lexer6)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U"{a}{};[]:a");
	EXPECT_EQ (result.results.size (), 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1i->string, mu::string (U"{};[]:"));
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 9);
	EXPECT_EQ (t1.second.last.column, 10);
	EXPECT_EQ (t1.second.last.row, 1);
	EXPECT_NE (dynamic_cast <mu::io::tokens::stream_end *> (t2.first), nullptr);
	EXPECT_EQ (t2.second.first.character, 10);
	EXPECT_EQ (t2.second.first.column, 11);
	EXPECT_EQ (t2.second.first.row, 1);
	EXPECT_EQ (t2.second.last.character, 10);
	EXPECT_EQ (t2.second.last.column, 11);
	EXPECT_EQ (t2.second.last.row, 1);
}

TEST (io_test, lexer7)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U"{:a}{};[]:a");
	ASSERT_TRUE (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	ASSERT_TRUE (t1i != nullptr);
	EXPECT_EQ (t1i->string, mu::string (U"{};[]"));
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 10);
	EXPECT_EQ (t1.second.last.column, 11);
	EXPECT_EQ (t1.second.last.row, 1);
	ASSERT_TRUE (dynamic_cast <mu::io::tokens::stream_end *> (t2.first) != nullptr);
	EXPECT_EQ (t2.second.first.character, 11);
	EXPECT_EQ (t2.second.first.column, 12);
	EXPECT_EQ (t2.second.first.row, 1);
	EXPECT_EQ (t2.second.last.character, 11);
	EXPECT_EQ (t2.second.last.column, 12);
	EXPECT_EQ (t2.second.last.row, 1);
}

TEST (io_test, lexer8)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":- a\nb");
	EXPECT_EQ (result.results.size (), 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_EQ (t1i->string, mu::string (U"b"));
	EXPECT_EQ (t1.second.first.character, 5);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 2);
	EXPECT_EQ (t1.second.last.character, 5);
	EXPECT_EQ (t1.second.last.column, 1);
	EXPECT_EQ (t1.second.last.row, 2);
	auto t2 (result.results [1]);
	EXPECT_NE (dynamic_cast <mu::io::tokens::stream_end *> (t2.first), nullptr);
	EXPECT_EQ (t2.second.first.character, 6);
	EXPECT_EQ (t2.second.first.column, 2);
	EXPECT_EQ (t2.second.first.row, 2);
	EXPECT_EQ (t2.second.last.character, 6);
	EXPECT_EQ (t2.second.last.column, 2);
	EXPECT_EQ (t2.second.last.row, 2);
}

//Testing single multiline comments
TEST (io_test, lexer9)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":( a :) b");
	ASSERT_TRUE (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_TRUE (t1i->string == mu::string (U"b"));
	EXPECT_EQ (t1.second.first.character, 8);
	EXPECT_EQ (t1.second.first.column, 9);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 8);
	EXPECT_EQ (t1.second.last.column, 9);
	EXPECT_EQ (t1.second.last.row, 1);
	auto t2 (result.results [1]);
	ASSERT_TRUE (dynamic_cast <mu::io::tokens::stream_end *> (t2.first) != nullptr);
	EXPECT_EQ (t2.second.first.character, 9);
	EXPECT_EQ (t2.second.first.column, 10);
	EXPECT_EQ (t2.second.first.row, 1);
	EXPECT_EQ (t2.second.last.character, 9);
	EXPECT_EQ (t2.second.last.column, 10);
	EXPECT_EQ (t2.second.last.row, 1);
}

//Testing nested multiline comments
TEST (io_test, lexer10)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":(:( a :):) b");
	ASSERT_TRUE (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_EQ (t1i->string, mu::string (U"b"));
	EXPECT_EQ (t1.second.first.character, 12);
	EXPECT_EQ (t1.second.first.column, 13);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 12);
	EXPECT_EQ (t1.second.last.column, 13);
	EXPECT_EQ (t1.second.last.row, 1);
	auto t2 (result.results [1]);
	EXPECT_NE (dynamic_cast <mu::io::tokens::stream_end *> (t2.first), nullptr);
	EXPECT_EQ (t2.second.first.character, 13);
	EXPECT_EQ (t2.second.first.column, 14);
	EXPECT_EQ (t2.second.first.row, 1);
	EXPECT_EQ (t2.second.last.character, 13);
	EXPECT_EQ (t2.second.last.column, 14);
	EXPECT_EQ (t2.second.last.row, 1);
}

TEST (io_test, lexer11)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":~");
	ASSERT_TRUE (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::parameters *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 1);
	EXPECT_EQ (t1.second.last.column, 2);
	EXPECT_EQ (t1.second.last.row, 1);
}

TEST (io_test, lexer12)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":~]");
	EXPECT_EQ (result.results.size (), 3);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::parameters *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 1);
	EXPECT_EQ (t1.second.last.column, 2);
	EXPECT_EQ (t1.second.last.row, 1);
	auto t2 (result.results [1]);
	auto t2i (dynamic_cast <mu::io::tokens::right_square *> (t2.first));
	EXPECT_NE (t2i, nullptr);
	EXPECT_EQ (t2.second.first.character, 2);
	EXPECT_EQ (t2.second.first.column, 3);
	EXPECT_EQ (t2.second.first.row, 1);
	EXPECT_EQ (t2.second.last.character, 2);
	EXPECT_EQ (t2.second.last.column, 3);
	EXPECT_EQ (t2.second.last.row, 1);
}

TEST (io_test, lexer13)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":a20");
	EXPECT_EQ (errors->errors.empty (), true);
	EXPECT_EQ (result.results.size (), 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1i->string, mu::string (U" "));
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 3);
	EXPECT_EQ (t1.second.last.column, 4);
	EXPECT_EQ (t1.second.last.row, 1);
}

TEST (io_test, lexer14)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U"thing:a20");
	EXPECT_EQ (errors->errors.empty (), true);
	EXPECT_EQ (result.results.size (), 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1i->string, U"thing ");
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 8);
	EXPECT_EQ (t1.second.last.column, 9);
	EXPECT_EQ (t1.second.last.row, 1);
}

TEST (io_test, lexer15)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":a20thing");
	EXPECT_EQ (errors->errors.empty (), true);
	EXPECT_EQ (result.results.size (), 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1i->string, U" thing");
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 8);
	EXPECT_EQ (t1.second.last.column, 9);
	EXPECT_EQ (t1.second.last.row, 1);
}

TEST (io_test, lexer16)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":u00000020");
	EXPECT_EQ (errors->errors.empty (), true);
	EXPECT_EQ (result.results.size (), 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1i->string, U" ");
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 9);
	EXPECT_EQ (t1.second.last.column, 10);
	EXPECT_EQ (t1.second.last.row, 1);
}

TEST (io_test, lexer17)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U"thing:u00000020");
	EXPECT_EQ (errors->errors.empty (), true);
	EXPECT_EQ (result.results.size (), 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1i->string, U"thing ");
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 14);
	EXPECT_EQ (t1.second.last.column, 15);
	EXPECT_EQ (t1.second.last.row, 1);
}

TEST (io_test, lexer18)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":u00000020thing");
	EXPECT_EQ (errors->errors.empty (), true);
	EXPECT_EQ (result.results.size (), 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1i->string, U" thing");
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 14);
	EXPECT_EQ (t1.second.last.column, 15);
	EXPECT_EQ (t1.second.last.row, 1);
}

TEST (io_test, lexer19)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":a7C:a3A:a3b:a5b:a5d");
	EXPECT_EQ (errors->errors.empty (), true);
	EXPECT_EQ (result.results.size (), 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1i->string, U"|:;[]");
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 19);
	EXPECT_EQ (t1.second.last.column, 20);
	EXPECT_EQ (t1.second.last.row, 1);
}

TEST (io_test, lexer20)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U"thing:~a");
	EXPECT_EQ (errors->errors.empty (), true);
	EXPECT_EQ (result.results.size (), 4);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	EXPECT_NE (t1i, nullptr);
	EXPECT_EQ (t1i->string, U"thing");
	EXPECT_EQ (t1.second.first.character, 0);
	EXPECT_EQ (t1.second.first.column, 1);
	EXPECT_EQ (t1.second.first.row, 1);
	EXPECT_EQ (t1.second.last.character, 4);
	EXPECT_EQ (t1.second.last.column, 5);
	EXPECT_EQ (t1.second.last.row, 1);
	auto t2 (result.results [1]);
	auto t2i (dynamic_cast <mu::io::tokens::parameters *> (t2.first));
	EXPECT_NE (t2i, nullptr);
	EXPECT_EQ (t2.second.first.character, 5);
	EXPECT_EQ (t2.second.first.column, 6);
	EXPECT_EQ (t2.second.first.row, 1);
	EXPECT_EQ (t2.second.last.character, 6);
	EXPECT_EQ (t2.second.last.column, 7);
	EXPECT_EQ (t2.second.last.row, 1);
	auto t3 (result.results [2]);
	auto t3i (dynamic_cast <mu::io::tokens::identifier *> (t3.first));
	EXPECT_NE (t3i, nullptr);
	EXPECT_EQ (t3i->string, U"a");
	EXPECT_EQ (t3.second.first.character, 7);
	EXPECT_EQ (t3.second.first.column, 8);
	EXPECT_EQ (t3.second.first.row, 1);
	EXPECT_EQ (t3.second.last.character, 7);
	EXPECT_EQ (t3.second.last.column, 8);
	EXPECT_EQ (t3.second.last.row, 1);
	auto t4 (result.results [3]);
	auto t4i (dynamic_cast <mu::io::tokens::stream_end *> (t4.first));
	EXPECT_NE (t4i, nullptr);
	EXPECT_EQ (t4.second.first.character, 8);
	EXPECT_EQ (t4.second.first.column, 9);
	EXPECT_EQ (t4.second.first.row, 1);
	EXPECT_EQ (t4.second.last.character, 8);
	EXPECT_EQ (t4.second.last.column, 9);
	EXPECT_EQ (t4.second.last.row, 1);
}

TEST (io_test, lexer21)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (*errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U"\r \rthing thing\r \r[ [\r \r] ]\r \r:~ :~\r \r:a50 :a50\r \r:u00000050 :u00000050\r \r; ;\r");
    EXPECT_EQ (result.results.size (), 15);
}