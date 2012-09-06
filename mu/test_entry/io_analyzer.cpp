#include <gtest/gtest.h>

#include <mu/io/analyzer_analyzer.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/tokens_identifier.h>
#include <mu/test_entry/io_extension5.h>
#include <mu/test_entry/io_lexer_result.h>

#include <gc_cpp.h>

// No extensions
TEST (io_test, analyzer1)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    mu::io::analyzer::extensions extensions;
    mu::io_test::lexer_result tokens;
    mu::io::analyzer::analyzer analyzer (errors,
                                               [&tokens]
                                               (mu::io::tokens::token const & token)
                                               {
                                                   tokens (token);
                                               }, &extensions);
    analyzer (mu::io::tokens::identifier (context, mu::string (U"test")));
    ASSERT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (tokens.results.size () == 1);
    auto identifier (dynamic_cast <mu::io::tokens::identifier const *> (tokens.results [0]));
    ASSERT_TRUE (identifier != nullptr);
    ASSERT_TRUE (identifier->string == mu::string (U"test"));
}

// No extensions
TEST (io_test, analyzer2)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    mu::io::analyzer::extensions extensions;
    extensions.add <mu::io_test::extension5> (mu::string (U"test"));
    mu::io_test::lexer_result tokens;
    mu::io::analyzer::analyzer analyzer (errors,
                                               [&tokens]
                                               (mu::io::tokens::token const & token)
                                               {
                                                   tokens (token);
                                               }, &extensions);
    analyzer (mu::io::tokens::identifier (context, mu::string (U"test")));
    analyzer (mu::io::tokens::identifier (context, mu::string (U"test123")));
    ASSERT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (tokens.results.size () == 2);
    auto identifier (dynamic_cast <mu::io::tokens::identifier const *> (tokens.results [0]));
    ASSERT_TRUE (identifier != nullptr);
    ASSERT_TRUE (identifier->string == mu::string (U""));
    auto identifier1 (dynamic_cast <mu::io::tokens::identifier const *> (tokens.results [1]));
    ASSERT_TRUE (identifier1 != nullptr);
    ASSERT_TRUE (identifier1->string == mu::string (U"123"));
}