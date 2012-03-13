#include <mu/script/fail/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/context.h>
#include <mu/script/runtime/trace.h>
#include <mu/script/debugging/binary_info.h>

#include <boost/make_shared.hpp>

void mu::script::fail::operation::operator () (mu::script::context & context_a)
{
	mu::script::runtime::trace trace (context_a, boost::make_shared <mu::script::debugging::binary_info> (typeid (*this)));
    context_a (L"Failure");
}