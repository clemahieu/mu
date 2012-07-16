#include <mu/io/parser/error_target.h>

#include <mu/io/parser/parser.h>

mu::io::parser::error_target::error_target (mu::io::parser::parser & parser_a, mu::core::errors::error_target * target_a)
	: parser (parser_a),
	target (target_a)
{
}

void mu::io::parser::error_target::operator () (mu::core::errors::error * error)
{
	(*target) (error);
}

bool mu::io::parser::error_target::operator () ()
{
	auto result ((*target) ());
	return result;
}

void mu::io::parser::error_target::print (mu::ostream & target_a)
{
	target->print (target_a);
}