#include "link.h"

#include <lambda_p/visitor.h>

lambda_p::link::link (boost::shared_ptr <lambda_p::routine> routine_a)
	: routine (routine_a)
{
}

void lambda_p::link::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}

std::wstring lambda_p::link::name ()
{
	return std::wstring (L"lambda_p::link");
}
