#include <mu/io/ast/builder.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <mu/script/ast/extension.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/ast/node.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_list.h>

mu::io::ast::builder::builder ()
	: errors (new mu::core::errors::error_list),
	parser (errors, boost::bind (&mu::io::ast::builder::add, this, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2)),
	building (new mu::io::ast::cluster)
{
}

void mu::io::ast::builder::add (boost::shared_ptr <mu::io::ast::node> node_a)
{
	current = node_a;
	(*node_a) (this);
}

void mu::io::ast::builder::operator () (mu::io::ast::parameters * parameters_a)
{
	boost::shared_ptr <mu::core::errors::error_target> errors_l (errors);
	(*errors_l) (L"Expecting only expressions or end of ast");
}

void mu::io::ast::builder::operator () (mu::io::ast::expression * expression_a)
{
	auto current_l (boost::static_pointer_cast <mu::io::ast::expression> (current));
	building->expressions.push_back (current_l);
}

void mu::io::ast::builder::operator () (mu::io::ast::identifier * identifier_a)
{
	boost::shared_ptr <mu::core::errors::error_target> errors_l (errors);
	(*errors_l) (L"Expecting only expressions or end of ast");
}

void mu::io::ast::builder::operator () (mu::io::ast::end * end_a)
{
	clusters.push_back (building);
	building.reset (new mu::io::ast::cluster);
}

void mu::io::ast::builder::operator () (wchar_t char_a)
{
	lexer (char_a);
}