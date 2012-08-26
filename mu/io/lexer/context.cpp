#include <mu/io/lexer/context.h>

mu::io::lexer::context::context ()
{
}

mu::io::lexer::context::context (mu::io::position position_a, char32_t character_a):
position (position_a),
character (character_a)
{
}