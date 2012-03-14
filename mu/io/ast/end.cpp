#include "end.h"

#include <mu/io/ast/visitor.h>

mu::io::ast::end::end (mu::io::debugging::context context_a)
	: mu::io::ast::node (context_a)
{
}

void mu::io::ast::end::operator () (mu::io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}

std::wstring mu::io::ast::end::name ()
{
	return std::wstring (L"end");
}