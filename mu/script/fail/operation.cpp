#include <mu/script/fail/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/context.h>

void mu::script::fail::operation::operator () (mu::script::context & context_a)
{
    (*context_a.errors) (L"Failure");
}