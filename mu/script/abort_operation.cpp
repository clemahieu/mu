#include <mu/script/abort_operation.h>

#include <mu/script/abort_exception.h>

bool mu::script::abort::operation::operator () (mu::script::context & context_a)
{
    throw mu::script::abort_exception ();
}