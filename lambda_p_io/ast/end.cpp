#include "end.h"

#include <lambda_p_io/ast/visitor.h>

lambda_p_io::ast::end::end (mu::core::context context_a)
	: lambda_p_io::ast::node (context_a)
{
}

void lambda_p_io::ast::end::operator () (lambda_p_io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}

std::wstring lambda_p_io::ast::end::name ()
{
	return std::wstring (L"end");
}