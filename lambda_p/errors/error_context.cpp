#include "error_context.h"

lambda_p::errors::error_context::error_context (boost::shared_ptr <lambda_p::errors::error_target> target_a, lambda_p::context context_a)
	: target (target_a),
	context (context_a)
{
}

void lambda_p::errors::error_context::operator () (boost::shared_ptr <lambda_p::errors::error> error, lambda_p::context context_a)
{
	(*target) (error, context_a);
}

bool lambda_p::errors::error_context::operator () ()
{
	return (*target) ();
}

void lambda_p::errors::error_context::operator () (std::wstring error)
{
	(*target) (error, context);
}

void lambda_p::errors::error_context::operator () (wchar_t const * error)
{
	(*target) (error, context);
}