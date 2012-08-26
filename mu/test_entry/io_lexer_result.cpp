#include <mu/test_entry/io_lexer_result.h>

#include <mu/io/tokens_token.h>

#include <iostream>

void mu::io_test::lexer_result::operator () (mu::io::tokens::token * token_a)
{
	results.push_back (token_a);
}

void mu::io_test::lexer_result::print (std::wostream & target)
{
    for (auto i (results.begin ()), j (results.end ()); i != j; ++i)
    {
        auto token_name ((*i)->token_name ());
        std::wstring str (token_name.begin (), token_name.end ());
        target << str;
        target << L' ';
    }
}