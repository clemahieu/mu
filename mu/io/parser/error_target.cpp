#include <mu/io/parser/error_target.h>

#include <mu/io/debugging/error.h>
#include <mu/io/parser/parser.h>

#include <boost/make_shared.hpp>

mu::io::parser::error_target::error_target (mu::io::parser::parser & parser_a, boost::shared_ptr <mu::core::errors::error_target> target_a)
	: parser (parser_a),
	target (target_a)
{
}

void mu::io::parser::error_target::operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a)
{
	(*target) (boost::make_shared <mu::io::debugging::error> (error, parser.context), parser.context);
}

bool mu::io::parser::error_target::operator () ()
{
	auto result ((*target) ());
	return result;
}

void mu::io::parser::error_target::print (std::wostream & target_a)
{
	target->print (target_a);
}