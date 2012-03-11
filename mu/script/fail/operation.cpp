#include <mu/script/fail/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/context.h>
#include <mu/script/runtime/trace.h>

void mu::script::fail::operation::operator () (mu::script::context & context_a)
{
	mu::script::runtime::trace trace (context_a, this);
    context_a (L"Failure");
}