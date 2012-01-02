#include "analyzer.h"

#include <lambda_p_serialization/ast/node.h>
#include <lambda_p_serialization/ast/identifier.h>
#include <lambda_p_serialization/analyzer/routine.h>

#include <sstream>

lambda_p_serialization::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, boost::function <void (std::wstring)> errors_a)
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
	lambda_p_serialization::analyzer::routine (*this, expression_a);
}

void lambda_p_serialization::analyzer::analyzer::operator () (lambda_p_serialization::ast::identifier * identifier_a)
{
	std::wstringstream message;
	message << L"At top level, expecting expression, have identifier: ";
	message << identifier_a->string;
	errors (message.str ());
}