#include <mu/io/parser/parser.h>

#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/parser/error.h>
#include <mu/io/parser/begin.h>
#include <mu/io/parser/finished.h>
#include <mu/io/parser/error_target.h>
#include <mu/io/ast/cluster.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <map>

#include <gc_cpp.h>

mu::io::parser::parser::parser (mu::core::errors::error_target * errors_a, boost::function <void (boost::shared_ptr <mu::io::ast::cluster>)> target_a)
	: cluster (new mu::io::ast::cluster),
	errors (new (GC) mu::io::parser::error_target (*this, errors_a)),
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

void mu::io::parser::parser::operator () (boost::shared_ptr <mu::io::ast::expression> expression_a)
{
	cluster->expressions.push_back (expression_a);
}

void mu::io::parser::parser::finish ()
{
	cluster->context.last = context.last;
	target (cluster);
	cluster.reset (new mu::io::ast::cluster);
	reset ();
}

void mu::io::parser::parser::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
	state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::finished (*this)));
	state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::begin (*this)));
}