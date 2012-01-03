#include "analyzer.h"

#include <lambda_p_serialization/ast/node.h>
#include <lambda_p_serialization/ast/identifier.h>
#include <lambda_p_serialization/analyzer/routine.h>
#include <lambda_p/errors/string_error.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

lambda_p_serialization::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: target (target_a),
	errors (errors_a)
{
}

void lambda_p_serialization::analyzer::analyzer::operator () (boost::shared_ptr <lambda_p_serialization::ast::node> node)
{
	(*node) (this);
}

void lambda_p_serialization::analyzer::analyzer::operator () (lambda_p_serialization::ast::expression * expression_a)
{
	std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::analyzer::declaration>> declarations;
	lambda_p_serialization::analyzer::routine (*this, expression_a, declarations, errors);
}

void lambda_p_serialization::analyzer::analyzer::operator () (lambda_p_serialization::ast::identifier * identifier_a)
{
	std::wstringstream message;
	message << L"At top level, expecting expression, have identifier: ";
	message << identifier_a->string;
	(*errors) (message.str ());
}