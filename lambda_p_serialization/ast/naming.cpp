#include "naming.h"

lambda_p_serialization::ast::node_ids lambda_p_serialization::ast::naming::node_id ()
{
	return lambda_p_serialization::ast::node_ids::naming;
}

std::wstring lambda_p_serialization::ast::naming::name ()
{
	return std::wstring (L"naming");
}