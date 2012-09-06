#include <mu/test_entry/io_lexer_result.h>

#include <mu/io/tokens_token.h>
#include <mu/io/tokens_implementor.h>

#include <iostream>

#include <gc_cpp.h>

void mu::io_test::lexer_result::operator() (mu::io::tokens::token const & token)
{
    token (this);
}

void mu::io_test::lexer_result::operator () (mu::io::tokens::divider const & token)
{
    results.push_back (new (GC) mu::io::tokens::divider (token));
}

void mu::io_test::lexer_result::operator () (mu::io::tokens::identifier const & token)
{
    results.push_back (new (GC) mu::io::tokens::identifier (token));
}

void mu::io_test::lexer_result::operator () (mu::io::tokens::left_square const & token)
{
    results.push_back (new (GC) mu::io::tokens::left_square (token));
}

void mu::io_test::lexer_result::operator () (mu::io::tokens::right_square const & token)
{
    results.push_back (new (GC) mu::io::tokens::right_square (token));
}

void mu::io_test::lexer_result::operator () (mu::io::tokens::stream_end const & token)
{
    results.push_back (new (GC) mu::io::tokens::stream_end (token));
}

void mu::io_test::lexer_result::operator () (mu::io::tokens::value const & token)
{
    results.push_back (new (GC) mu::io::tokens::value (token));
}

void mu::io_test::lexer_result::print (std::wostream & target)
{
    for (auto i (results.begin ()), j (results.end ()); i != j; ++i)
    {
        auto token_name ((*i)->token_name ());
        std::wstring str (token_name.begin (), token_name.end ());
        target << str;
        target << U' ';
    }
}