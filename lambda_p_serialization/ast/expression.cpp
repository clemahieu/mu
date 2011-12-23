#include "expression.h"

lambda_p_serialization::ast::node_ids lambda_p_serialization::ast::expression::node_id ()
{
	return lambda_p_serialization::ast::node_ids::expression;
}

std::wstring lambda_p_serialization::ast::expression::name ()
{
	return std::wstring (L"expression");
}