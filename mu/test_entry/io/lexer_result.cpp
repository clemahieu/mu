#include <mu/test_entry/io/lexer_result.h>

#include <mu/io/tokens/token.h>

#include <iostream>

void mu::io_test::lexer_result::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
	results.push_back (std::pair <mu::io::tokens::token *, mu::io::debugging::context> (token_a, context_a));
}

void mu::io_test::lexer_result::print (std::wostream & target)
{
    for (auto i (results.begin ()), j (results.end ()); i != j; ++i)
    {
        std::wstring str (i->first->token_name ().begin (), i->first->token_name().end ());
        target << str;
        target << L' ';
    }
}