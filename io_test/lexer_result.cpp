#include "lexer_result.h"

void mu::io_test::lexer_result::operator () (mu::io::tokens::token * token_a, mu::core::context context_a)
{
	results.push_back (std::pair <mu::io::tokens::token *, mu::core::context> (token_a, context_a));
}