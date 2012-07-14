#include <mu/core/routine.h>

#include <mu/core/expression.h>
#include <mu/core/visitor.h>

mu::core::routine::routine ()
{
}

mu::core::routine::routine (mu::core::expression * body_a)
	: body (body_a)
{
}

void mu::core::routine::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}

std::wstring mu::core::routine::name ()
{
	return std::wstring (L"mu::core::routine");
}