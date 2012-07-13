#include <mu/io/lexer/error_target.h>

#include <mu/io/lexer/lexer.h>

#include <boost/make_shared.hpp>

mu::io::lexer::error_target::error_target (mu::io::lexer::lexer & lexer_a, boost::shared_ptr <mu::core::errors::error_target> target_a)
	: lexer (lexer_a),
	target (target_a)
{
}

void mu::io::lexer::error_target::operator () (mu::core::errors::error * error)
{
	(*target) (error);
}

bool mu::io::lexer::error_target::operator () ()
{
	auto result ((*target) ());
	return result;
}

void mu::io::lexer::error_target::print (std::wostream & target_a)
{
	target->print (target_a);
}