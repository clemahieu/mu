#include <mu/test_entry/io/lexer_result.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/source.h>
#include <mu/io/tokens/identifier.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

// Testing EOS in middle of control character
TEST (io_test, control1)
{
	mu::io_test::lexer_result result;
	mu::core::errors::error_list errors;
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":");
	EXPECT_TRUE (result.results.empty ());
	EXPECT_TRUE (!errors.errors.empty ());
}

// Testing failure of invalid control characters
TEST (io_test, control2)
{
	mu::io_test::lexer_result result;
	mu::core::errors::error_list errors;
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	mu::io::process (lexer, U":0");
	EXPECT_TRUE (result.results.empty ());
	EXPECT_TRUE (!errors.errors.empty ());
}

// Testing control character {
TEST (io_test, control3)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::io::process (lexer, U":{");
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    EXPECT_TRUE (result_identifier1->string == mu::string (U"{"));
}

// Testing control character }
TEST (io_test, control4)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::io::process (lexer, U":}");
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    EXPECT_TRUE (result_identifier1->string == mu::string (U"}"));
}

// Testing control character [
TEST (io_test, control5)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::io::process (lexer, U":[");
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    EXPECT_TRUE (result_identifier1->string == mu::string (U"["));
}

// Testing control character ]
TEST (io_test, control6)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::io::process (lexer, U":]");
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    EXPECT_TRUE (result_identifier1->string == mu::string (U"]"));
}

// Testing control character :
TEST (io_test, control7)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::io::process (lexer, U"::");
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    EXPECT_TRUE (result_identifier1->string == mu::string (U":"));
}

// Testing control character ;
TEST (io_test, control8)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::io::process (lexer, U":;");
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    EXPECT_TRUE (result_identifier1->string == mu::string (U";"));
}

// Testing control character (space)
TEST (io_test, control9)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::io::process (lexer, U": ");
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    EXPECT_TRUE (result_identifier1->string == mu::string (U" "));
}

// Testing control character \0
TEST (io_test, control10)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::string str;
    str.push_back (U':');
    str.push_back (U'\0');
    mu::io::process (lexer, str);
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    ASSERT_TRUE (result_identifier1->string.size () == 1);
    EXPECT_TRUE (result_identifier1->string [0] == L'\0');
}

// Testing control character \t
TEST (io_test, control11)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::io::process (lexer, U":\t");
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    EXPECT_TRUE (result_identifier1->string == mu::string (U"\t"));
}

// Testing control character \f
TEST (io_test, control12)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::io::process (lexer, U":\f");
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    EXPECT_TRUE (result_identifier1->string == mu::string (U"\f"));
}

// Testing control character \r
TEST (io_test, control13)
{
    mu::io_test ::lexer_result result;
    mu::core::errors::error_list errors;
    mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
    mu::io::process (lexer, U":\r");
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (!result.results.empty ());
    auto result1 (result.results [0]);
    ASSERT_TRUE (dynamic_cast <mu::io::tokens::identifier *> (result1.first) != nullptr);
    auto result_identifier1 (static_cast <mu::io::tokens::identifier *> (result1.first));
    EXPECT_TRUE (result_identifier1->string == mu::string (U"\r"));
}
