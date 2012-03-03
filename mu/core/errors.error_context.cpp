#include "errors.error_context.h"

mu::core::errors::error_context::error_context (boost::shared_ptr <mu::core::errors::error_target> target_a, mu::core::context context_a)
	: target (target_a),
	context (context_a)
{
}

void mu::core::errors::error_context::operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a)
{
	(*target) (error, context_a);
}

bool mu::core::errors::error_context::operator () ()
{
	return (*target) ();
}

void mu::core::errors::error_context::operator () (std::wstring error)
{
	(*target) (error, context);
}

void mu::core::errors::error_context::operator () (wchar_t const * error)
{
	(*target) (error, context);
}
