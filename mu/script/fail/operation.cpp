#include <mu/script/fail/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/context.h>
#include <mu/script/runtime/trace.h>

void mu::script::fail::operation::operator () (mu::script::context & context_a)
{
    context_a (L"Failure");
}