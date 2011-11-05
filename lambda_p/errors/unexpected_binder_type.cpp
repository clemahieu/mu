#include "unexpected_binder_type.h"

#include <string>

lambda_p::errors::unexpected_binder_type::unexpected_binder_type (std::wstring binder_name_a, size_t position_a, std::wstring expected_type_a)
	: expected_type (expected_type_a),
	position (position_a),
	binder_error (binder_name_a)
{
}

lambda_p::errors::error_id lambda_p::errors::unexpected_binder_type::error_type ()
{
	return lambda_p::errors::error_unexpected_node_type;
}

void lambda_p::errors::unexpected_binder_type::string (std::wostream & stream)
{
	stream << L"In binder: ";
	stream << binder_name;
	stream << " unexpected binder type at position: ";
	stream << position;
	stream << L" expecting: ";
	stream << expected_type;
}
