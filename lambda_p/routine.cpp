#include "routine.h"

#include <lambda_p/expression.h>

#include <lambda_p/visitor.h>

lambda_p::routine::routine (lambda_p::context context_a)
	: parameters (new lambda_p::expression (context_a))
{
}

lambda_p::routine::routine (boost::shared_ptr <lambda_p::expression> body_a, boost::shared_ptr <lambda_p::expression> parameters_a)
	: parameters (parameters_a),
	body (body_a)
{

}

void lambda_p::routine::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}

std::wstring lambda_p::routine::name ()
{
	return std::wstring (L"lambda_p::routine");
}