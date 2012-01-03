#include "expression.h"

#include <lambda_p_serialization/ast/visitor.h>

lambda_p_serialization::ast::expression::expression (std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values_a)
	: values (values_a)
{
}

lambda_p_serialization::ast::expression::expression (std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values_a, std::vector <std::wstring> individual_names_a)
	: values (values_a),
	individual_names (individual_names_a)
{
}

lambda_p_serialization::ast::expression::expression (std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values_a, std::vector <std::wstring> individual_names_a, std::wstring full_name_a)
	: values (values_a),
	individual_names (individual_names_a),
	full_name (full_name_a)
{
}

std::wstring lambda_p_serialization::ast::expression::name ()
{
	return std::wstring (L"expression");
}

void lambda_p_serialization::ast::expression::operator () (lambda_p_serialization::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}