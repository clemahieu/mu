#include <mu/io/parser/parser.h>

#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/parser/error.h>
#include <mu/io/parser/begin.h>
#include <mu/io/parser/finished.h>
#include <mu/io/parser/error_target.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <map>

mu::io::parser::parser::parser (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::function <void (boost::shared_ptr <mu::io::ast::node>)> target_a)
	: errors (boost::make_shared <mu::io::parser::error_target> (*this, errors_a)),
	target (target_a)
{
	reset ();
}

void mu::io::parser::parser::operator () (mu::io::tokens::token * token, mu::io::debugging::context context_a)
{
	context = context_a;
	auto state_l (state.top ());
	(*token) (state_l.get ());
}

void mu::io::parser::parser::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::finished (*this)));
	state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::begin (*this, target)));
}