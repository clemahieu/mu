#include "analyzer.h"

#include <lambda_p_io/ast/node.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p/errors/string_error.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

lambda_p_io::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <lambda_p::expression>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: target (target_a),
	errors (errors_a)
{
}

lambda_p_io::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <lambda_p::expression>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> extensions_a)
	: target (target_a),
	errors (errors_a),
	extensions (extensions_a)
{
}

void lambda_p_io::analyzer::analyzer::operator () (boost::shared_ptr <lambda_p_io::ast::node> node)
{
	(*node) (this);
}

void lambda_p_io::analyzer::analyzer::operator () (lambda_p_io::ast::expression * expression_a)
{
	lambda_p_io::analyzer::routine (*this, expression_a);
}

void lambda_p_io::analyzer::analyzer::operator () (lambda_p_io::ast::identifier * identifier_a)
{
	std::wstringstream message;
	message << L"At top level, expecting expression, have identifier: ";
	message << identifier_a->string;
	(*errors) (message.str ());
}