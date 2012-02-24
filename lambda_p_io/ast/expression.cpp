#include "expression.h"

#include <lambda_p_io/ast/visitor.h>
#include <lambda_p_io/ast/identifier.h>

lambda_p_io::ast::expression::expression (mu::core::context context_a, std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values_a)
	: values (values_a),
	lambda_p_io::ast::node (context_a),
	full_name (new lambda_p_io::ast::identifier (mu::core::context (), std::wstring ()))
{
}

lambda_p_io::ast::expression::expression (mu::core::context context_a, std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values_a, std::vector <boost::shared_ptr <lambda_p_io::ast::identifier>> individual_names_a)
	: values (values_a),
	individual_names (individual_names_a),
	lambda_p_io::ast::node (context_a),
	full_name (new lambda_p_io::ast::identifier (mu::core::context (), std::wstring ()))
{
}

lambda_p_io::ast::expression::expression (mu::core::context context_a, std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values_a, std::vector <boost::shared_ptr <lambda_p_io::ast::identifier>> individual_names_a, boost::shared_ptr <lambda_p_io::ast::identifier> full_name_a)
	: values (values_a),
	individual_names (individual_names_a),
	full_name (full_name_a),
	lambda_p_io::ast::node (context_a)
{
}

std::wstring lambda_p_io::ast::expression::name ()
{
	return std::wstring (L"expression");
}

void lambda_p_io::ast::expression::operator () (lambda_p_io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}