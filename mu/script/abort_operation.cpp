#include <mu/script/abort_operation.h>

#include <cstdlib>

bool mu::script::abort::operation::operator () (mu::script::context & context_a)
{
    std::abort ();
}