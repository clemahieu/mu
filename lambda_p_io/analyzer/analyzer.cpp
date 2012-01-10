#include "analyzer.h"

#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p/errors/string_error.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

lambda_p_io::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <lambda_p::routine>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: target (target_a),
	errors (errors_a)
{
}

lambda_p_io::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <lambda_p::routine>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> extensions_a)
	: target (target_a),
	errors (errors_a),
	extensions (extensions_a)
{
}

void lambda_p_io::analyzer::analyzer::operator () (boost::shared_ptr <lambda_p_io::ast::expression> expression_a)
{
	lambda_p_io::analyzer::routine (*this, expression_a.get ());
}