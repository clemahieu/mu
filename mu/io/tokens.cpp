#include <mu/io/tokens.hpp>

mu::io::token::token (mu::core::region const & region_a):
region (region_a)
{
}

mu::io::token::~token ()
{
}

mu::io::left_square::left_square (mu::core::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::left_square::id ()
{
    return mu::io::token_id::left_square;
}

mu::io::right_square::right_square (mu::core::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::right_square::id ()
{
    return mu::io::token_id::right_square;
}

mu::io::terminator::terminator (mu::core::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::terminator::id ()
{
    return mu::io::token_id::terminator;
}

mu::io::end::end (mu::core::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::end::id ()
{
    return mu::io::token_id::end;
}

mu::io::identifier::identifier (mu::core::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::identifier::id ()
{
    return mu::io::token_id::identifier;
}

mu::io::left_paren::left_paren (mu::core::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::left_paren::id ()
{
    return mu::io::token_id::left_paren;
}

mu::io::right_paren::right_paren (mu::core::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::right_paren::id ()
{
    return mu::io::token_id::right_paren;
}