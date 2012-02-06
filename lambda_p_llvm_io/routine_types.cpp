#include "routine_types.h"

#include <lambda_p/order.h>
#include <lambda_p/routine.h>
#include <lambda_p/errors/error_context.h>
#include <lambda_p/expression.h>
#include <lambda_p_llvm_io/expression_types.h>

#include <boost/make_shared.hpp>

lambda_p_llvm_io::routine_types::routine_types (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::routine> routine_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a, lambda_p_llvm_io::cluster_types & cluster_a)
	: type_set (false)
{
	lambda_p::order order (routine_a->body);
	for (auto i (order.expressions.begin ()), j (order.expressions.end ()); i != j && !type_set; ++i)
	{
		auto errors_l (boost::make_shared <lambda_p::errors::error_context> (errors_a, (*i)->context));
		lambda_p_llvm_io::expression_types expression (errors_l, *this, *i);
	}
	if (!type_set)
	{
		(*errors_a) (L"Routine does not define signature");
	}
}