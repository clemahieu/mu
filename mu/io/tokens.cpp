#include <mu/io/tokens.hpp>

mu::io::token::~token ()
{
}

mu::io::token_id mu::io::left_square::id ()
{
    return mu::io::token_id::left_square;
}

mu::io::token_id mu::io::right_square::id ()
{
    return mu::io::token_id::right_square;
}

mu::io::token_id mu::io::terminator::id ()
{
    return mu::io::token_id::terminator;
}

mu::io::token_id mu::io::end::id ()
{
    return mu::io::token_id::end;
}

mu::io::token_id mu::io::identifier::id ()
{
    return mu::io::token_id::identifier;
}