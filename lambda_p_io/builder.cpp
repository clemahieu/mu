#include "builder.h"

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <lambda_p_script/ast/extension.h>
#include <lambda_p_io/analyzer/extensions/extensions.h>
#include <lambda_p_io/ast/cluster.h>
#include <lambda_p_io/ast/node.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/errors/error_list.h>

lambda_p_io::builder::builder ()
	: errors (new lambda_p::errors::error_list),
	parser (errors, boost::bind (&lambda_p_io::builder::add, this, _1)),
	lexer (errors, boost::bind (&lambda_p_io::parser::parser::operator (), &parser, _1, _2)),
	building (new lambda_p_io::ast::cluster)
{
}

void lambda_p_io::builder::add (boost::shared_ptr <lambda_p_io::ast::node> node_a)
{
	current = node_a;
	(*node_a) (this);
}

void lambda_p_io::builder::operator () (lambda_p_io::ast::parameters * parameters_a)
{
	boost::shared_ptr <lambda_p::errors::error_target> errors_l (errors);
	(*errors_l) (L"Expecting only expressions or end of ast");
}

void lambda_p_io::builder::operator () (lambda_p_io::ast::expression * expression_a)
{
	auto current_l (boost::static_pointer_cast <lambda_p_io::ast::expression> (current));
	building->expressions.push_back (current_l);
}

void lambda_p_io::builder::operator () (lambda_p_io::ast::identifier * identifier_a)
{
	boost::shared_ptr <lambda_p::errors::error_target> errors_l (errors);
	(*errors_l) (L"Expecting only expressions or end of ast");
}

void lambda_p_io::builder::operator () (lambda_p_io::ast::end * end_a)
{
	clusters.push_back (building);
	building.reset (new lambda_p_io::ast::cluster);
}
