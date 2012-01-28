#include "builder.h"

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <lambda_p_io/analyzer/extensions/ast.h>
#include <lambda_p_io/analyzer/extensions/extensions.h>

lambda_p_io::builder::builder ()
	: errors (new lambda_p::errors::error_list),
	analyzer (boost::bind (&lambda_p_io::builder::operator (), this, _1), errors),
	parser (errors, boost::bind (&lambda_p_io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&lambda_p_io::parser::parser::operator (), &parser, _1, _2))
{
	analyzer.extensions->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L".ast"), boost::make_shared <lambda_p_io::analyzer::extensions::ast> ()));
}

void lambda_p_io::builder::operator () (boost::shared_ptr <lambda_p::cluster> cluster_a)
{
	clusters.push_back (cluster_a);
}
