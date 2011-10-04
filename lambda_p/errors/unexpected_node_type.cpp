#include "unexpected_node_type.h"

#include <string>

lambda_p::errors::unexpected_node_type::unexpected_node_type (::std::wstring binder_name_a, size_t position_a, ::lambda_p::core::node_id id_a)
	: id (id_a),
	position (position_a),
	binder_error (binder_name_a)
{
}

lambda_p::errors::error_id lambda_p::errors::unexpected_node_type::error_type ()
{
	return ::lambda_p::errors::error_unexpected_node_type;
}

void lambda_p::errors::unexpected_node_type::string (::std::wostream & stream)
{
	::std::wstring node_name (::lambda_p::core::node_name (id));
	stream << L"Unexpected node type: ";
	stream << node_name;
	stream << L" at position: ";
	stream << position;
}
